# Data Structures Basics — V

Implementación de la especificación [06_Data_Structures_Basics](https://yorche3.github.io/programming_languages/core/algorithms/06_Data_Structures_Basics/) en **V**, usando estructuras basadas en un nodo compartido (`Node`) sobre el heap con punteros opcionales y el framework de pruebas integrado de V (`v test`).

El módulo implementa manualmente tres estructuras de datos elementales — `LinkedList`, `Stack` y `Queue` — compartiendo una única estructura de celda enlazada `Node`, gestionando cada una sus propios punteros de forma independiente y sin dependencias operacionales de la biblioteca estándar.

---

## 📂 Archivos y estructura / Files & Structure

Describe la estructura del proyecto y el propósito de cada archivo.

| Archivo / Directory | Propósito / Purpose |
|---|---|
| `src/data_structures_basics.v` | Implementación del nodo compartido y las tres estructuras de datos (`Node`, `LinkedList`, `Stack`, `Queue`) / Source code for shared node and data structures |
| `tests/data_structures_basics_test.v` | Suite de pruebas unitarias integradas con 23 funciones `test_*` / Unit test suite covering all contract operations |
| `v.mod` | Manifiesto de metadatos del módulo V / V module manifest |
| `.gitignore` | Archivos generados y artefactos excluidos / Ignored generated files |
| `.editorconfig` | Configuración de formato y estilo de código / Editor formatting rules |

```text
data_structures_basics/
├── .editorconfig
├── .gitignore
├── src/
│   └── data_structures_basics.v
├── tests/
│   └── data_structures_basics_test.v
├── v.mod
└── README.md
```

> **Nota de desviación de estructura / Layout deviation note:** La especificación sugiere `src/data_structures_basics.ext` y `test/run_tests.ext`. Aquí el fuente vive en `src/data_structures_basics.v` —declara `module src` y es lo que verifica `v fmt -verify src`— y las pruebas en `tests/`, la carpeta que crea `v init --lib`, con el sufijo `_test.v` que V descubre y `v test .` como runner, sin `run_tests` manual.

---

## 🛠️ Enfoque y construcción / Approach & Build

**ES:** El proyecto se construyó de forma manual como un paquete V autónomo. La celda `Node` está anotada con `@[heap]` para permitir la asignación dinámica de nodos enlazados mediante punteros de referencia opcionales (`?&Node`), utilizando el valor nativo `none` para representar la ausencia de enlace. Las tres estructuras (`LinkedList`, `Stack`, `Queue`) mutan en sitio (*in-place*) y mantienen sus propios punteros (`head`/`tail`, `top`, `front`/`rear`) y contadores de tamaño `count` de forma desacoplada.

**EN:** The project was built manually as a standalone V package. The `Node` cell is marked with `@[heap]` to enable dynamic heap allocation for linked nodes via optional reference pointers (`?&Node`), using the native `none` value to represent absence of link. All three structures (`LinkedList`, `Stack`, `Queue`) mutate in-place and maintain their own pointers (`head`/`tail`, `top`, `front`/`rear`) and size counters `count` independently.

### Inicialización / Initialization

```bash
mkdir -p v/core/algorithms/data_structures_basics/tests
cd v/core/algorithms/data_structures_basics
v init
```

---

## 📄 Configuración clave / Key Configuration

### `v.mod`

```v
Module {
    name: 'data_structures_basics'
    version: '0.1.0'
    license: 'MIT'
    dependencies: []
}
```

El manifiesto identifica el módulo local `data_structures_basics`; el fuente declara `module src` (submódulo del paquete) y la suite lo importa con `import data_structures_basics.src as ds`. El `description` vacío y la versión/licencia por defecto que escribe el inicializador se retiraron para dejar el mismo patrón que `core/foundations/numbers/`: versión declarada `0.1.0` y licencia `MIT`.

---

## 🚀 Compilación y ejecución / Build & Run

### Verificación estática / Static check

```bash
v -shared -check src/data_structures_basics.v
```

### Ejecución de pruebas / Run tests

```bash
v test .
```

**Salida real / Actual output:**

```text
$ v -shared -check src/data_structures_basics.v

$ v test .
---- Testing... ----------------------------------------------------------------
OK       3.209 ms ~/programming_languages/v/core/algorithms/data_structures_basics/tests/data_structures_basics_test.v
--------------------------------------------------------------------------------
Summary for all V _test.v files: 1 passed, 1 total. Elapsed time: 3350 ms, on 1 job. Comptime: 3344 ms. Runtime: 3 ms.
```

---

## 🧠 Algoritmos y operaciones / Algorithms & Operations

| Operación / Operation | Entrada → salida / Input → output | Complejidad / Complexity | Notas / Notes |
|---|---|---|---|
| `new_node(value)` | `int → &Node` | $O(1)$ | Construye una celda en el heap con valor y enlace ausente (`none`) |
| `Node.value()` | `() → int` | $O(1)$ | Observador no mutante del valor entero contenido |
| `Node.next()` | `() → ?&Node` | $O(1)$ | Observador no mutante del puntero al siguiente nodo |
| `Node.set_next(next)` | `?&Node → ()` | $O(1)$ | Reengancha el puntero de enlace en la celda mutable |
| `new_linked_list()` | `() → &LinkedList` | $O(1)$ | Inicializa una lista vacía con cabeza/cola en `none` y contador en 0 |
| `LinkedList.head()` | `() → int` | $O(1)$ | Devuelve el valor de la cabeza o `-1` si está vacía |
| `LinkedList.is_empty()` | `() → bool` | $O(1)$ | Comprueba si `head == none` |
| `LinkedList.size()` | `() → int` | $O(1)$ | Consulta el contador interno `count` |
| `LinkedList.insert_head(value)` | `int → ()` | $O(1)$ | Inserta un nodo al inicio y actualiza `head` (y `tail` si estaba vacía) |
| `LinkedList.insert_tail(value)` | `int → ()` | $O(1)$ | Inserta un nodo al final en $O(1)$ usando el puntero `tail` guardado |
| `LinkedList.delete(value)` | `int → bool` | $O(n)$ | Elimina la primera aparición del valor; actualiza punteros y devuelve `true`/`false` |
| `new_stack()` | `() → &Stack` | $O(1)$ | Inicializa una pila vacía con tope en `none` y contador en 0 |
| `Stack.is_empty()` | `() → bool` | $O(1)$ | Comprueba si `top == none` |
| `Stack.size()` | `() → int` | $O(1)$ | Consulta el contador interno `count` |
| `Stack.push(value)` | `int → ()` | $O(1)$ | Apila un nuevo nodo sobre el tope (`top`) |
| `Stack.pop()` | `() → int` | $O(1)$ | Extrae y devuelve el valor del tope, o `-1` si la pila está vacía |
| `Stack.peek()` | `() → int` | $O(1)$ | Observa el valor del tope sin extraerlo, o `-1` si está vacía |
| `new_queue()` | `() → &Queue` | $O(1)$ | Inicializa una cola vacía con frente y final en `none` y contador en 0 |
| `Queue.is_empty()` | `() → bool` | $O(1)$ | Comprueba si `front == none` |
| `Queue.size()` | `() → int` | $O(1)$ | Consulta el contador interno `count` |
| `Queue.enqueue(value)` | `int → ()` | $O(1)$ | Encola un nuevo nodo tras `rear` en $O(1)$ |
| `Queue.dequeue()` | `() → int` | $O(1)$ | Extrae y devuelve el valor del frente, o `-1` si la cola está vacía |
| `Queue.peek()` | `() → int` | $O(1)$ | Observa el valor del frente sin extraerlo, o `-1` si está vacía |

---

## 🧩 Decisiones de diseño / Design decisions

| Decisión / Decision | Alternativa considerada / Alternative | Razón / Reason |
|---|---|---|
| Atributo `@[heap]` en `struct Node` | Almacenamiento directo en stack / valor plano | V exige `@[heap]` cuando los campos contienen referencias autorreferenciadas u opcionales de puntero mutables para evitar dangling pointers |
| Ausencia mediante `?&Node` nativo | Puntero crudo `&Node` nulo inseguro o centinela especial | `?&Node` es el mecanismo idiomático seguro de V para referencias anulables opcionales sin comprometer la seguridad de memoria |
| Mutación en sitio con receptores mutables (`mut list LinkedList`) | Retorno de instancias clonadas e inmutables | Las estructuras de datos elementales con punteros y contadores se modelan eficientemente en memoria mediante mutación local |
| Puntero `tail` en `LinkedList` y `rear` en `Queue` | Recorrido lineal $O(n)$ en cada inserción al final | Garantiza la complejidad $O(1)$ requerida por el contrato para `insert_tail` y `enqueue` |

---

## 🔀 Adaptaciones idiomáticas / Idiomatic adaptations

| Especificación / Specification | Adaptación / Adaptation | Justificación / Justification |
|---|---|---|
| `init(value)` / `init()` constructores | Funciones constructoras idiomáticas `new_node`, `new_linked_list`, `new_stack`, `new_queue` | V utiliza convenciones `new_*` como constructores factoría estándar que devuelven referencias inicializadas |
| Representación de ausencia en enlaces (`next = absent`) | `next = none` sobre tipo `?&Node` | V utiliza `none` para denotar la ausencia nativa en tipos opcionales de puntero |
| `get_value()`, `get_next()`, `get_head()` | Métodos de método receptor `node.value()`, `node.next()`, `list.head()` | En V los getters omiten el prefijo `get_` para alinearse con el estilo idiomático del lenguaje |
| Ubicación esperada `src/` y `test/run_tests.ext` | `src/data_structures_basics.v` (con `module src`) y `tests/` con `v test .` | El fuente va a `src/` porque es la ruta que verifican `v fmt -verify src` y los tres módulos V homologados; `tests/` es la carpeta que crea `v init --lib` y se conserva tal cual |
| Caso nulo / entrada inválida | Omitido para valores numéricos enteros | `int` en V es un tipo de valor primitivo que no admite `null`; no hay caso nulo para enteros representables |

---

## 🚨 Indicadores de fallo / Failure indicators

| Operación / Operation | Situación de fallo / Failure situation | Indicador / Indicator | Ejemplo / Example |
|---|---|---|---|
| `LinkedList.head()` | Lista vacía (`count == 0`) | `-1` | `new_linked_list().head() == -1` |
| `LinkedList.delete(value)` | Valor no presente en la lista | `false` | `list.delete(99) == false` |
| `Stack.peek()` | Pila vacía (`count == 0`) | `-1` | `new_stack().peek() == -1` |
| `Stack.pop()` | Pila vacía (`count == 0`) | `-1` | `new_stack().pop() == -1` |
| `Queue.peek()` | Cola vacía (`count == 0`) | `-1` | `new_queue().peek() == -1` |
| `Queue.dequeue()` | Cola vacía (`count == 0`) | `-1` | `new_queue().dequeue() == -1` |
| `Node.next()` | Ausencia de enlace siguiente | `none` | `new_node(10).next() == none` |
| Valor entero `null` / inválido | Entrada nula en tipos `int` | No representable | En V los enteros son tipos por valor no anulables |

---

## ✅ Cobertura de pruebas / Test coverage

| Caso de la especificación / Specification case | Cubierto / Covered | Prueba / Test | Notas / Notes |
|---|---|:--:|---|
| `Node`: Inicializar y observar valor/enlace | Sí | `tests/data_structures_basics_test.v:19` (`test_new_node`, `test_node_value`, `test_node_next`) | Verifica `value() == 10` y `next() == none` |
| `Node`: Inicializar otro nodo, enlazar y recorrer | Sí | `tests/data_structures_basics_test.v:24` (`test_node_set_next`) | Enlaza segundo nodo y verifica recorrido mediante `next()` |
| `LinkedList`: Estado vacío | Sí | `tests/data_structures_basics_test.v:35` (`test_new_linked_list`, `test_linked_list_is_empty`, `test_linked_list_size`, `test_linked_list_head`) | Verifica `is_empty() == true`, `size() == 0`, `head() == -1` |
| `LinkedList`: Insertar por ambos extremos | Sí | `tests/data_structures_basics_test.v:40` (`test_linked_list_insert_head`, `test_linked_list_insert_tail`) | Secuencia de inserciones `10, 20, 5, 10`, verifica `size() == 4` y cabeza `5` |
| `LinkedList`: Eliminar primera aparición | Sí | `tests/data_structures_basics_test.v:47` (`test_linked_list_delete`) | Elimina valor intermedio `10`, verifica `size() == 3` y conservación de cabeza |
| `LinkedList`: Valor ausente | Sí | `tests/data_structures_basics_test.v:51` (`test_linked_list_delete`) | Intento de borrar `99`, devuelve `false` sin mutar tamaño |
| `LinkedList`: Vaciar la lista | Sí | `tests/data_structures_basics_test.v:55` (`test_linked_list_delete`) | Borrado sucesivo de elementos restantes hasta `is_empty() == true` y `head() == -1` |
| `Stack`: Estado vacío y extracción fallida | Sí | `tests/data_structures_basics_test.v:66` (`test_new_stack`, `test_stack_is_empty`, `test_stack_size`, `test_stack_peek`, `test_stack_pop`) | Verifica `is_empty() == true`, `size() == 0`, `peek() == -1`, `pop() == -1` |
| `Stack`: LIFO y `peek` no mutante | Sí | `tests/data_structures_basics_test.v:72` (`test_stack_push`, `test_stack_peek`) | Apila `10, 20, 30`, verifica `peek() == 30` y `size() == 3` |
| `Stack`: Extracción y reutilización | Sí | `tests/data_structures_basics_test.v:78` (`test_stack_push`, `test_stack_pop`) | Desapila y reutiliza con `push(40)`, desapila en orden LIFO hasta vaciar |
| `Stack`: Vacío tras extracción | Sí | `tests/data_structures_basics_test.v:86` (`test_stack_pop`) | Comprueba fallo con `-1` al desapilar de pila vacía y mantiene `is_empty()` |
| `Queue`: Estado vacío y extracción fallida | Sí | `tests/data_structures_basics_test.v:91` (`test_new_queue`, `test_queue_is_empty`, `test_queue_size`, `test_queue_peek`, `test_queue_dequeue`) | Verifica `is_empty() == true`, `size() == 0`, `peek() == -1`, `dequeue() == -1` |
| `Queue`: FIFO y `peek` no mutante | Sí | `tests/data_structures_basics_test.v:97` (`test_queue_enqueue`, `test_queue_peek`) | Encola `10, 20, 30`, verifica `peek() == 10` y `size() == 3` |
| `Queue`: Extracción y reutilización | Sí | `tests/data_structures_basics_test.v:103` (`test_queue_enqueue`, `test_queue_dequeue`) | Desencola y encola `40`, desencola en orden FIFO hasta vaciar |
| `Queue`: Vacío tras extracción | Sí | `tests/data_structures_basics_test.v:111` (`test_queue_dequeue`) | Comprueba fallo con `-1` al desencolar de cola vacía y mantiene `is_empty()` |
| Caso de entrada entera `null` | Omitido | — | `int` en V es un tipo primitivo por valor y no admite `null` |

---

## ⚠️ Limitaciones conocidas / Known limitations

| Limitación / Limitation | Impacto / Impact | Alternativa o plan / Workaround or plan |
|---|---|---|
| Dominio de valores positivos | Valores `-1` no diferenciables del centinela de fallo | Acorde a la especificación de algoritmos puros; se formaliza con tipos sumas `Option` en la fase de abstracción |
| Sin soporte para tipos genéricos en este nivel | Las estructuras solo contienen valores de tipo `int` | Diseñado específicamente para cumplir el contrato mínimo del módulo sin genericidad prematura |

---

## 📝 Notas de implementación / Implementation Notes

- **ES:** La celda compartida `Node` implementa el enlace como un tipo opcional de puntero `?&Node`. Para acceder al enlace se utiliza desempaquetado condicional (`if head := list.head` o `node := current or { break }`). Cuando se requiere reasignar el enlace de un nodo existente, se utiliza la referencia mutable `if mut tail := list.tail`.
- **EN:** The shared cell `Node` implements links as an optional pointer type `?&Node`. Traversals unwrap pointers conditionally (`if head := list.head` or `node := current or { break }`). When updating links on an existing node, mutable unwrapping `if mut tail := list.tail` is used.
- **ES:** Todas las operaciones respetan las cotas de complejidad temporal requeridas: $O(1)$ para inserciones y eliminaciones en los extremos gracias a los punteros auxiliares `tail` y `rear`, y $O(n)$ en `delete` por el recorrido lineal sobre la lista enlazada.
- **EN:** All operations satisfy the required time complexity bounds: $O(1)$ for end insertions and deletions through auxiliary `tail` and `rear` pointers, and $O(n)$ in `delete` due to linear traversal over the linked list.
- **ES:** El indicador natural de fallo para operaciones vacías devuelve `-1`, mientras que para borrados devuelve `bool` (`false` en ausencia del valor). No se levantan excepciones ni panics.
- **EN:** The natural failure indicator for empty operations returns `-1`, while deletions return `bool` (`false` when absent). No exceptions or panics are raised.

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
| Especificación / Specification | [`06_Data_Structures_Basics.md`](https://yorche3.github.io/programming_languages/core/algorithms/06_Data_Structures_Basics/) |
| Módulo homologado del lenguaje / Homologated module | [`v/core/foundations/numbers/`](https://yorche3.github.io/programming_languages/core/foundations/numbers/) |
| Guía de inicialización / Initialisation guide | [`00_Project_Initialization_Guide.md`](https://yorche3.github.io/programming_languages/core/00_Project_Initialization_Guide/) |
| Adaptaciones idiomáticas / Idiomatic adaptations | [`AGENT_Template.md`](https://yorche3.github.io/programming_languages/AGENT_Template/) |
| Validación de la documentación / Documentation validation | [`WORKFLOW.md`](https://yorche3.github.io/programming_languages/WORKFLOW/) |
| Documentación oficial del lenguaje / Language official docs | [V Language Documentation](https://docs.vlang.io/) |

---

## 🌐 Otras implementaciones / Other implementations

Este proyecto también está implementado en otros lenguajes. Explora el [repositorio principal](https://github.com/yorche3/programming_languages) para ver todas las versiones.

---

*[← Volver a Algoritmos Puros](../README.md)*

*🌐 [github.com/yorche3/programming_languages](https://github.com/yorche3/programming_languages) · [GitHub Pages](https://yorche3.github.io/programming_languages/)*
