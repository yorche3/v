// Casos de prueba de la especificación 06_Data_Structures_Basics.md.
//
// Adaptación: V representa la ausencia del enlace de Node con `none` en
// `?&Node`. Las estructuras se inicializan con sus constructores
// `new_*`; sus valores y los enteros de las operaciones no admiten `null`,
// por lo que no hay un caso nulo independiente.

import data_structures_basics as ds

const failure_value = -1
const empty_size = 0
const first_value = 5
const second_value = 10
const third_value = 20
const fourth_value = 30
const reused_value = 40
const absent_value = 99

fn assert_node_cases(subject string) {
	mut first_node := ds.new_node(second_value)
	assert first_node.value() == second_value, '${subject} should preserve the initialized value'
	assert first_node.next() == none, '${subject} should leave the initialized link absent'

	second_node := ds.new_node(third_value)
	first_node.set_next(second_node)
	next_node := first_node.next() or {
		assert false, '${subject} should link the initialized next node'
		return
	}
	assert next_node.value() == third_value, '${subject} should traverse the linked next node'
	assert second_node.next() == none, '${subject} should leave the linked node next absent'
}

fn assert_linked_list_cases(subject string) {
	mut list := ds.new_linked_list()
	assert list.is_empty(), '${subject} should report an initialized empty list'
	assert list.size() == empty_size, '${subject} should report zero for an initialized empty list'
	assert list.head() == failure_value, '${subject} should return the failure indicator for an empty list head'

	list.insert_tail(second_value)
	list.insert_tail(third_value)
	list.insert_head(first_value)
	list.insert_tail(second_value)
	assert list.size() == 4, '${subject} should count inserts at both ends'
	assert list.head() == first_value, '${subject} should keep the head insertion first'

	assert list.delete(second_value), '${subject} should delete the first matching value'
	assert list.size() == 3, '${subject} should decrease the size after deleting the first match'
	assert list.head() == first_value, '${subject} should preserve the head after deleting an interior value'

	assert !list.delete(absent_value), '${subject} should return failure for an absent value'
	assert list.size() == 3, '${subject} should preserve size after an absent deletion'
	assert list.head() == first_value, '${subject} should preserve order after an absent deletion'

	assert list.delete(first_value), '${subject} should delete the head value'
	assert list.head() == third_value, '${subject} should advance the head after deleting it'
	assert list.delete(third_value), '${subject} should delete the remaining middle value'
	assert list.head() == second_value, '${subject} should retain the final tail as head'
	assert list.delete(second_value), '${subject} should delete the final value'
	assert list.is_empty(), '${subject} should report empty after deleting every value'
	assert list.size() == empty_size, '${subject} should report zero after deleting every value'
	assert list.head() == failure_value, '${subject} should return the failure indicator after emptying the list'
}

fn assert_stack_cases(subject string) {
	mut stack := ds.new_stack()
	assert stack.is_empty(), '${subject} should report an initialized empty stack'
	assert stack.size() == empty_size, '${subject} should report zero for an initialized empty stack'
	assert stack.peek() == failure_value, '${subject} should return the failure indicator when peeking an empty stack'
	assert stack.pop() == failure_value, '${subject} should return the failure indicator when popping an empty stack'

	stack.push(second_value)
	stack.push(third_value)
	stack.push(fourth_value)
	assert stack.peek() == fourth_value, '${subject} should peek the most recently pushed value'
	assert stack.size() == 3, '${subject} should not mutate size while peeking'

	assert stack.pop() == fourth_value, '${subject} should pop values in LIFO order'
	stack.push(reused_value)
	assert stack.pop() == reused_value, '${subject} should pop a value pushed after reuse'
	assert stack.pop() == third_value, '${subject} should retain LIFO order after reuse'
	assert stack.pop() == second_value, '${subject} should pop the first pushed value last'
	assert stack.is_empty(), '${subject} should report empty after popping every value'
	assert stack.size() == empty_size, '${subject} should report zero after popping every value'

	assert stack.pop() == failure_value, '${subject} should return the failure indicator after emptying the stack'
	assert stack.is_empty(), '${subject} should remain empty after a failed pop'
}

fn assert_queue_cases(subject string) {
	mut queue := ds.new_queue()
	assert queue.is_empty(), '${subject} should report an initialized empty queue'
	assert queue.size() == empty_size, '${subject} should report zero for an initialized empty queue'
	assert queue.peek() == failure_value, '${subject} should return the failure indicator when peeking an empty queue'
	assert queue.dequeue() == failure_value, '${subject} should return the failure indicator when dequeuing an empty queue'

	queue.enqueue(second_value)
	queue.enqueue(third_value)
	queue.enqueue(fourth_value)
	assert queue.peek() == second_value, '${subject} should peek the first enqueued value'
	assert queue.size() == 3, '${subject} should not mutate size while peeking'

	assert queue.dequeue() == second_value, '${subject} should dequeue values in FIFO order'
	queue.enqueue(reused_value)
	assert queue.dequeue() == third_value, '${subject} should retain FIFO order after reuse'
	assert queue.dequeue() == fourth_value, '${subject} should dequeue the third enqueued value next'
	assert queue.dequeue() == reused_value, '${subject} should dequeue the reused value last'
	assert queue.is_empty(), '${subject} should report empty after dequeuing every value'
	assert queue.size() == empty_size, '${subject} should report zero after dequeuing every value'

	assert queue.dequeue() == failure_value, '${subject} should return the failure indicator after emptying the queue'
	assert queue.is_empty(), '${subject} should remain empty after a failed dequeue'
}

fn test_new_node() {
	assert_node_cases('new_node')
}

fn test_node_value() {
	assert_node_cases('Node.value')
}

fn test_node_next() {
	assert_node_cases('Node.next')
}

fn test_node_set_next() {
	assert_node_cases('Node.set_next')
}

fn test_new_linked_list() {
	assert_linked_list_cases('new_linked_list')
}

fn test_linked_list_head() {
	assert_linked_list_cases('LinkedList.head')
}

fn test_linked_list_is_empty() {
	assert_linked_list_cases('LinkedList.is_empty')
}

fn test_linked_list_size() {
	assert_linked_list_cases('LinkedList.size')
}

fn test_linked_list_insert_head() {
	assert_linked_list_cases('LinkedList.insert_head')
}

fn test_linked_list_insert_tail() {
	assert_linked_list_cases('LinkedList.insert_tail')
}

fn test_linked_list_delete() {
	assert_linked_list_cases('LinkedList.delete')
}

fn test_new_stack() {
	assert_stack_cases('new_stack')
}

fn test_stack_is_empty() {
	assert_stack_cases('Stack.is_empty')
}

fn test_stack_size() {
	assert_stack_cases('Stack.size')
}

fn test_stack_push() {
	assert_stack_cases('Stack.push')
}

fn test_stack_pop() {
	assert_stack_cases('Stack.pop')
}

fn test_stack_peek() {
	assert_stack_cases('Stack.peek')
}

fn test_new_queue() {
	assert_queue_cases('new_queue')
}

fn test_queue_is_empty() {
	assert_queue_cases('Queue.is_empty')
}

fn test_queue_size() {
	assert_queue_cases('Queue.size')
}

fn test_queue_enqueue() {
	assert_queue_cases('Queue.enqueue')
}

fn test_queue_dequeue() {
	assert_queue_cases('Queue.dequeue')
}

fn test_queue_peek() {
	assert_queue_cases('Queue.peek')
}
