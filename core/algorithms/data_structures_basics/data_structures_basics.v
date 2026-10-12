// data_structures_basics — Node, lista enlazada, pila y cola.
//
// Especificación: 06_Data_Structures_Basics
//
// Contrato: un único tipo de celda, `Node`, compartido por las tres estructuras;
// cada una guarda sus propios punteros y su contador y no delega en `LinkedList`.
// El valor de la celda se fija al construirla y el enlace se reengancha con
// `set_next`.
// API (naming snake_case, el mismo de la especificación y de
// `core/foundations/numbers/`): `new_node`, `value`, `next`, `set_next`;
// `new_linked_list`, `head`, `is_empty`, `size`, `insert_head`, `insert_tail`,
// `delete`; `new_stack`, `push`, `pop`, `peek`; `new_queue`, `enqueue`, `dequeue`,
// `peek`.
//
// Adecuaciones de salida de centinela (todavía no hay fallos reales):
//   - **int → -1**: `value`, `head`, `pop`, `peek`, `dequeue` y `size` mientras su
//     cuerpo sea un esqueleto.
//   - **bool → false**: `is_empty` y `delete`.
//   - **Solo los nodos y los enlaces usan la ausencia nativa `none`**: `next` es
//     `?&Node`, el opcional de V para punteros, y `none` es la ausencia de enlace
//     —no un tipo opcional inventado para el indicador de fallo—. Ningún cuerpo
//     lanza excepciones.
//
// `init` de la especificación: las funciones `new_node`, `new_linked_list`,
// `new_stack` y `new_queue` construyen el estado —la celda con su valor y sin
// enlace; las tres estructuras vacías— y quedan implementadas; el resto de los
// cuerpos son esqueletos con el centinela de su tipo. La implementación es el
// paso 5.

module data_structures_basics

// ---------------------------------------------------------------------------
// Node — celda enlazada compartida por LinkedList, Stack y Queue.
// ---------------------------------------------------------------------------

// Celda enlazada. El valor es inmutable tras la construcción; el enlace es
// mutable.
pub struct Node {
mut:
	value int
	next  ?&Node
}

// Crea una celda con `value` y el enlace ausente (el `init(value)` de la
// especificación).
pub fn new_node(value int) &Node {
	return &Node{
		value: value
		next: none
	}
}

// Esqueleto: valor de la celda.
pub fn (node &Node) value() int {
	return -1
}

// Esqueleto: enlace a la celda siguiente, o none cuando no hay ninguna.
pub fn (node &Node) next() ?&Node {
	return none
}

// Esqueleto: reengancha el enlace.
pub fn (mut node Node) set_next(next ?&Node) {
	_ = next
}

// ---------------------------------------------------------------------------
// LinkedList
// ---------------------------------------------------------------------------

// Lista enlazada simple construida desde cero sobre Node.
pub struct LinkedList {
mut:
	head  ?&Node
	tail  ?&Node
	count int
}

// Crea una lista vacía: sin enlaces y con el contador a cero.
pub fn new_linked_list() &LinkedList {
	return &LinkedList{}
}

// Esqueleto: valor de la cabeza, o -1 cuando la lista está vacía. No muta.
pub fn (list &LinkedList) head() int {
	return -1
}

// Esqueleto: true solo si no hay nodos.
pub fn (list &LinkedList) is_empty() bool {
	return false
}

// Esqueleto: número de nodos (el centinela es -1 mientras sea esqueleto).
pub fn (list &LinkedList) size() int {
	return -1
}

// Esqueleto: inserta al principio. O(1). Sin resultado de fallo.
pub fn (mut list LinkedList) insert_head(value int) {
	_ = value
}

// Esqueleto: inserta al final. O(1). Sin resultado de fallo.
pub fn (mut list LinkedList) insert_tail(value int) {
	_ = value
}

// Esqueleto: borra la primera aparición; false cuando el valor no estaba. O(n).
pub fn (mut list LinkedList) delete(value int) bool {
	_ = value
	return false
}

// ---------------------------------------------------------------------------
// Stack
// ---------------------------------------------------------------------------

// Pila LIFO construida desde cero sobre Node.
pub struct Stack {
mut:
	top   ?&Node
	count int
}

// Crea una pila vacía: sin cima y con el contador a cero.
pub fn new_stack() &Stack {
	return &Stack{}
}

// Esqueleto: true solo si no hay nodos.
pub fn (stack &Stack) is_empty() bool {
	return false
}

// Esqueleto: número de nodos (el centinela es -1 mientras sea esqueleto).
pub fn (stack &Stack) size() int {
	return -1
}

// Esqueleto: apila sobre la cima. O(1). Sin resultado de fallo.
pub fn (mut stack Stack) push(value int) {
	_ = value
}

// Esqueleto: desapila el valor de la cima, o -1 cuando está vacía. O(1).
pub fn (mut stack Stack) pop() int {
	return -1
}

// Esqueleto: valor de la cima, o -1 cuando está vacía. No muta.
pub fn (stack &Stack) peek() int {
	return -1
}

// ---------------------------------------------------------------------------
// Queue
// ---------------------------------------------------------------------------

// Cola FIFO construida desde cero sobre Node.
pub struct Queue {
mut:
	front ?&Node
	rear  ?&Node
	count int
}

// Crea una cola vacía: sin frente, sin final y con el contador a cero.
pub fn new_queue() &Queue {
	return &Queue{}
}

// Esqueleto: true solo si no hay nodos.
pub fn (queue &Queue) is_empty() bool {
	return false
}

// Esqueleto: número de nodos (el centinela es -1 mientras sea esqueleto).
pub fn (queue &Queue) size() int {
	return -1
}

// Esqueleto: encola por el final. O(1). Sin resultado de fallo.
pub fn (mut queue Queue) enqueue(value int) {
	_ = value
}

// Esqueleto: desencola el valor del frente, o -1 cuando está vacía. O(1).
pub fn (mut queue Queue) dequeue() int {
	return -1
}

// Esqueleto: valor del frente, o -1 cuando está vacía. No muta.
pub fn (queue &Queue) peek() int {
	return -1
}
