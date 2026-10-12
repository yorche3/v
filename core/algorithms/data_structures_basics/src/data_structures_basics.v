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
// Indicadores de fallo (valores representables, sin excepciones):
//   - **int → -1**: `head`, `pop`, `peek` y `dequeue` cuando la estructura está
//     vacía; `value` y `size` devuelven su valor real.
//   - **bool → false**: `delete` cuando el valor no estaba.
//   - **Solo los nodos y los enlaces usan la ausencia nativa `none`**: `next` es
//     `?&Node`, el opcional de V para punteros, y `none` es la ausencia de enlace
//     —no un tipo opcional inventado para el indicador de fallo—. Las operaciones
//     sin resultado de fallo (`insert_head`, `insert_tail`, `push`, `enqueue`) no
//     devuelven nada.
//   - Ningún cuerpo lanza excepciones: el fallo viaja en el valor devuelto.
//
// Mutabilidad: las tres estructuras mutan en sitio, así que cada escenario trabaja
// con una instancia (`new_linked_list()` y luego las operaciones). `Node` es la
// celda compartida: el valor se fija al construirla y el enlace se reengancha.
//
// V y los punteros de la celda: `Node` va marcado `@[heap]`, porque un campo
// `?&Node` puede apuntar a memoria del montón y V lo exige para asignar enlaces;
// y un opcional no se puede usar directamente —se desenvuelve con `if x := opt`,
// con `if mut x := opt` cuando hay que reenganchar ese nodo, o con `or { … }` en
// los recorridos—.
//
// Complejidad: O(1) en `head`, `insert_head`, `insert_tail`, `push`, `pop`,
// `peek`, `enqueue`, `dequeue`, `is_empty` y `size` —las estructuras guardan sus
// punteros (cabeza/cola, cima, frente/final) y su contador— y O(n) en `delete`,
// como pide la especificación.

module src

@[heap]
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

// Valor de la celda. No muta.
pub fn (node &Node) value() int {
	return node.value
}

// Enlace a la celda siguiente, o none cuando no hay ninguna.
pub fn (node &Node) next() ?&Node {
	return node.next
}

// Reengancha el enlace: la celda es mutable.
pub fn (mut node Node) set_next(next ?&Node) {
	node.next = next
}

// ---------------------------------------------------------------------------
// LinkedList
// ---------------------------------------------------------------------------

pub struct LinkedList {
mut:
	head  ?&Node
	tail  ?&Node
	count int
}

// Crea una lista vacía: sin enlaces y con el contador a cero (el `init()` de la
// especificación).
pub fn new_linked_list() &LinkedList {
	return &LinkedList{}
}

// Valor de la cabeza, o -1 cuando la lista está vacía. No muta.
pub fn (list &LinkedList) head() int {
	if head := list.head {
		return head.value()
	}
	return -1
}

// true solo si no hay nodos.
pub fn (list &LinkedList) is_empty() bool {
	return list.head == none
}

// Número de nodos. O(1) sobre el contador.
pub fn (list &LinkedList) size() int {
	return list.count
}

// Inserta al principio: O(1) y sin resultado de fallo.
pub fn (mut list LinkedList) insert_head(value int) {
	mut new_head := new_node(value)
	new_head.set_next(list.head)
	list.head = new_head
	if list.tail == none {
		list.tail = new_head
	}
	list.count++
}

// Inserta al final: O(1) y sin resultado de fallo. El final guardado es lo que
// evita recorrer la lista.
pub fn (mut list LinkedList) insert_tail(value int) {
	new_tail := new_node(value)
	if mut tail := list.tail {
		tail.set_next(new_tail)
	} else {
		list.head = new_tail
	}
	list.tail = new_tail
	list.count++
}

// Borra la primera aparición: true si borró y false si el valor no estaba. O(n).
pub fn (mut list LinkedList) delete(value int) bool {
	mut previous := ?&Node(none)
	mut current := list.head
	for current != none {
		node := current or { break }
		if node.value() == value {
			if mut prev := previous {
				prev.set_next(node.next())
			} else {
				list.head = node.next()
			}
			if list.tail == current {
				list.tail = previous
			}
			list.count--
			return true
		}
		previous = current
		current = node.next()
	}
	return false
}

// ---------------------------------------------------------------------------
// Stack
// ---------------------------------------------------------------------------

pub struct Stack {
mut:
	top   ?&Node
	count int
}

// Crea una pila vacía: sin cima y con el contador a cero (el `init()` de la
// especificación).
pub fn new_stack() &Stack {
	return &Stack{}
}

// true solo si no hay nodos.
pub fn (stack &Stack) is_empty() bool {
	return stack.top == none
}

// Número de nodos. O(1) sobre el contador.
pub fn (stack &Stack) size() int {
	return stack.count
}

// Apila sobre la cima: O(1) y sin resultado de fallo.
pub fn (mut stack Stack) push(value int) {
	mut new_top := new_node(value)
	new_top.set_next(stack.top)
	stack.top = new_top
	stack.count++
}

// Desapila: devuelve el valor de la cima, o -1 cuando está vacía. O(1).
pub fn (mut stack Stack) pop() int {
	if top := stack.top {
		value := top.value()
		stack.top = top.next()
		stack.count--
		return value
	}
	return -1
}

// Valor de la cima, o -1 cuando está vacía. No muta.
pub fn (stack &Stack) peek() int {
	if top := stack.top {
		return top.value()
	}
	return -1
}

// ---------------------------------------------------------------------------
// Queue
// ---------------------------------------------------------------------------

pub struct Queue {
mut:
	front ?&Node
	rear  ?&Node
	count int
}

// Crea una cola vacía: sin frente, sin final y con el contador a cero (el
// `init()` de la especificación).
pub fn new_queue() &Queue {
	return &Queue{}
}

// true solo si no hay nodos.
pub fn (queue &Queue) is_empty() bool {
	return queue.front == none
}

// Número de nodos. O(1) sobre el contador.
pub fn (queue &Queue) size() int {
	return queue.count
}

// Encola por el final: O(1) y sin resultado de fallo. El final guardado es lo que
// evita recorrer la cola.
pub fn (mut queue Queue) enqueue(value int) {
	new_rear := new_node(value)
	if mut rear := queue.rear {
		rear.set_next(new_rear)
	} else {
		queue.front = new_rear
	}
	queue.rear = new_rear
	queue.count++
}

// Desencola: devuelve el valor del frente, o -1 cuando está vacía. O(1).
pub fn (mut queue Queue) dequeue() int {
	if front := queue.front {
		value := front.value()
		queue.front = front.next()
		if queue.front == none {
			queue.rear = none
		}
		queue.count--
		return value
	}
	return -1
}

// Valor del frente, o -1 cuando está vacía. No muta.
pub fn (queue &Queue) peek() int {
	if front := queue.front {
		return front.value()
	}
	return -1
}
