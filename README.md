# SDML — Simple Direct Memory Language

SDML is a C-like systems programming language designed for simplicity, direct memory access, and predictable execution.

It aims to sit somewhere between C and modern systems languages, offering cleaner syntax while still allowing low-level control over memory and execution.

---

## Features (WIP)

- C-style syntax with cleaner structure
- Function-first design (no top-level executable code)
- Indentation-based blocks
- Class support (structured types)
- Pointers and direct memory access
- Multiple return values
- Planned: bytecode VM / native backend
- No mandatory memory allocation in user code (design goal)

---

## Example Syntax

### Functions

```sdml
func main(int: argc, *string: argv) -> int:
    if (argc > 1) do:
        return (1);

    return (0);
```

---

### Variables

```sdml
int: x = 10;
string: name = "SDML";
```

---

### Control Flow

```sdml
while (x > 0) do:
    x = x - 1;
```

---

### Classes

```sdml
class Foo:
    public:
        int: value;

    private:
        int: hidden;
```

---

## Design Goals

SDML is built around a few core ideas:

1. Simplicity
2. Direct Memory Access
3. Predictable Execution
4. Compiler-Friendly Design

---

## Project Structure (Planned)

```
src/
    lexer/
    parser/
    ast/
    semantic/
    vm/
    codegen/
    runtime/
```

---

## Current Status

Early development.

Planned milestones:

- Lexer implementation
- Parser implementation
- AST generation
- Semantic analysis
- Bytecode VM or LLVM backend
- First executable programs

---

## License

MIT (recommended)

---

## Why SDML?

SDML aims to be:

- simpler than C
- more structured than C
- still fully low-level
- easy to compile and reason about
