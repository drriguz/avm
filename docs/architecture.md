# Architecture

This document describes how avm is implemented — the class file format, runtime data structures, class loading pipeline, bytecode interpreter, and how to add new instructions.

## Project Layout

```
avm/
├── class_file/                  # .class file parser library
│   ├── include/class_file/
│   │   ├── format/              # Data structures (JavaClass, ConstantPool, Instruction, etc.)
│   │   ├── parser/              # BinaryReader, JavaClassParser
│   │   └── helper/              # String utilities
│   └── src/                     # Implementations
├── vm/                          # Runtime and interpreter library
│   ├── include/vm/
│   │   ├── runtime/             # Frame, VmStack, VmClass, Heap, Object, etc.
│   │   └── util/                # Number splitting utilities
│   └── src/
│       ├── interpreter/         # Opcode handlers (11 files by category)
│       ├── runtime/             # Runtime component implementations
│       └── util/
├── avm_cli/                     # CLI entry point (stub)
└── tests/
    ├── src/                     # C++ test files (Google Test)
    └── res/                     # Java fixtures (.java + compiled .class)
```

## Class File Parsing (`class_file` library)

The parser reads `.class` files byte-by-byte according to the JVM spec. The main entry point is `JavaClassParser`, which reads from a `BinaryReader` (abstract) / `FileReader` (disk) and builds a `JavaClass` object.

### Key types

| Type | Purpose |
|------|---------|
| `JavaClass` | Top-level container: header, constant pool, fields, methods, interfaces |
| `ConstantPool` | Array of 17 constant types (Utf8, Class, Fieldref, Methodref, Integer, Float, Long, Double, String, NameAndType, etc.) |
| `FieldInfo` / `MethodInfo` | Class members with access flags, descriptor, and attributes |
| `Code` | Attribute containing bytecode instructions, max stack/locals, and exception table |
| `Instruction` | Single opcode + 0–2 operand bytes. Stores `_byteOffset` for branch target calculation |
| `FieldType` | Type descriptor hierarchy: `BaseType` (int, float, etc.), `ObjectType` (class references), `ArrayType` |

### Instruction encoding

The parser reads instructions sequentially from the bytecode array. Each instruction is stored as an `Instruction` object with its opcode, operand bytes, and byte offset. Multi-byte instructions (e.g., `goto` with a 2-byte offset) occupy one slot in the instruction vector but multiple bytes in the original bytecode.

The `instructionSet[]` array in `opcodes.h` maps each opcode to its operand count (0, 1, or 2 bytes).

## Runtime Data Structures (`vm` library)

### Slot and Reference

The fundamental storage unit is `SLOT`, defined in `slot.h`:

```cpp
#ifdef _ARCH_X64_
#define SLOT uint64_t
#else
#define SLOT uint32_t
#endif
typedef SLOT reference;
```

On 64-bit platforms, `SLOT` is 8 bytes. On 32-bit, it's 4 bytes. The `reference` type (for object pointers) is always the same size as `SLOT`.

**All values occupy 1 or 2 positions** regardless of platform:
- `int`, `float`, `byte`, `short`, `char`, `reference` → 1 position
- `long`, `double` → 2 positions (split into two 32-bit halves)

### Frame

A `Frame` represents one method invocation on the call stack:

```
Frame
├── _pc              — program counter (instruction index)
├── _operandStack    — OperandStack (std::stack<SLOT>)
├── _localVariables  — LocalVariables (SLOT* array)
├── _runtimeConstants — const ConstantPool* (from the class file)
└── _previousFrame   — link to caller's frame
```

The operand stack grows upward (push adds to top). Local variables are accessed by index. Long/double values occupy two consecutive positions in both the stack and locals.

### VmStack

A `std::stack<std::unique_ptr<Frame>>` — the JVM call stack. `currentFrame()` returns the top frame. `push()`/`pop()` manage frame lifecycle.

### Heap

A 10 MB bump-allocator (`OBJECT_UNIT*` array where `OBJECT_UNIT` is always `uint64_t`). `newInstance(VmClass)` allocates `type.getSize()` units and returns an `Object` wrapper. No garbage collection.

### Object

A thin wrapper over a pointer into the heap:

```cpp
class Object {
    OBJECT_UNIT* _data;
    int _size;
};
```

Field access methods (`setIntAt`, `setLongAt`, `setReferenceAt`, etc.) read/write at offsets computed during class preparation. References are stored as a single `OBJECT_UNIT` (64-bit on x64, 32-bit on 32-bit).

### VmClass / VmMethod / VmField

- `VmClass` wraps a `JavaClass` with runtime state: superclass/interface links, registered fields/methods, field size calculations, constant field initialization.
- `VmMethod` wraps a `MethodInfo` with parameter count, max stack/locals, and instruction access.
- `VmField` wraps a field with its descriptor, offset (for instance fields), and value storage (for static fields use `_value1`/`_value2`).

## Class Loading Pipeline

```
VirtualMachine::getClass(name)
  → ClasspathClassLoader::load(name, methodArea)
    → resolve(name, methodArea)
      → readClass(name)           // parse .class file from disk
      → new VmClass(javaClass)    // wrap with runtime state
      → load(superclass)          // recursive: load superclass chain
      → load(interfaces)          // recursive: load interfaces
      → methodArea->register()
    → link(vmClass)
      → prepare()
        → registerFields()        // compute field offsets, init constant fields
        → registerMethods()       // build method lookup table
```

The class loader caches parsed `JavaClass` objects in `_classCache` and loaded `VmClass` objects in the `MethodArea`. Classes are loaded lazily on first reference.

