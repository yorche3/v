# 🚀 Fundamentos / Foundations — V

Implementación de los ejercicios de la sección [Fundamentos / Foundations](https://yorche3.github.io/programming_languages/core/foundations/) del repositorio principal en **V**.

---

## 📖 Descripción / Description

**ES:** Esta sección introduce V mediante scripts independientes y módulos tipo librería con pruebas unitarias usando el framework integrado de V (`v test` + `assert`).

**EN:** This section introduces V through standalone scripts and library-style modules with unit tests using V's built-in framework (`v test` + `assert`).

---

## 📁 Estructura / Structure

```text
v/
└── core/
    └── foundations/
        ├── README.md                   # Este archivo / This file
        ├── helloworld/                 # 01_Hello_World
        │   ├── hello_world.v
        │   ├── .gitignore
        │   └── README.md
        ├── hellouser/                  # 02_Hello_User
        │   ├── hello_user.v
        │   ├── .gitignore
        │   └── README.md
        ├── unit_test/
        │   └── calculator/             # 03_Unit_Test_Calculator
        │       ├── v.mod
        │       ├── src/
        │       │   └── calculator.v
        │       ├── test/
        │       │   └── calculator_test.v
        │       ├── .gitignore
        │       └── README.md
        └── numbers/                    # 04_Numbers
            ├── v.mod
            ├── src/
            │   └── numbers.v
            ├── test/
            │   ├── recursive_test.v
            │   └── iterative_test.v
            ├── .gitignore
            └── README.md
```

---

## 🔢 Progresión / Progression

| Especificación | Proyecto | Conceptos | Tests | Dependencias |
| -------------- | -------- | --------- | :---: | ------------ |
| [`01_Hello_World`](https://yorche3.github.io/programming_languages/core/foundations/01_Hello_World/) | [`helloworld/`](helloworld/) | `println`, código de nivel superior, `v run` | — | Solo V |
| [`02_Hello_User`](https://yorche3.github.io/programming_languages/core/foundations/02_Hello_User/) | [`hellouser/`](hellouser/) | `os.get_line`, `fn main`, interpolación | — | Solo V |
| [`03_Unit_Test_Calculator`](https://yorche3.github.io/programming_languages/core/foundations/03_Unit_Test_Calculator/) | [`unit_test/calculator/`](unit_test/calculator/) | módulos V, `v.mod`, `v test`, `assert` | 5 | Testing integrado |
| [`04_Numbers`](https://yorche3.github.io/programming_languages/core/foundations/04_Numbers/) | [`numbers/`](numbers/) | recursión, acumuladores, `for`, TCO | 10 (22 casos) | Testing integrado |

---

## 🛠️ Enfoque general / General Approach

**ES:** Los proyectos de esta sección siguen una progresión gradual:

1. **Hello World**: script V independiente ejecutado con `v run` o compilado a un ejecutable nativo.
2. **Hello User**: programa con `fn main`, entrada estándar mediante `os.get_line` e interpolación de cadenas.
3. **Calculator**: primer proyecto tipo librería con `v.mod`, `src/` y `test/`. Usa el framework integrado de V para validar cinco operaciones educativas.
4. **Numbers**: implementa cinco algoritmos en tres enfoques. V tiene iteración nativa mediante `for`, pero no ofrece una garantía general de TCO; por eso se prueban `_rec` e `_ite`, mientras `_acc` se conserva como puente didáctico sin suite propia.

**EN:** The projects in this section follow a gradual progression:

1. **Hello World**: standalone V script run with `v run` or compiled to a native executable.
2. **Hello User**: program with `fn main`, standard input through `os.get_line`, and string interpolation.
3. **Calculator**: the first library-style project with `v.mod`, `src/`, and `test/`. It uses V's built-in framework to validate five educational operations.
4. **Numbers**: implements five algorithms in three approaches. V has native iteration through `for`, but does not provide a general TCO guarantee; therefore `_rec` and `_ite` are tested, while `_acc` remains an educational bridge without its own suite.

---

## 📦 Requisitos / Requirements

| Herramienta | Uso | Verificación |
| ----------- | --- | ------------ |
| V 0.5.2 | Compilador y runtime | `v version` |
| `v test` | Framework de pruebas integrado | `v help test` |
| `assert` | Aserciones integradas | Incluido en V |

En este entorno V se instaló en `$HOME/.local/share/vlang` y esa ruta se añadió al `PATH` mediante `.bashrc`.

```bash
source "$HOME/.bashrc"
v version
```

Salida verificada:

```text
V 0.5.2 76c0d94
```

No se requiere instalar una biblioteca externa ni usar `sudo`.

---

## 🚀 Ejecución rápida / Quick Start

### Hello World

```bash
cd v/core/foundations/helloworld
v run hello_world.v
```

### Hello User

```bash
cd v/core/foundations/hellouser
printf 'Ada\n' | v run hello_user.v
```

### Calculator

```bash
cd v/core/foundations/unit_test/calculator
v test ./test
```

Resultado verificado:

```text
Summary for all V _test.v files: 1 passed, 1 total.
```

### Numbers

```bash
cd v/core/foundations/numbers
v test ./test/recursive_test.v
v test ./test/iterative_test.v
```

Resultados verificados:

```text
Summary for all V _test.v files: 1 passed, 1 total.
Summary for all V _test.v files: 1 passed, 1 total.
```

---

## 🧪 Convenciones de pruebas / Testing Conventions

**ES:** V descubre automáticamente los archivos que terminan en `_test.v` y las funciones que comienzan por `test_`. Las aserciones usan `assert` y no requieren un runner externo.

**EN:** V automatically discovers files ending in `_test.v` and functions beginning with `test_`. Assertions use `assert` and require no external runner.

`calculator` tiene 5 tests. `numbers` tiene 2 suites con 5 tests cada una y 22 casos/assertions en total.

`calculator` has 5 tests. `numbers` has 2 suites with 5 tests each and 22 total cases/assertions.

---

## 🔁 TCO e iteración / TCO and Iteration

V ofrece iteración nativa mediante `for`, pero no se documenta una garantía general de Tail Call Optimization para estos módulos. Según la regla de `04_Numbers`, la combinación aplicada es:

V provides native iteration through `for`, but no general Tail Call Optimization guarantee is documented for these modules. According to the `04_Numbers` rule, the applied combination is:

```text
TCO no garantizada + iteración nativa ✅
_rec + _ite
2 suites
10 tests
22 casos
```

La implementación `_acc` permanece en `numbers.v` como puente conceptual hacia `_ite`, pero no tiene una suite independiente.

The `_acc` implementation remains in `numbers.v` as a conceptual bridge toward `_ite`, but it has no independent suite.

---

## 🧹 Artefactos de compilación / Build Artifacts

Los `.gitignore` locales excluyen los ejecutables generados por V y otros artefactos nativos. Los scripts pueden ejecutarse con `v run` sin conservar un binario dentro del módulo.

Local `.gitignore` files exclude V-generated executables and other native artifacts. Scripts can run with `v run` without keeping a binary inside the module.

---

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://github.com/yorche3/programming_languages)*
