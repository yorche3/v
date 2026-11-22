# Data Structures Advanced — V

Implementación de la especificación [07_Data_Structures_Advanced](https://yorche3.github.io/programming_languages/core/algorithms/07_Data_Structures_Advanced/) en **V**, usando estructuras enlazadas dinámicas sobre el heap (`TreeNode`, `BinaryTree`, `GraphNode`, `Graph`) con referencias opcionales y el framework de pruebas integrado de V (`v test`).

El módulo implementa manualmente un árbol binario de búsqueda (`BinaryTree`) sobre celdas `TreeNode` y un grafo dirigido (`Graph`) con registro enlazado canónico de vértices (`GraphNode`) y listas de adyacencia ordenadas crecientemente, respetando la prohibición de diccionarios, tablas hash y algoritmos de ordenación de biblioteca.

---

## 📂 Archivos y estructura / Files & Structure

Describe la estructura del proyecto y el propósito de cada archivo.

| Archivo / Directory | Propósito / Purpose |
|---|---|
| `src/data_structures_advanced.v` | Implementación del árbol binario de búsqueda y grafo dirigido (`TreeNode`, `BinaryTree`, `GraphNode`, `Graph`) / Source code for binary search tree and directed graph |
| `tests/data_structures_advanced_test.v` | Suite de pruebas unitarias integradas con 23 funciones `test_*` / Unit test suite covering all contract operations |
| `v.mod` | Manifiesto de metadatos del módulo V / V module manifest |
| `.gitignore` | Archivos generados y artefactos excluidos / Ignored generated files |
| `.editorconfig` | Configuración de formato y estilo de código / Editor formatting rules |
| `.gitattributes` | Atributos de control de versiones git / Git repository attributes |

```text
data_structures_advanced/
├── .editorconfig
├── .gitattributes
├── .gitignore
├── src/
│   └── data_structures_advanced.v
├── tests/
│   └── data_structures_advanced_test.v
├── v.mod
└── README.md
```

> **Nota de desviación de estructura / Layout deviation note:** La especificación sugiere `src/data_structures_advanced.ext` y `test/run_tests.ext`. Aquí el código fuente vive en `src/data_structures_advanced.v` —declara `module src` y es lo que verifica `v fmt -verify src`— y las pruebas en `tests/`, la carpeta estándar que crea `v init --lib`, con el sufijo `_test.v` que V descubre y `v test .` como runner integrado nativo, sin `run_tests` manual.

---

## 🛠️ Enfoque y construcción / Approach & Build

**ES:** El proyecto se construyó de forma manual como un paquete V autónomo. Las celdas `TreeNode` y `GraphNode` están anotadas con `@[heap]` para permitir la asignación dinámica de nodos enlazados mediante punteros de referencia opcionales (`?&TreeNode`, `?&GraphNode`), utilizando el valor nativo `none` para representar la ausencia de enlace. Al carecer V de herencia de tipos o structs, se emplea el modelo de valor embebido (`value int`) con validaciones encapsuladas en cada estructura derivada. El registro global de vértices se construye manualmente mediante un encadenamiento lineal (`next_vertex ?&GraphNode`), y la adyacencia de cada vértice mantiene sus etiquetas ordenadas ascendentemente mediante inserción ordenada manual en $O(d(u))$, sin delegar en `map`, `set` ni funciones de ordenación de la biblioteca estándar.

**EN:** The project was built manually as an autonomous V package. The `TreeNode` and `GraphNode` cells are annotated with `@[heap]` to enable dynamic heap allocation of linked nodes via optional reference pointers (`?&TreeNode`, `?&GraphNode`), using the native `none` value to represent absence of a link. Because V lacks struct inheritance, the embedded value pattern (`value int`) is used with validations encapsulated in each derived structure. The global vertex registry is built manually through a linear chain (`next_vertex ?&GraphNode`), and each vertex's adjacency maintains its labels in ascending order via manual ordered insertion in $O(d(u))$, without delegating to `map`, `set`, or standard library sorting functions.

### Inicialización / Initialization

```bash
mkdir -p v/core/algorithms/data_structures_advanced/tests
cd v/core/algorithms/data_structures_advanced
v init
```

---

## 📄 Configuración clave / Key Configuration

### `v.mod`

```v
Module {
	name: 'data_structures_advanced'
	version: '0.1.0'
	license: 'MIT'
	dependencies: []
}
```

El manifiesto identifica el módulo local `data_structures_advanced`; el archivo fuente declara `module src` y la suite de pruebas lo importa con `import data_structures_advanced.src as ds`. Siguiendo el estándar de las bases de referencia `numbers` y `data_structures_basics`, la versión se fija en `0.1.0` bajo licencia `MIT`.

---

## 🚀 Compilación y ejecución / Build & Run

### Verificación estática / Static check

```bash
v -shared -check src/data_structures_advanced.v
```

### Ejecución de pruebas / Run tests

```bash
v test .
```

**Salida real / Actual output:**

```text
$ v -shared -check src/data_structures_advanced.v

$ v test .
---- Testing... ----------------------------------------------------------------
OK       2.809 ms ~/programming_languages/v/core/algorithms/data_structures_advanced/tests/data_structures_advanced_test.v
--------------------------------------------------------------------------------
Summary for all V _test.v files: 1 passed, 1 total. Elapsed time: 3266 ms, on 1 job. Comptime: 3260 ms. Runtime: 2 ms.
```

---

## 🧠 Algoritmos y operaciones / Algorithms & Operations

| Operación / Operation | Entrada → salida / Input → output | Complejidad / Complexity | Notas / Notes |
|---|---|---|---|
| `new_tree_node(value)` | `int → &TreeNode` | $O(1)$ | Construye un nodo de árbol en el heap con valor y ambos enlaces ausentes (`none`) |
| `TreeNode.value()` | `() → int` | $O(1)$ | Observador no mutante del valor entero contenido |
| `TreeNode.left()` | `() → ?&TreeNode` | $O(1)$ | Observador no mutante del puntero al subárbol izquierdo |
| `TreeNode.right()` | `() → ?&TreeNode` | $O(1)$ | Observador no mutante del puntero al subárbol derecho |
| `TreeNode.set_left(left)` | `?&TreeNode → ()` | $O(1)$ | Reasigna el enlace izquierdo (nodo o `none`) |
| `TreeNode.set_right(right)` | `?&TreeNode → ()` | $O(1)$ | Reasigna el enlace derecho (nodo o `none`) |
| `new_binary_tree()` | `() → &BinaryTree` | $O(1)$ | Inicializa un ABB vacío con raíz ausente (`none`) y tamaño 0 |
| `BinaryTree.is_empty()` | `() → bool` | $O(1)$ | Comprueba si el árbol carece de nodos (`count == 0`) |
| `BinaryTree.size()` | `() → int` | $O(1)$ | Consulta el contador interno `count` de valores distintos |
| `BinaryTree.insert(value)` | `int → bool` | $O(h)$ | Inserta iterativamente según la invariante del ABB; duplicados devuelven `true` sin aumentar tamaño |
| `BinaryTree.contains(value)` | `int → bool` | $O(h)$ | Búsqueda iterativa siguiendo la invariante del ABB; devuelve `true` si existe o `false` |
| `new_graph()` | `() → &Graph` | $O(1)$ | Inicializa un grafo vacío con registro ausente y contadores en 0 |
| `Graph.is_empty()` | `() → bool` | $O(1)$ | Comprueba si no hay vértices registrados (`vertex_total == 0`) |
| `Graph.vertex_count()` | `() → int` | $O(1)$ | Consulta la cantidad de vértices registrados |
| `Graph.edge_count()` | `() → int` | $O(1)$ | Consulta la cantidad de aristas dirigidas registradas |
| `Graph.add_vertex(label)` | `int → bool` | $O(V)$ | Registra explícitamente un vértice; duplicados devuelven `true` conservando adyacencias |
| `Graph.add_edge(u, v)` | `(int, int) → bool` | $O(V + d(u))$ | Añade la arista dirigida $u \to v$ en orden; falla (`false`) si falta un extremo; aristas o bucles repetidos devuelven `true` |
| `Graph.has_edge(u, v)` | `(int, int) → bool` | $O(V + d(u))$ | Comprueba la existencia de la arista dirigida $u \to v$ |
| `Graph.neighbors(u)` | `int → ([]int, bool)` | $O(V + d(u))$ | Devuelve una copia clonada e independiente de los vecinos ordenados y `true`; si $u$ no existe devuelve `([], false)` |

---

## 🧩 Decisiones de diseño / Design decisions

| Decisión / Decision | Alternativa considerada / Alternative | Razón / Reason |
|---|---|---|
| Atributo `@[heap]` en `TreeNode` y `GraphNode` | Almacenamiento directo en el stack | V exige `@[heap]` en tipos autorreferenciados o que contienen referencias mutables opcionales para evitar punteros colgantes |
| Valor embebido (`value int`) en nodos | Herencia de clases o tipos base | V no soporta herencia de structs; la composición con campo de valor directo cumple el contrato manteniendo aislamiento de validaciones |
| Punteros opcionales nativos (`?&TreeNode`, `?&GraphNode`) | Punteros crudos o índices enteros sobre arrays | `?&T` con `none` es el mecanismo seguro e idiomático de V para referencias anulables sin recurrir a memoria insegura |
| Registro canónico lineal de vértices | Diccionarios o tablas hash (`map[int]&GraphNode`) | El contrato prohíbe delegar el registro de vértices en mapas o árboles de biblioteca; el recorrido lineal garantiza fidelidad conceptual |
| Inserción ordenada manual en adyacencia | Inserción al final seguida de `sort()` de biblioteca | La búsqueda de posición e inserción ordenada en $O(d(u))$ cumple el mandato de implementar algoritmos manuales sin dependencias de alto nivel |
| Clonación explícita en `neighbors(u)` (`clone()`) | Devolución de la referencia al slice interno | Asegura el aislamiento del resultado frente a mutaciones externas o adiciones posteriores de aristas al grafo |

---

## 🔀 Adaptaciones idiomáticas / Idiomatic adaptations

| Especificación / Specification | Adaptación / Adaptation | Justificación / Justification |
|---|---|---|
| `init(value)` / `init()` constructores | Funciones factoría `new_tree_node`, `new_binary_tree`, `new_graph` | V utiliza `new_*` como convención estándar para constructores que inicializan referencias |
| `Node` base por herencia | Valor embebido (`value int`) en `TreeNode` y `GraphNode` | V carece de herencia; la composición embebida satisface el requisito de nodo base portador del valor |
| Getters `get_value()`, `get_left()`, `get_right()`, `get_neighbors()` | Métodos receptores `value()`, `left()`, `right()`, `neighbors()` | El estilo idiomático de V descarta el prefijo `get_` en métodos observadores |
| Indicador de fallo en `get_neighbors(u)` | Tupla de retorno `([]int, bool)` | Permite distinguir inequívocamente un vértice aislado (`[], true`) de un vértice inexistente (`[], false`) sin inventar centinelas |
| Representación de ausencia en enlaces | `none` sobre referencias opcionales `?&TreeNode` y `?&GraphNode` | Mecanismo idiomático y nativo en V para modelar ausencia de puntero |
| Ubicación sugerida `src/` y `test/run_tests.ext` | `src/data_structures_advanced.v` (`module src`) y `tests/` con runner `v test .` | Alineado con el layout estándar de paquetes V, el verificador `v fmt -verify` y las bases homologadas del proyecto |
| Variante inmutable de `TreeNode` | Omitida / No aplicable | En V los structs mutan en sitio con receptores mutables (`mut node TreeNode`); no existe variante inmutable separada |
| Caso nulo en enteros | No representable | `int` en V es un tipo de valor primitivo no anulable; no admite valores nulos |

---

## 🚨 Indicadores de fallo / Failure indicators

| Operación / Operation | Situación de fallo / Failure situation | Indicador / Indicator | Ejemplo / Example |
|---|---|---|---|
| `TreeNode.left()` | Subárbol izquierdo ausente | `none` | `new_tree_node(10).left() == none` |
| `TreeNode.right()` | Subárbol derecho ausente | `none` | `new_tree_node(10).right() == none` |
| `BinaryTree.contains(value)` | Valor ausente en el árbol | `false` | `new_binary_tree().contains(50) == false` |
| `Graph.add_edge(u, v)` | Extremo `u` o `v` inexistente en el grafo | `false` | `new_graph().add_edge(10, 99) == false` |
| `Graph.has_edge(u, v)` | Arista ausente o extremo no registrado | `false` | `new_graph().has_edge(10, 30) == false` |
| `Graph.neighbors(u)` | Vértice `u` no registrado en el grafo | `([], false)` | `_, ok := new_graph().neighbors(99); !ok` |
| Valor entero `null` / inválido | Entrada nula sobre tipo entero `int` | No representable | En V los enteros son tipos primitivos por valor no anulables |

---

## ✅ Cobertura de pruebas / Test coverage

| Caso de la especificación / Specification case | Cubierto / Covered | Prueba / Test | Notas / Notes |
|---|---|:--:|---|
| `TreeNode`: Crear un nodo de árbol | Sí | `tests/data_structures_advanced_test.v:67` (`test_tree_node_create`) | `TreeNode` / mutación en sitio → inicialización y valor → grupo `TreeNode` → `tests/data_structures_advanced_test.v` → `v test .` |
| `TreeNode`: Enlaces iniciales ausentes | Sí | `tests/data_structures_advanced_test.v:72` (`test_tree_node_initial_links_absent`) | `TreeNode` / mutación en sitio → ausencia inicial de hijos → grupo `TreeNode` → `tests/data_structures_advanced_test.v` → `v test .` |
| `TreeNode`: Enlazar dos hijos | Sí | `tests/data_structures_advanced_test.v:78` (`test_tree_node_link_two_children`) | `TreeNode` / mutación en sitio → enlace de hijos izquierdo y derecho → grupo `TreeNode` → `tests/data_structures_advanced_test.v` → `v test .` |
| `TreeNode`: Recorrer cada enlace | Sí | `tests/data_structures_advanced_test.v:92` (`test_tree_node_traverse_each_link`) | `TreeNode` / mutación en sitio → recorrido y verificación de ausencia en hojas → grupo `TreeNode` → `tests/data_structures_advanced_test.v` → `v test .` |
| `TreeNode`: Desenlazar hijos | Sí | `tests/data_structures_advanced_test.v:108` (`test_tree_node_unlink_children`) | `TreeNode` / mutación en sitio → reasignación a `none` y conservación → grupo `TreeNode` → `tests/data_structures_advanced_test.v` → `v test .` |
| `TreeNode`: Adaptación inmutable (si aplica) | Omitido | — | En V `TreeNode` muta en sitio (`mut node TreeNode`); la variante inmutable no aplica |
| `BinaryTree`: Crear vacío | Sí | `tests/data_structures_advanced_test.v:125` (`test_binary_tree_create_empty`) | `BinaryTree` / iterativo → estado inicial y pertenencia en vacío → grupo `BinaryTree` → `tests/data_structures_advanced_test.v` → `v test .` |
| `BinaryTree`: Insertar la raíz | Sí | `tests/data_structures_advanced_test.v:131` (`test_binary_tree_insert_root`) | `BinaryTree` / iterativo → alta en raíz y tamaño 1 → grupo `BinaryTree` → `tests/data_structures_advanced_test.v` → `v test .` |
| `BinaryTree`: Insertar menor y mayor | Sí | `tests/data_structures_advanced_test.v:137` (`test_binary_tree_insert_lower_and_higher`) | `BinaryTree` / iterativo → inserción en ramas izquierda y derecha → grupo `BinaryTree` → `tests/data_structures_advanced_test.v` → `v test .` |
| `BinaryTree`: Ramas de varios niveles | Sí | `tests/data_structures_advanced_test.v:143` (`test_binary_tree_multilevel_branches`) | `BinaryTree` / iterativo → descenso multinivel y conteo → grupo `BinaryTree` → `tests/data_structures_advanced_test.v` → `v test .` |
| `BinaryTree`: Valor ausente en árbol no vacío | Sí | `tests/data_structures_advanced_test.v:149` (`test_binary_tree_missing_value_in_nonempty_tree`) | `BinaryTree` / iterativo → búsqueda fallida de valor no presente → grupo `BinaryTree` → `tests/data_structures_advanced_test.v` → `v test .` |
| `BinaryTree`: Duplicado idempotente | Sí | `tests/data_structures_advanced_test.v:156` (`test_binary_tree_idempotent_duplicate`) | `BinaryTree` / iterativo → éxito en alta duplicada sin incremento de tamaño → grupo `BinaryTree` → `tests/data_structures_advanced_test.v` → `v test .` |
| `BinaryTree`: Inserciones ordenadas | Sí | `tests/data_structures_advanced_test.v:162` (`test_binary_tree_ordered_insertions`) | `BinaryTree` / iterativo → inserción monótona creciente en $O(h)$ → grupo `BinaryTree` → `tests/data_structures_advanced_test.v` → `v test .` |
| `Graph`: Crear vacío | Sí | `tests/data_structures_advanced_test.v:171` (`test_graph_create_empty`) | `Graph` / registro enlazado → estado vacío y consultas fallidas → grupo `Graph` → `tests/data_structures_advanced_test.v` → `v test .` |
| `Graph`: Vértice aislado | Sí | `tests/data_structures_advanced_test.v:178` (`test_graph_isolated_vertex`) | `Graph` / registro enlazado → vértice registrado sin adyacencias → grupo `Graph` → `tests/data_structures_advanced_test.v` → `v test .` |
| `Graph`: Etiquetas no consecutivas y arista dirigida | Sí | `tests/data_structures_advanced_test.v:185` (`test_graph_nonconsecutive_labels_directed_edge`) | `Graph` / registro enlazado → direccionalidad de aristas no simétricas → grupo `Graph` → `tests/data_structures_advanced_test.v` → `v test .` |
| `Graph`: Vértice duplicado conserva adyacencia | Sí | `tests/data_structures_advanced_test.v:194` (`test_graph_duplicate_vertex_preserves_adjacency`) | `Graph` / registro enlazado → idempotencia de `add_vertex` sin resetear aristas → grupo `Graph` → `tests/data_structures_advanced_test.v` → `v test .` |
| `Graph`: Arista duplicada | Sí | `tests/data_structures_advanced_test.v:203` (`test_graph_duplicate_edge`) | `Graph` / registro enlazado → éxito en adición repetida sin incrementar `edge_count` → grupo `Graph` → `tests/data_structures_advanced_test.v` → `v test .` |
| `Graph`: Extremo inexistente sin mutación | Sí | `tests/data_structures_advanced_test.v:212` (`test_graph_missing_endpoint_without_mutation`) | `Graph` / registro enlazado → fallos atómicos sin creación espuria de vértices → grupo `Graph` → `tests/data_structures_advanced_test.v` → `v test .` |
| `Graph`: Vecinos ordenados y contadores | Sí | `tests/data_structures_advanced_test.v:231` (`test_graph_sorted_neighbors_and_counts`) | `Graph` / registro enlazado → orden creciente estricto en adyacencias → grupo `Graph` → `tests/data_structures_advanced_test.v` → `v test .` |
| `Graph`: Consulta de arista ausente | Sí | `tests/data_structures_advanced_test.v:245` (`test_graph_missing_edge_query`) | `Graph` / registro enlazado → verificación de arista no conectada entre vértices existentes → grupo `Graph` → `tests/data_structures_advanced_test.v` → `v test .` |
| `Graph`: Vecinos de vértice inexistente | Sí | `tests/data_structures_advanced_test.v:252` (`test_graph_neighbors_of_missing_vertex`) | `Graph` / registro enlazado → fallo `false` distinguiendo vértice ausente de aislado → grupo `Graph` → `tests/data_structures_advanced_test.v` → `v test .` |
| `Graph`: Bucle y duplicado | Sí | `tests/data_structures_advanced_test.v:260` (`test_graph_self_loop_and_duplicate`) | `Graph` / registro enlazado → soporte de bucle $u \to u$ e idempotencia → grupo `Graph` → `tests/data_structures_advanced_test.v` → `v test .` |
| `Graph`: Aislamiento del resultado de vecinos | Sí | `tests/data_structures_advanced_test.v:270` (`test_graph_neighbor_result_isolation`) | `Graph` / registro enlazado → independencia de copia frente a mutaciones locales o del grafo → grupo `Graph` → `tests/data_structures_advanced_test.v` → `v test .` |

---

## ⚠️ Limitaciones conocidas / Known limitations

| Limitación / Limitation | Impacto / Impact | Alternativa o plan / Workaround or plan |
|---|---|---|
| Dominio primitivo de enteros `int` | Valores enteros no admiten `null` | Acorde a la fase de algoritmos puros; la nulabilidad y tipos suma se formalizan con `Option` en fases posteriores |
| Altura no balanceada en `BinaryTree` | Inserciones monótonas degeneran el ABB a listas con operaciones en $O(n)$ | Comportamiento natural y esperado para un ABB elemental sin algoritmos de auto-balanceo |
| Recorrido lineal en `find_vertex` | La localización de vértices en el grafo toma tiempo $O(V)$ | Cumple la restricción contractual estricta de no usar índices hash ni mapas de biblioteca |

---

## 📝 Notas de implementación / Implementation Notes

- **ES:** La gestión de memoria dinámica en V para tipos recursivos y autorreferenciados requiere la anotación `@[heap]`. Tanto `TreeNode` como `GraphNode` están anotados correspondientemente para evitar punteros al stack que queden inválidos al retornar.
- **EN:** Dynamic memory management in V for recursive and self-referencing types requires the `@[heap]` attribute. Both `TreeNode` and `GraphNode` are annotated accordingly to prevent stack pointers from becoming invalid upon return.
- **ES:** La inserción y búsqueda en `BinaryTree` se implementan mediante bucles iterativos `for` que descienden por los enlaces `left` y `right`, garantizando un consumo de espacio auxiliar $O(1)$ sin riesgo de desbordamiento de la pila de llamadas.
- **EN:** Insertion and lookup in `BinaryTree` are implemented via iterative `for` loops that traverse down `left` and `right` links, guaranteeing $O(1)$ auxiliary space without risk of call-stack overflow.
- **ES:** Para garantizar el aislamiento requerido en `neighbors(u)`, se devuelve `node.neighbors.clone()`, asegurando que modificaciones sobre el slice devuelto o mutaciones posteriores del grafo no alteren los resultados obtenidos previamente.
- **EN:** To ensure the isolation required in `neighbors(u)`, `node.neighbors.clone()` is returned, ensuring that modifications to the returned slice or subsequent graph mutations do not alter previously retrieved results.
- **ES:** La inserción en el registro de vértices se realiza en $O(1)$ agregando el nuevo vértice al frente de la lista enlazada tras una comprobación previa en $O(V)$, manteniendo un seguimiento desacoplado de `vertex_total` y `edges`.
- **EN:** Vertex registry insertion occurs in $O(1)$ by prepending the new vertex to the linked list after an initial $O(V)$ check, maintaining decoupled tracking of `vertex_total` and `edges`.

---

## 🔍 Checklist de validación / Validation checklist

- [x] La suite nativa se ejecutó y su salida real está copiada en este README.
- [x] Cada caso de la especificación tiene su fila en _Cobertura de pruebas_ (o `Omitido` con razón).
- [x] Cada desviación del pseudocódigo o de la ubicación esperada está en _Adaptaciones idiomáticas_.
- [x] Cada operación con fallo posible está en _Indicadores de fallo_.
- [x] No hay rutas absolutas del autor, credenciales ni salidas inventadas.
- [x] Los enlaces relativos resuelven dentro del repositorio y el documento es bilingüe.
- [x] Ninguna sección repite lo que ya dice la especificación.

---

## 📚 Referencias / References

| Tipo / Kind | Referencia / Reference |
|---|---|
| Especificación / Specification | [`07_Data_Structures_Advanced.md`](https://yorche3.github.io/programming_languages/core/algorithms/07_Data_Structures_Advanced/) |
| Primera base del lenguaje / First language reference | `data_structures_basics` — [`../data_structures_basics/`](../data_structures_basics/) |
| Segunda base del lenguaje / Second language reference | `numbers` — [`../../foundations/numbers/`](../../foundations/numbers/) |
| Guía de inicialización / Initialisation guide | [`core/00_Project_Initialization_Guide.md`](https://yorche3.github.io/programming_languages/core/00_Project_Initialization_Guide/) |
| Adaptaciones idiomáticas / Idiomatic adaptations | [`AGENT_Template.md`](https://yorche3.github.io/programming_languages/AGENT_Template/) |
| Validación de la documentación / Documentation validation | [`WORKFLOW.md`](https://yorche3.github.io/programming_languages/WORKFLOW/) |
| Documentación oficial del lenguaje / Language official docs | [V Language Documentation](https://docs.vlang.io/) |

---

## 🌐 Otras implementaciones / Other implementations

Este proyecto también está implementado en otros lenguajes. Explora el [repositorio principal](https://github.com/yorche3/programming_languages) para ver todas las versiones.

---

*[← Volver a Algoritmos Puros](../README.md)*

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://yorche3.github.io/programming_languages/)*
