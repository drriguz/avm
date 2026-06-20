# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**avm** is a simple JVM (Java Virtual Machine) written in C++11. It parses Java `.class` files and interprets bytecode. The project is under active development — the class file parser is relatively complete, but the interpreter only implements a subset of JVM opcodes (many throw `UnsupportedInstructionException`).

## Build Commands

```bash
mkdir build && cd build
cmake ../
make
```

This produces four targets: `class_file` (static lib), `vm` (static lib), `avm_cli` (executable), and `tests` (executable). Test resources (`.class` files) are copied into the build directory as a post-build step.

## Running Tests

```bash
cd build
./tests
```

Tests use bundled Google Test 1.8.0. Run a single test by name:

```bash
./tests --gtest_filter="TestSuiteName.TestName"
```

To regenerate test resource `.class` files, run `tests/res/compile.sh` (requires `javac`).

## Code Formatting

```bash
./format.sh
```

Uses `astyle` with Java-style formatting on all `.cpp` and `.h` files.

## Architecture

The project is split into two static libraries and one CLI executable, built in dependency order:

### `class_file` library — Class file parsing

Parses `.class` files per the JVM spec into in-memory structures. Key classes:
- `JavaClassParser` reads bytes via `BinaryReader`/`FileReader` and builds a `JavaClass`
- `ConstantPool` holds all 17 JVM constant types
- `MethodInfo` / `FieldInfo` represent class members with their attributes
- `Instruction` represents a single bytecode opcode with operands
- `FieldType` hierarchy (`BaseType`, `ObjectType`, `ArrayType`) parses JVM type descriptors

Headers are in `class_file/include/class_file/{format,parser,helper}/`, implementations in `class_file/src/`.

### `vm` library — Runtime and execution engine (depends on `class_file`)

Three subsystems:

**Class Loading:** `ClassLoader` (abstract) → `ClasspathClassLoader` reads from filesystem. `VmClass` wraps `JavaClass` with runtime state (superclass links, field offsets, method registration). `MethodArea` is the loaded-class registry.

**Memory:** `Heap` is a 10 MB bump-allocator. `Frame` holds `OperandStack` + `LocalVariables` + constant pool ref. `VmStack` is the JVM call stack of frames. `Slot` is `uint64_t` (64-bit) or `uint32_t` (32-bit); `reference` is a typedef for `Slot`.

**Execution:** `VirtualMachine` coordinates class loader, heap, method area, and main thread. `VmThread` owns a `VmStack` and delegates to `Interpreter`. The `Interpreter` dispatches via a function pointer table (`invoke_mapping[]`) indexed by opcode, with handler functions split across 11 files by instruction category in `vm/src/interpreter/`.

Headers are in `vm/include/vm/` and `vm/include/vm/runtime/`, implementations in `vm/src/`.

### `avm_cli` — Entry point (depends on both libraries)

Accepts `-classpath <path> <mainClass>`. Currently a stub that parses arguments but doesn't invoke the VM.

### `tests` — Test suite

21 test files organized to mirror the library structure under `tests/src/`. Test `.class` fixtures and their Java sources are in `tests/res/`.

## Interpreter Implementation Status

When implementing new bytecode instructions, add the handler function in the appropriate category file under `vm/src/interpreter/`, then register it in the `invoke_mapping[]` table. Most unimplemented opcodes throw `UnsupportedInstructionException`.

**Implemented:** constants (`iconst_*`, `aconst_null`, `bipush`, `sipush`, `ldc`/`ldc_w`/`ldc2_w`, `lconst_*`, `fconst_*`, `dconst_*`), all loads/stores (generic indexed + `_0`..`_3` variants for all types), stack ops (`pop`, `pop2`, `dup*`, `swap`), integer/long/float/double math, all type conversions, comparisons (`lcmp`, `fcmpl/g`, `dcmpl/g`), conditional branches (`ifeq`/`ifne`/`iflt`/`ifge`/`ifgt`/`ifle`, `if_icmp*`, `if_acmp*`, `ifnull`/`ifnonnull`), control flow (`goto`, `ireturn`/`lreturn`/`freturn`/`dreturn`/`areturn`/`return`), references (`getstatic`/`putstatic`, `getfield`/`putfield`, `new`, `invokestatic`/`invokevirtual`/`invokespecial`/`invokeinterface`, `checkcast`, `instanceof`, `monitorenter`/`monitorexit`), and `println(int)` as a native.

**Still stubs:** array ops (`newarray`/`anewarray`/`arraylength`/`multianewarray`, all `*aload`/`*astore`), `athrow` (exception handling), `wide`, `tableswitch`/`lookupswitch`, `goto_w`, `jsr`/`ret`/`jsr_w`, `invokedynamic`.

**x64 considerations:** On 64-bit platforms, `SLOT` is `uint64_t`. The `maxStack` and `maxLocals` from class files are in 32-bit JVM slots, so they are doubled on x64 when creating frames. References are stored as full 64-bit pointers in a single SLOT. The `Instruction` class stores `_byteOffset` for correct branch target calculation (bytecode offsets differ from instruction indices since multi-byte instructions occupy one slot in the vector).

**Branch target calculation:** Branch handlers must use `instruction->getByteOffset()` to compute the target byte offset, then `context.getMethod()->getInstructionIndexAtByteOffset()` to find the target instruction index. Setting `frame->setPc(targetIdx)` makes `getNextPc()` return `targetIdx` and increment to `targetIdx+1`.

**Object initialization:** `invokespecial` for `java/lang/Object.<init>` is skipped to prevent infinite recursion (the stub Object constructor calls itself). The objectref is still popped from the caller's stack.
