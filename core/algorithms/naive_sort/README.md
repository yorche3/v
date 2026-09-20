# Naive Sort — V

Implementación de la especificación [05_Naive_Sort](https://yorche3.github.io/programming_languages/core/algorithms/05_Naive_Sort/) en **V**, usando una estructura tipo librería con `src/` y `test/`, y el framework de testing integrado de V (`v test` + `assert`).

Los tres algoritmos elementales de ordenamiento $O(n^2)$ — **selection sort**, **bubble sort** e **insertion sort** — reciben el array por valor, ordenan una copia local y devuelven el array ordenado, sin invocar `sort` ni ninguna otra ayuda de ordenamiento de la biblioteca estándar.

---

## 📂 Archivos y estructura / Files & Structure

| Archivo / Directorio | Propósito |
|----------------------|-----------|
| [`v.mod`](v.mod) | Manifiesto del módulo V. |
| [`src/naive_sort.v`](src/naive_sort.v) | Módulo `src` con las 3 funciones públicas. |
| [`test/naive_sort_test.v`](test/naive_sort_test.v) | Suite integrada: 3 funciones `test_*` × 7 casos. |
| [`.gitignore`](.gitignore) | Ignora el ejecutable compilado y artefactos nativos. |

```text
naive_sort/
├── v.mod
├── src/
│   └── naive_sort.v          # module src: 3 algoritmos
├── test/
│   └── naive_sort_test.v     # 3 tests × 7 casos
├── .gitignore
└── README.md
```

---

## 🛠️ Enfoque y construcción / Approach & Build

**ES:** El proyecto se creó manualmente como un módulo V, igual que `core/foundations/numbers/`: manifiesto `v.mod`, código de producción en `src/` y suites en `test/`. V descubre los archivos `_test.v` y las funciones `test_*` automáticamente, así que no hay runner propio ni `main`.

**EN:** The project was created by hand as a V module, like `core/foundations/numbers/`: `v.mod` manifest, production code under `src/`, and suites under `test/`. V automatically discovers `_test.v` files and `test_*` functions, so there is no custom runner or `main`.

### Inicialización / Initialization

```bash
mkdir -p v/core/algorithms/naive_sort/{src,test}
cd v/core/algorithms/naive_sort
# Escribir v.mod, src/naive_sort.v y test/naive_sort_test.v
```

---

## 📄 Configuración clave / Key Configuration

### `v.mod` — manifiesto del módulo

```v
Module {
    name: 'naive_sort'
    version: '0.1.0'
    license: 'MIT'
    dependencies: []
}
```

**ES:** El nombre del módulo es el que usan las suites para importarlo (`import naive_sort.src`), y V resuelve esa ruta por el nombre del directorio del módulo.

**EN:** The module name is what the suites use to import it (`import naive_sort.src`), and V resolves that path through the module directory name.

### `src/naive_sort.v` — contrato e implementación

**ES:** Las tres funciones reciben el array por valor (`arr`), ordenan una copia mutable (`result`) y la devuelven. Con menos de dos elementos el array vuelve sin cambios y ninguna función lanza excepciones.

**EN:** All three functions take the array by value (`arr`), sort a mutable copy (`result`), and return it. With fewer than two elements the array is returned unchanged and no function throws.

```v
module src

pub fn selection_sort(arr []int) []int {
	mut result := arr.clone()
	n := result.len
	if n < 2 {
		return result
	}
	for i in 0 .. n - 1 {
		mut min_index := i
		for j in i + 1 .. n {
			if result[j] < result[min_index] {
				min_index = j
			}
		}
		if min_index != i {
			result[i], result[min_index] = result[min_index], result[i]
		}
	}
	return result
}
```

| Elemento del contrato | Representación en V |
| --------------------- | ------------------- |
| Array de enteros | `[]int` (índices 0-based) |
| Caso nulo / inválido | Omitido: `[]int` es un tipo de valor y no admite `null` |
| Array vacío | `[]int{}` (`len == 0`) |
| Orden | sobre una copia local, devuelve un array nuevo ordenado |
| Nombres de la especificación | `selection_sort`, `bubble_sort`, `insertion_sort` (snake_case, idénticos a la especificación y a `numbers/`) |

### Suite de pruebas / Test suite

**ES:** La suite usa el framework integrado: constantes con los fixtures, una tabla de `SortCase`, un helper compartido que recibe el nombre del algoritmo y la función a probar, y una función `test_*` por algoritmo. Cada caso ordena una copia (`clone()`), porque el orden es *in-place* dentro de la función.

**EN:** The suite uses the built-in framework: fixture constants, a `SortCase` table, a shared helper that receives the algorithm name and the function under test, and one `test_*` function per algorithm. Each case sorts a `clone()` copy, because sorting is *in-place* inside the function.

```v
fn assert_sorts_all_cases(algorithm string, sort fn ([]int) []int) {
	cases := [
		SortCase{'an unsorted array', standard_input, standard_output},
		// …
	]

	for test_case in cases {
		assert sort(test_case.input.clone()) == test_case.expected, '${algorithm} should sort ${test_case.description}'
	}
}
```

---

## 🚀 Compilación y ejecución / Build & Run

### Requisitos / Requirements

- **V 0.5.2**; en este entorno está instalado en `$HOME/.local/share/vlang` y se carga desde `.bashrc`.

```bash
source "$HOME/.bashrc"
v version
```

### Ejecutar las pruebas / Run tests

```bash
cd v/core/algorithms/naive_sort
v test .
```

**Salida real / Actual output:**

```text
$ v version
V 0.5.2 76c0d94
```

```text
$ v test .
---- Testing... ----------------------------------------------------------------
OK       2.319 ms /home/yorche3/programming_languages/v/core/algorithms/naive_sort/test/naive_sort_test.v
--------------------------------------------------------------------------------
Summary for all V _test.v files: 1 passed, 1 total. Elapsed time: 3438 ms, on 1 job. Comptime: 3432 ms. Runtime: 2 ms.
```

> **ES:** `v test .` compila el módulo y la suite sin warnings ni errores (la compilación es la verificación estática de V) y el resumen cuenta **archivos de test**, no aserciones: hay 1 archivo con 3 funciones `test_*`, y cada una ejecuta los 7 casos de la tabla (21 aserciones). Un `assert` fallido imprime el mensaje del contrato.
> **EN:** `v test .` compiles the module and the suite with no warnings or errors (compilation is V's static check) and the summary counts **test files**, not assertions: there is 1 file with 3 `test_*` functions, each running the 7 cases of the table (21 assertions). A failing `assert` prints the contract message.

---

## 🧠 Algoritmos y operaciones / Algorithms & Operations

| Función / Algorithm | Enfoque / Approach | Descripción / Description |
| ------------------- | ------------------ | ------------------------- |
| `selection_sort(arr)` | iterativo, con intercambio doble | Busca el mínimo del tramo no ordenado con `min_index` y lo intercambia al inicio con `result[i], result[min_index] = result[min_index], result[i]`. $O(n^2)$ siempre. |
| `bubble_sort(arr)` | iterativo, con bandera | Compara adyacentes e intercambia; sale antes con `if !swapped { break }` cuando una pasada no intercambia nada. $O(n^2)$ peor/promedio, $O(n)$ mejor. |
| `insertion_sort(arr)` | iterativo, estable | Guarda `key`, desplaza el sub-array ordenado con `for j >= 0 && result[j] > key` y lo inserta en su posición. $O(n^2)$ peor/promedio, $O(n)$ mejor. |

| Caso (descripción en la suite) | Entrada | Salida esperada |
| ------------------------------ | ------- | --------------- |
| an unsorted array | `[5, 2, 9, 1, 5, 6]` | `[1, 2, 5, 5, 6, 9]` |
| an already sorted array | `[1, 2, 3, 4, 5]` | `[1, 2, 3, 4, 5]` |
| a reverse ordered array | `[5, 4, 3, 2, 1]` | `[1, 2, 3, 4, 5]` |
| an array of identical elements | `[7, 7, 7, 7]` | `[7, 7, 7, 7]` |
| an array with negative numbers | `[3, -1, 4, -5, 0]` | `[-5, -1, 0, 3, 4]` |
| a single element array | `[42]` | `[42]` |
| an empty array | `[]` | `[]` |

---

## 📝 Notas de implementación / Implementation Notes

- **ES:** Divergencia idiomática aceptada: las funciones reciben el array por valor y trabajan sobre una copia mutable (`mut result := arr.clone()`), devolviendo un array nuevo ordenado, variante que la especificación permite («in-place o retornando una copia ordenada»). Los arrays de V son valores, así que los fixtures de la suite no se contaminan aunque la función reordene su copia.
- **EN:** Accepted idiomatic divergence: the functions take the array by value and work on a mutable copy (`mut result := arr.clone()`), returning a new sorted array, a variant the specification allows ("in-place or returning a sorted copy"). V arrays are values, so the suite fixtures are not polluted even though the function reorders its copy.
- **ES:** Caso nulo omitido: en V `[]int` es un tipo de valor y no admite `null`; los opcionales (`?[]int`) se formalizan más adelante, en la fase de abstracción y persistencia, así que no hay indicador de fallo que comprobar. Se conservan los 7 casos de la especificación. Ninguna función lanza excepciones.
- **EN:** Null case omitted: in V `[]int` is a value type and does not admit `null`; optionals (`?[]int`) are formalized later, in the abstraction and persistence phase, so there is no failure indicator to check. The 7 cases of the specification are kept. No function throws.
- **ES:** En V el parámetro no se puede redeclarar con `:=` en el mismo ámbito (`error: redefinition of 'array'`), así que la copia mutable lleva otro nombre: parámetro `arr` y copia `result`.
- **EN:** In V a parameter cannot be redeclared with `:=` in the same scope (`error: redefinition of 'array'`), so the mutable copy uses a different name: parameter `arr` and copy `result`.
- **ES:** `bubble_sort` conserva la optimización de salida temprana: la bandera `swapped` y `if !swapped { break }` reproducen el `if not swapped: break` del pseudocódigo (mejor caso $O(n)$). La bandera no es observable en la salida, así que su presencia se verifica contra el pseudocódigo.
- **EN:** `bubble_sort` keeps the early-exit optimization: the `swapped` flag and `if !swapped { break }` reproduce the pseudocode's `if not swapped: break` (best case $O(n)$). The flag is not observable in the output, so its presence is verified against the pseudocode.
- **ES:** Los bucles del pseudocódigo se traducen a rangos semiabiertos de V: `0 .. n - 1` y `i + 1 .. n` en `selection_sort`, y `0 .. n - 1 - i` en el bucle interior de `bubble_sort` (el equivalente exacto de `for j = 0 to n - 2 - i`).
- **EN:** The pseudocode loops translate to V's half-open ranges: `0 .. n - 1` and `i + 1 .. n` in `selection_sort`, and `0 .. n - 1 - i` in the inner loop of `bubble_sort` (the exact equivalent of `for j = 0 to n - 2 - i`).
- **ES:** `insertion_sort` traduce el `while j >= 0 and arr[j] > key` del pseudocódigo literalmente (`for j >= 0 && result[j] > key`) sobre la copia local; la comparación estricta lo mantiene estable. El único intercambio es la asignación doble `result[i], result[min_index] = result[min_index], result[i]`.
- **EN:** `insertion_sort` translates the pseudocode's `while j >= 0 and arr[j] > key` literally (`for j >= 0 && result[j] > key`) over the local copy; the strict comparison keeps it stable. The only swap is the double assignment `result[i], result[min_index] = result[min_index], result[i]`.
- **ES:** A diferencia de Jest, `assert` de V **sí** acepta un mensaje (`assert cond, 'mensaje'`), así que el mensaje del contrato viaja en cada aserción y aparece en el reporte de fallo.
- **EN:** Unlike Jest, V's `assert` **does** accept a message (`assert cond, 'message'`), so the contract message travels in each assertion and shows up in the failure report.
- **ES:** Nota de desviación respecto a la ubicación esperada: se conservan `src/naive_sort.v` (solo cambia la extensión), `test/naive_sort_test.v` (sufijo `_test.v` que V descubre automáticamente, como en `numbers/`) y el manifiesto `v.mod` que pide la guía; no se añade `run_tests.v` porque `v test .` es el runner. Las constantes vacías exigen tipo explícito (`[]int{}`).
- **EN:** Deviation note from the expected location: `src/naive_sort.v` (only the extension changes), `test/naive_sort_test.v` (the `_test.v` suffix V discovers automatically, as in `numbers/`), and the `v.mod` manifest required by the guide are kept; no `run_tests.v` is added because `v test .` is the runner. Empty constants require an explicit type (`[]int{}`).

---

## 🌐 Otras implementaciones / Other implementations

Este proyecto también está implementado en otros lenguajes. Explora el [repositorio principal](https://github.com/yorche3/programming_languages) para ver todas las versiones.

---

*[← Volver a Algoritmos Puros](../README.md)*

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://yorche3.github.io/programming_languages/)*
