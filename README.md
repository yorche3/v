# V

Proyectos en **V**, con scripts independientes ejecutados mediante `v run` o compilados a ejecutables nativos, y módulos tipo librería probados con el framework integrado de V (`v test` + `assert`).

---

## 📂 Módulos / Modules

| Módulo | Descripción |
| ------ | ----------- |
| [`core/foundations/`](core/foundations/) | **Fase 0 — Fundamentos**: `helloworld`, `hellouser`, `unit_test/calculator`, `numbers` |

---

## ▶️ Comenzar / Getting Started

```bash
# Cargar V desde la instalación de usuario
source "$HOME/.bashrc"

# Hello, World!
cd core/foundations/helloworld
v run hello_world.v

# Hello, User!
cd ../hellouser
printf 'Ada\n' | v run hello_user.v

# Calculator tests
cd ../unit_test/calculator
v test ./test

# Numbers tests
cd ../../numbers
v test ./test/recursive_test.v
v test ./test/iterative_test.v
```

---

## 📦 Requisitos / Requirements

| Herramienta | Uso | Verificación |
| ----------- | --- | ------------ |
| V 0.5.2 | Compilador y runtime | `v version` |
| `v test` | Framework de pruebas integrado | `v help test` |
| `assert` | Aserciones integradas | Incluido en V |

V está instalado en `$HOME/.local/share/vlang` y esa ruta se carga desde `.bashrc`:

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

## 🏗️ Tipos de proyecto / Project Types

### 1. Programa independiente (`v run` / compilación nativa)

**ES:** `helloworld` y `hellouser` son archivos `.v` ejecutados con `v run` o compilados directamente a binarios nativos con `v -o`.

**EN:** `helloworld` and `hellouser` are `.v` files run with `v run` or compiled directly into native binaries with `v -o`.

```bash
v run <File>.v
v -o <binary> <File>.v
./<binary>
```

### 2. Módulo V con pruebas

**ES:** `calculator` y `numbers` usan `v.mod`, `src/` y `test/`. V descubre archivos `_test.v` y funciones `test_*` automáticamente.

**EN:** `calculator` and `numbers` use `v.mod`, `src/`, and `test/`. V automatically discovers `_test.v` files and `test_*` functions.

```bash
v test ./test
```

---

## 🔁 Decisión de TCO / TCO Decision

V tiene iteración nativa mediante `for`, pero no ofrece una garantía general de Tail Call Optimization para estos módulos. Por eso `numbers` conserva `_acc` como puente educativo sin suite propia y prueba `_rec` e `_ite`:

V has native iteration through `for`, but does not provide a general Tail Call Optimization guarantee for these modules. Therefore `numbers` keeps `_acc` as an educational bridge without a dedicated suite and tests `_rec` and `_ite`:

```text
TCO no garantizada + iteración nativa ✅
_rec + _ite
2 suites
10 tests
22 casos
```

---

## 🧪 Convenciones de pruebas / Testing Conventions

**ES:** V usa su framework integrado: archivos con sufijo `_test.v`, funciones con prefijo `test_` y aserciones `assert`. `calculator` tiene 5 tests; `numbers` tiene 10 tests en 2 suites y 22 casos/assertions.

**EN:** V uses its built-in framework: files ending in `_test.v`, functions prefixed with `test_`, and `assert` expressions. `calculator` has 5 tests; `numbers` has 10 tests in 2 suites and 22 cases/assertions.

---

## 🧹 Artefactos de compilación / Build Artifacts

Los `.gitignore` locales excluyen los ejecutables generados por V (`hello_world`, `hello_user`, `calculator`, `numbers`), sus variantes Windows y artefactos nativos.

Local `.gitignore` files exclude V-generated executables (`hello_world`, `hello_user`, `calculator`, `numbers`), Windows variants, and native artifacts.

---

## 🌐 Otras implementaciones / Other implementations

Este proyecto también está implementado en otros lenguajes. Explora el [repositorio principal](https://github.com/yorche3/programming_languages) para ver todas las versiones.

---

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://github.com/yorche3/programming_languages)*