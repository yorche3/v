module src

// data_structures_advanced — TreeNode, BinaryTree, GraphNode y Graph.
//
// Especificación: 07_Data_Structures_Advanced
//
// Contrato declarado con la API pública del módulo: los tipos exportados son
// `TreeNode`, `BinaryTree` y `Graph`; `NeighborNode` y `GraphNode` quedan
// internos a la implementación del grafo.
//
// Adaptaciones declaradas:
//   - Ausencia: `none` sobre `?&TreeNode` para los enlaces y sobre
//     `?&GraphNode` para el registro de vértices. V no tiene `null`.
//   - `neighbors` devuelve `([]int, bool)`: el `bool` distingue el vértice
//     inexistente (`false`) del vértice aislado (`true` con lista vacía), que
//     es la distinción que exige la especificación sin inventar un centinela.
//   - Valor embebido: cada nodo declara su `value` y valida sus propios
//     enlaces; V no tiene herencia de structs.
//   - Mutabilidad: los nodos y las estructuras mutan en sitio, como en la base
//     `data_structures_basics`, así que cada escenario trabaja con una
//     instancia.
//
// Indicadores de fallo (valores representables, sin excepciones):
//   - **bool**: `insert`, `contains`, `is_empty`, `add_vertex`, `add_edge`,
//     `has_edge`. Un alta duplicada o una arista repetida devuelven `true`: son
//     éxito y no suman al contador.
//   - **`([], false)`**: `neighbors` de un vértice inexistente.
//
// La búsqueda por etiqueta, la detección de duplicados y la inserción ordenada
// de vecinos se escriben a mano: no se usan `sort`, `index` ni `contains` de la
// biblioteca en los pasos internos del algoritmo.

@[heap]
pub struct TreeNode {
mut:
	value int
	left  ?&TreeNode
	right ?&TreeNode
}

// `init(value)` de la especificación: valor fijado y ambos enlaces ausentes.
pub fn new_tree_node(value int) &TreeNode {
	return &TreeNode{ value: value, left: none, right: none }
}

// Valor del nodo.
pub fn (node &TreeNode) value() int {
	return node.value
}

// Enlace izquierdo, o `none` cuando está ausente.
pub fn (node &TreeNode) left() ?&TreeNode {
	return node.left
}

// Enlace derecho, o `none` cuando está ausente.
pub fn (node &TreeNode) right() ?&TreeNode {
	return node.right
}

// Reemplaza el enlace izquierdo con `left`, o lo deja ausente con `none`.
pub fn (mut node TreeNode) set_left(left ?&TreeNode) {
	node.left = left
}

// Reemplaza el enlace derecho con `right`, o lo deja ausente con `none`.
pub fn (mut node TreeNode) set_right(right ?&TreeNode) {
	node.right = right
}

@[heap]
pub struct BinaryTree {
mut:
	root  ?&TreeNode
	count int
}

// `init()` de la especificación: raíz ausente y contador a cero.
pub fn new_binary_tree() &BinaryTree {
	return &BinaryTree{ root: none, count: 0 }
}

// Inserta `value`; un duplicado también es éxito y no crece el tamaño.
// Desciende por la invariante del ABB con un bucle, sin recursión.
pub fn (mut tree BinaryTree) insert(value int) bool {
	if tree.root == none {
		tree.root = new_tree_node(value)
		tree.count++
		return true
	}
	mut current := tree.root or { return false }
	for {
		if value == current.value {
			return true
		}
		if value < current.value {
			if current.left == none {
				current.left = new_tree_node(value)
				tree.count++
				return true
			}
			current = current.left or { return false }
		} else {
			if current.right == none {
				current.right = new_tree_node(value)
				tree.count++
				return true
			}
			current = current.right or { return false }
		}
	}
	return false
}

// `true` si `value` pertenece al árbol; `false` si no.
pub fn (tree &BinaryTree) contains(value int) bool {
	mut current := tree.root
	for {
		node := current or { return false }
		if value == node.value {
			return true
		}
		current = if value < node.value { node.left } else { node.right }
	}
	return false
}