## Bytecode Interpreter

### Dispatch

The interpreter uses a function pointer table indexed by opcode:

```cpp
using invoke_fn = void(Context&, const Instruction*);
invoke_fn* invoke_mapping[] = { invoke_nop, invoke_aconst_null, ... };
```

Each handler function has the signature `void invoke_xxx(Context& context, const Instruction* instruction)`.

### Execute Loop

```cpp
void Interpreter::execute(const VmMethod* method, VirtualMachine& jvm, VmStack& stack) {
    Frame* frame = stack.currentFrame();
    while(true) {
        int pc = frame->getNextPc();          // returns current index, increments
        const Instruction* instruction = ...;  // fetch by index
        if(instruction == nullptr) break;      // end of method
        Context context(&jvm, &stack, method);
        invoke(&context, instruction);          // dispatch via invoke_mapping
        if(stack.currentFrame() != frame) break; // frame changed (return or call)
    }
}
```

### Method Invocation

`Interpreter::invoke()` handles both static and instance methods:

1. Calculate required locals and max stack
2. Create a new `Frame` and push it onto the `VmStack`
3. For instance methods: pop objectref from caller's stack, store as local 0
4. Pop parameters in reverse order (rightmost first) from caller's stack into locals
5. Call `execute()` for the new frame

For native methods, `invokeNative()` pops parameters and dispatches by name (currently only `println(int)`).

### Branch Target Calculation

Branch instructions (`goto`, `ifeq`, `if_icmpne`, etc.) use byte offsets from the JVM spec. Since the instruction vector uses sequential indices (not byte offsets), branch handlers must convert:

```cpp
int targetByteOffset = instruction->getByteOffset() + offset;
int targetIdx = context.getMethod()->getInstructionIndexAtByteOffset(targetByteOffset);
context.frame()->setPc(targetIdx);
```

`getNextPc()` auto-increments, so setting `pc = targetIdx` means the next fetch returns `targetIdx` and increments to `targetIdx + 1`.

### Object Initialization

`invokespecial` for `java/lang/Object.<init>` is skipped to prevent infinite recursion (the stub Object constructor calls itself via `invokespecial`). The objectref is still popped from the caller's stack.

## How to Add a New Opcode

1. **Add the handler function** in the appropriate category file under `vm/src/interpreter/`:
   - `constants.cpp` — constant push
   - `loads.cpp` / `stores.cpp` — local variable access
   - `stack.cpp` — operand stack manipulation
   - `math.cpp` — arithmetic, bitwise, shifts
   - `conversions.cpp` — type conversions
   - `comparisons.cpp` — comparisons and conditional branches
   - `control.cpp` — unconditional branches, returns
   - `references.cpp` — field/method access, object creation
   - `extended.cpp` — wide, ifnull/ifnonnull

2. **Declare the function** in `vm/include/vm/interpreter.h`:
   ```cpp
   void invoke_xxx(Context& context, const Instruction* instruction);
   ```

3. **Register it** in the `invoke_mapping[]` table in `vm/src/interpreter.cpp` at the correct index (matching the opcode value in the JVM spec).

4. **Implement the handler** following the existing patterns:
   ```cpp
   void avm::invoke_xxx(Context& context, const Instruction* instruction) {
       // Pop operands from stack, perform operation, push result
       auto stack = context.frame()->getOperandStack();
       auto locals = context.frame()->getLocalVariables();
       // ...
   }
   ```

5. **Add tests** — either instruction-level tests (construct `Instruction` objects manually and verify stack state) or execution tests (run a Java method end-to-end).

## Key API Reference

| Expression | Returns |
|------------|---------|
| `context.frame()` | Current `Frame*` |
| `context.frame()->getOperandStack()` | `OperandStack*` |
| `context.frame()->getLocalVariables()` | `LocalVariables*` |
| `context.frame()->getRuntimeConstantPool()` | `const ConstantPool*` |
| `context.getMethod()` | `const VmMethod*` (current method being executed) |
| `context.getJVM()` | `VirtualMachine*` |
| `context.getStack()` | `VmStack*` |
| `context.previousFrame()` | Caller's `Frame*` |
| `instruction->getOpcode()` | `Mnemonic` enum value |
| `instruction->getOprand(i)` | Operand byte at index i |
| `instruction->getOprandAsU2()` | Two operand bytes as big-endian u2 |
| `instruction->getByteOffset()` | Byte offset of this instruction in the method |
| `Interpreter::lookupField(context, cpIndex)` | Resolve field reference from constant pool |
| `Interpreter::lookupMethod(context, cpIndex)` | Resolve method reference from constant pool |
| `stack->pushInt(val)` / `popInt()` | Push/pop 32-bit integer |
| `stack->pushLong(val)` / `popLong()` | Push/pop 64-bit long (2 positions) |
| `stack->pushReference(val)` / `popReference()` | Push/pop object reference (1 position) |
| `locals->setInt(i, val)` / `getInt(i)` | Get/set integer local variable |
| `locals->setReference(i, val)` / `getReference(i)` | Get/set reference local variable |

## Test Structure

Tests use Google Test (fetched via CMake FetchContent). Three categories:

1. **Format/parser tests** — parse `.class` files and verify structures
2. **Runtime unit tests** — test `OperandStack`, `LocalVariables`, `VmField`, `Heap`, etc.
3. **Interpreter tests** — instruction-level tests (construct `Instruction` objects, verify stack state) and execution tests (run Java methods end-to-end via `VirtualMachine::execute()`)

Java test fixtures are in `tests/res/`. They compile to `.class` files that the C++ tests load at runtime.
