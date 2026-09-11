# Numbers — V

Implementación de la especificación [04_Numbers](https://yorche3.github.io/programming_languages/core/foundations/04_Numbers/) en **V**, usando una estructura tipo librería con `src/` y `test/`, y el framework de testing integrado de V (`v test` + `assert`).

No se requiere instalar una biblioteca externa ni usar `sudo`.

---

## 📂 Archivos y estructura / Files & Structure

| Archivo / Directorio | Propósito |
|----------------------|-----------|
| [`v.mod`](v.mod) | Manifiesto del módulo V. |
| [`src/numbers.v`](src/numbers.v) | Implementación de los 15 procedimientos. |
| [`test/recursive_test.v`](test/recursive_test.v) | Suite `_rec`: 5 tests y 11 assertions. |
| [`test/iterative_test.v`](test/iterative_test.v) | Suite `_ite`: 5 tests y 11 assertions. |
| [`.gitignore`](.gitignore) | Ignora ejecutables y artefactos nativos. |

```text
numbers/
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

## 🛠️ Enfoque y construcción / Approach & Build

**ES:** El proyecto se creó manualmente como un módulo V. El código de producción está separado en `src/` y las suites en `test/`. V descubre los archivos `_test.v` y las funciones `test_*` automáticamente.

**EN:** The project was created manually as a V module. Production code is separated under `src/`, and suites are under `test/`. V automatically discovers `_test.v` files and `test_*` functions.

Los cinco algoritmos tienen tres implementaciones:

| Enfoque | Sufijo | Ejemplo | ¿Tiene suite propia? |
|---------|--------|---------|:--------------------:|
| Recursivo directo | `_rec` | `fibonacci_rec` | Sí |
| Recursivo con acumulador | `_acc` | `fibonacci_acc` | No, por TCO no garantizada |
| Iterativo | `_ite` | `fibonacci_ite` | Sí |

**Combinación aplicada:** TCO no garantizada + iteración nativa (`for`) ✅ → `_rec` + `_ite` = **2 suites, 10 tests agrupados y 22 casos**.

**Applied combination:** No guaranteed TCO + native iteration (`for`) ✅ → `_rec` + `_ite` = **2 suites, 10 grouped tests, and 22 cases**.

### Inicialización / Initialization

```bash
mkdir -p v/core/foundations/numbers/{src,test}
cd v/core/foundations/numbers
v init
```

Después se añaden el módulo en `src/` y las suites en `test/`.

---

## 📄 Archivos de configuración clave / Key Configuration Files

### `v.mod`

```v
Module {
    name: 'numbers'
    version: '0.1.0'
    license: 'MIT'
    dependencies: []
}
```

El archivo `v.mod` identifica el paquete; `src/numbers.v` declara el módulo `src`, importado como `numbers.src` por las suites.

### Suites V

Cada suite contiene cinco funciones `test_*`, una por algoritmo, y agrupa dentro de ellas los casos de la especificación. V proporciona `assert` y el runner integrado.

Each suite contains five `test_*` functions, one per algorithm, grouping the specification cases inside each function. V provides `assert` and the built-in runner.

---

## 🚀 Compilación y ejecución / Build & Run

### Requisitos / Requirements

- **V 0.5.2**.
- Framework de testing integrado (`v test`).

Verificar:

```bash
v version
```

Salida verificada:

```text
V 0.5.2 76c0d94
```

### Ejecutar la suite recursiva / Run recursive suite

```bash
cd v/core/foundations/numbers
v test ./test/recursive_test.v
```

### Ejecutar la suite iterativa / Run iterative suite

```bash
cd v/core/foundations/numbers
v test ./test/iterative_test.v
```

### Salida esperada / Expected output

Cada suite debe finalizar con:

```text
Summary for all V _test.v files: 1 passed, 1 total.
```

La ejecución conjunta representa 22 casos/assertions aprobados y 0 fallos.

The combined execution represents 22 passed cases/assertions and 0 failures.

---

## 🧠 Operaciones / Operations

| Función | `_rec` | `_acc` | `_ite` |
|---------|--------|--------|--------|
| `sum_of_first_n` | Recursión directa | Helper con acumulador | `for` |
| `factorial` | Recursión directa | Helper con acumulador | `for` |
| `fibonacci` | Dos llamadas recursivas | Dos acumuladores | `for` |
| `greatest_common_divisor` | Euclides recursivo | Helper de Euclides | `for` |
| `least_common_multiple` | Usa MCD y aritmética | Usa MCD y aritmética | Usa MCD y aritmética |

---

## 📝 Notas de implementación / Implementation Notes

- **ES:** V tiene iteración nativa mediante `for`, por lo que `_ite` se implementa sin llamadas recursivas.
- **EN:** V has native iteration through `for`, so `_ite` is implemented without recursive calls.
- **ES:** V no ofrece una garantía general de TCO para este proyecto; `_acc` se conserva como puente didáctico sin suite propia.
- **EN:** V does not provide a general TCO guarantee for this project; `_acc` remains as an educational bridge without its own suite.
- **ES:** Vtest proporciona el runner y `assert`, por lo que no se añade una dependencia externa.
- **EN:** Vtest provides the runner and `assert`, so no external dependency is added.
- **ES:** Los ejecutables generados quedan excluidos por `.gitignore`.
- **EN:** Generated executables are excluded by `.gitignore`.
- **ES:** El código fuente no incluye comentarios inline; la explicación se mantiene en este README.
- **EN:** The source code contains no inline comments; explanations are kept in this README.

---

## 🌐 Otras implementaciones / Other implementations

Este proyecto también está implementado en otros lenguajes. Explora el [repositorio principal](https://github.com/yorche3/programming_languages) para ver todas las versiones.

---

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://github.com/yorche3/programming_languages)*