// `true` solo si no hay nodos.
pub fn (tree &BinaryTree) is_empty() bool {
	return tree.count == 0
}

// Número de valores distintos del árbol.
pub fn (tree &BinaryTree) size() int {
	return tree.count
}

// Vértice del registro canónico: etiqueta, adyacencia ordenada y enlace al
// siguiente vértice. Interno a `Graph`.
@[heap]
struct GraphNode {
mut:
	value       int
	neighbors   []int
	next_vertex ?&GraphNode
}

// `init(label)` interno de la especificación: sin vecinos y sin siguiente.
fn new_graph_node(label int) &GraphNode {
	return &GraphNode{ value: label, neighbors: [], next_vertex: none }
}

// Búsqueda lineal por etiqueta sobre el registro enlazado.
fn (graph &Graph) find_vertex(label int) ?&GraphNode {
	mut current := graph.vertices
	for {
		node := current or { return none }
		if node.value == label {
			return node
		}
		current = node.next_vertex
	}
	return none
}

// `true` si `label` figura en la adyacencia; se recorre a mano.
fn (node &GraphNode) has_neighbor(label int) bool {
	for neighbor in node.neighbors {
		if neighbor == label {
			return true
		}
	}
	return false
}

// Inserta `label` en su posición creciente. Devuelve `false` si ya era vecino,
// así que el grafo no cuenta una arista nueva. La posición se busca recorriendo
// la adyacencia a mano, sin `sort` ni `index`.
fn (mut node GraphNode) add_neighbor(label int) bool {
	mut position := 0
	for position < node.neighbors.len {
		if node.neighbors[position] == label {
			return false
		}
		if node.neighbors[position] > label {
			break
		}
		position++
	}
	node.neighbors.insert(position, label)
	return true
}

pub struct Graph {
mut:
	vertices     ?&GraphNode
	vertex_total int
	edges        int
}

// `init()` de la especificación: registro ausente y ambos contadores a cero.
pub fn new_graph() &Graph {
	return &Graph{ vertices: none, vertex_total: 0, edges: 0 }
}

// Registra `label`; un duplicado también es éxito y conserva los vecinos.
pub fn (mut graph Graph) add_vertex(label int) bool {
	if graph.find_vertex(label) != none {
		return true
	}
	mut new_vertex := new_graph_node(label)
	new_vertex.next_vertex = graph.vertices
	graph.vertices = new_vertex
	graph.vertex_total++
	return true
}

// Añade la arista `u → v`; falla si falta un extremo y no muta. Una arista
// repetida o un bucle repetido también son éxito, pero no cuentan.
pub fn (mut graph Graph) add_edge(u int, v int) bool {
	mut u_vertex := graph.find_vertex(u) or { return false }
	if graph.find_vertex(v) == none {
		return false
	}
	if u_vertex.add_neighbor(v) {
		graph.edges++
	}
	return true
}

// `true` si la arista `u → v` existe; `false` si no existe o falta un extremo.
pub fn (graph &Graph) has_edge(u int, v int) bool {
	u_vertex := graph.find_vertex(u) or { return false }
	return u_vertex.has_neighbor(v)
}

// Vecinos de `u` en orden creciente: lista vacía con `true` si el vértice está
// aislado, y `false` si el vértice no existe.
pub fn (graph &Graph) neighbors(u int) ([]int, bool) {
	node := graph.find_vertex(u) or { return []int{}, false }
	return node.neighbors.clone(), true
}

// `true` solo si no hay vértices.
pub fn (graph &Graph) is_empty() bool {
	return graph.vertex_total == 0
}

// Número de vértices registrados.
pub fn (graph &Graph) vertex_count() int {
	return graph.vertex_total
}

// Número de aristas registradas.
pub fn (graph &Graph) edge_count() int {
	return graph.edges
}
