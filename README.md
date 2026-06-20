# avm

A simple JVM (Java Virtual Machine) written in C++11, targeting Java 1.4 class files.

[![Build & Test](https://github.com/drriguz/avm/actions/workflows/build.yml/badge.svg)](https://github.com/drriguz/avm/actions/workflows/build.yml)

## Building

Requires CMake 3.11+ and a C++11 compiler.

```bash
cmake -B build
cmake --build build
```

This produces:
- `class_file` — static library for `.class` file parsing
- `vm` — static library for the runtime and bytecode interpreter
- `avm_cli` — command-line executable
- `tests` — test suite (Google Test is fetched automatically via CMake FetchContent)

## Running Tests

```bash
cd build
./tests
```

Run a single test by name:

```bash
./tests --gtest_filter="TestSuiteName.TestName"
```

To regenerate test `.class` fixtures from Java sources:

```bash
tests/res/compile.sh
```

Requires `javac` on PATH.

## Usage

```
avm -classpath <path> <fully.qualified.MainClass>
```

- `-classpath` — directory containing `.class` files
- Main class — fully qualified class name with a `public static void main(String[])` method

**Note:** The CLI is currently a stub that parses arguments but does not invoke the VM.

## Architecture

See [docs/architecture.md](docs/architecture.md) for the full implementation guide.

The project is split into two static libraries:

**`class_file`** — Parses `.class` files per the JVM spec. Handles constant pool, fields, methods, attributes, and bytecode instructions. Headers in `class_file/include/`, sources in `class_file/src/`.

**`vm`** — The execution engine with three subsystems:
- **Class loading** — `ClassLoader` → `ClasspathClassLoader` reads from filesystem. `VmClass` wraps `JavaClass` with runtime state. `MethodArea` is the class registry.
- **Memory** — `Heap` (10 MB bump-allocator), `Frame` (operand stack + locals + constant pool), `VmStack` (call stack of frames).
- **Interpreter** — Dispatches opcodes via a function pointer table (`invoke_mapping[]`). Handler functions are split across 11 files by instruction category in `vm/src/interpreter/`.

## Interpreter Status

| Category | Status |
|----------|--------|
| Constants | `iconst_*`, `aconst_null`, `bipush`, `sipush`, `ldc`/`ldc_w`/`ldc2_w`, `lconst_*`, `fconst_*`, `dconst_*` |
| Loads/Stores | All generic indexed + `_0`..`_3` variants for int/long/float/double/reference |
| Stack | `pop`, `pop2`, `dup*`, `swap` |
| Math | Integer/long/float/double arithmetic, bitwise, shifts, `iinc` |
| Conversions | All 15 type conversions (`i2l`, `i2f`, `f2i`, etc.) |
| Comparisons | `lcmp`, `fcmpl`/`fcmpg`, `dcmpl`/`dcmpg` |
| Branches | `ifeq`/`ifne`/`iflt`/`ifge`/`ifgt`/`ifle`, `if_icmp*`, `if_acmp*`, `ifnull`/`ifnonnull` |
| Control | `goto`, all return variants (`ireturn` through `return`) |
| References | `getstatic`/`putstatic`, `getfield`/`putfield`, `new`, `invokestatic`/`invokevirtual`/`invokespecial`/`invokeinterface`, `checkcast`, `instanceof` |
| Native | `println(int)` (hardcoded) |

**Not yet implemented:** array operations, exception handling (`athrow`), `wide`, `tableswitch`/`lookupswitch`, `goto_w`, `jsr`/`ret`, `invokedynamic`, synchronization (`monitorenter`/`monitorexit` is no-op).

## License

See LICENSE file.
