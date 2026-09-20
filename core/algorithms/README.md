# 🚀 Algoritmos Puros / Algorithms Pure — V

Implementaciones de la [Fase 1 — Algoritmos Puros](https://yorche3.github.io/programming_languages/ROADMAP/#fase-1--algoritmos-puros--algorithms-pure-) en **V**: ordenamientos elementales, estructuras de datos propias, ordenamientos óptimos y distribuidos, y búsqueda.

Los módulos de esta fase trabajan sobre **arrays de valor** (`[]int`): reciben el array por valor, ordenan una copia local y devuelven el array ordenado. `[]int` no admite `null`, así que el caso nulo no es representable en la firma.

---

## 📂 Módulos / Modules

| Módulo | Especificación | Enfoque | Tests | Estado |
|--------|---------------|---------|:-----:|:------:|
| [`naive_sort/`](naive_sort/) | [05_Naive_Sort](https://yorche3.github.io/programming_languages/core/algorithms/05_Naive_Sort/) | `v test .` (framework integrado) | 21 | ✅ |

---

## 📁 Estructura / Structure

```text
algorithms/
└── naive_sort/                  # 05_Naive_Sort
    ├── v.mod                    # Manifiesto del módulo: name 'naive_sort'
    ├── .gitignore               # Ejecutable compilado y artefactos nativos
    ├── src/
    │   └── naive_sort.v         # module src: 3 funciones públicas
    ├── test/
    │   └── naive_sort_test.v    # 3 funciones test_* × 7 casos
    └── README.md
```

---

## 🛠️ Patrón común / Common Pattern

| Característica | Descripción |
|---------------|-------------|
| **Runtime** | V 0.5.2, instalado en `$HOME/.local/share/vlang` y cargado desde `.bashrc` |
| **CLI** | `v test .`, ejecutado desde la raíz del módulo |
| **Andamiaje** | ✍️ Estructura manual (`mkdir -p src test` + `v.mod`), la que ya usa [`foundations/numbers/`](../foundations/numbers/) |
| **Framework de tests** | El integrado de V: archivos `_test.v`, funciones `test_*` y `assert` |
| **Runner** | `v test .` descubre los `_test.v`; no hay `run_tests.v` |
| **Separación** | `src/` (módulo `src`) ↔ `test/` (suites) |
| **Módulo fuente** | Un archivo `src/<modulo>.v` con `module src` y funciones `pub fn`, como `numbers.v` |
| **API** | Una función por algoritmo: `src.selection_sort(arr)`, etc. |
| **Naming** | `snake_case` idéntico al de la especificación (`selection_sort`), como en los otros módulos V del repositorio |
| **Semántica de valor** | Los arrays son valores: la función recibe `arr` y ordena una copia mutable `result` (`arr.clone()`), devolviendo el array ordenado |
| **Nulabilidad** | `[]int` no admite `null` (los opcionales `?[]int` llegan en una fase posterior): el caso nulo no es representable y se omite |
| **Mensajes de aserción** | `assert cond, 'mensaje'`: V **sí** admite mensaje, con el formato `"{algorithm} should sort {caso}"` |
| **Verificación estática** | La propia compilación de `v test .`, sin warnings ni errores |
| **Artefactos** | Ejecutable del módulo (`naive_sort`, `naive_sort.exe`) y objetos nativos (`*.out`, `*.o`, `*.so`, `*.dylib`, `*.dll`) — ignorados por el `.gitignore` |
| **Particularidades** | El parámetro no puede redeclararse con `:=` (`error: redefinition of 'array'`): parámetro `arr` y copia `result`; rangos semiabiertos `0 .. n - 1`; intercambio con asignación doble `a, b = b, a`; constantes vacías con tipo explícito (`[]int{}`) |

---

## 🚀 Compilación rápida / Quick Build

```bash
# Naive Sort Tests
cd naive_sort
v test .
```

---

## ▶️ Siguiente / Next

👉 Continúa con los módulos pendientes de esta fase en el [Roadmap](https://yorche3.github.io/programming_languages/ROADMAP/).

👉 Continue with the pending modules of this phase in the [Roadmap](https://yorche3.github.io/programming_languages/ROADMAP/).

---

*[← Volver a Core](../README.md)*

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://yorche3.github.io/programming_languages/)*
