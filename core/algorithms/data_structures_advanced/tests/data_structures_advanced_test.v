// Casos de prueba de la especificación 07_Data_Structures_Advanced.md:
// TreeNode (6 filas), BinaryTree (7) y Graph (11); 24 filas, 23 tests.
//
// Adaptaciones: V representa la ausencia de enlace con `none` en `?&TreeNode`
// y el fallo de `neighbors` con el `bool` de su segundo resultado (distinto de
// un `[]int` vacío con éxito). `TreeNode` muta en sitio, así que la fila
// «Adaptación inmutable (si aplica)» no aplica. Cada test crea instancias nuevas.

import data_structures_advanced.src as ds

const parent_value = 10
const left_value = 20
const right_value = 30
const absent_value = 99

fn assert_links(subject string, node &ds.TreeNode, want_left bool, want_right bool) {
	assert (node.left() != none) == want_left, '${subject} should report left link presence ${want_left}'
	assert (node.right() != none) == want_right, '${subject} should report right link presence ${want_right}'
}

fn linked_parent() &ds.TreeNode {
	mut parent := ds.new_tree_node(parent_value)
	parent.set_left(ds.new_tree_node(left_value))
	parent.set_right(ds.new_tree_node(right_value))
	return parent
}

fn insert_all(subject string, mut tree ds.BinaryTree, values []int) {
	for value in values {
		assert tree.insert(value), '${subject} should insert ${value}'
	}
}

fn assert_tree_state(subject string, tree &ds.BinaryTree, present []int, size int) {
	assert tree.size() == size, '${subject} should report size ${size}'
	assert tree.is_empty() == (size == 0), '${subject} should report emptiness for size ${size}'
	for value in present {
		assert tree.contains(value), '${subject} should contain ${value}'
	}
}

fn add_vertices(subject string, mut graph ds.Graph, labels []int) {
	for label in labels {
		assert graph.add_vertex(label), '${subject} should register vertex ${label}'
	}
}

fn assert_counts(subject string, graph &ds.Graph, vertices int, edges int) {
	assert graph.vertex_count() == vertices, '${subject} should report ${vertices} vertices'
	assert graph.edge_count() == edges, '${subject} should report ${edges} edges'
	assert graph.is_empty() == (vertices == 0), '${subject} should report emptiness for ${vertices} vertices'
}

fn assert_neighbors(subject string, graph &ds.Graph, label int, want []int) {
	got, ok := graph.neighbors(label)
	assert ok, '${subject} should find neighbours of ${label}'
	assert got == want, '${subject} should list neighbours ${want} of ${label}'
}

fn assert_no_neighbors_result(subject string, graph &ds.Graph, label int) {
	_, ok := graph.neighbors(label)
	assert !ok, '${subject} should fail neighbours of missing vertex ${label}'
}

// TreeNode

fn test_tree_node_create() {
	node := ds.new_tree_node(parent_value)
	assert node.value() == parent_value, 'TreeNode create should preserve the initialized value'
}

fn test_tree_node_initial_links_absent() {
	node := ds.new_tree_node(parent_value)
	assert node.left() == none, 'TreeNode initial links should leave left absent'
	assert node.right() == none, 'TreeNode initial links should leave right absent'
}

fn test_tree_node_link_two_children() {
	parent := linked_parent()
	left := parent.left() or {
		assert false, 'TreeNode link should expose the left child'
		return
	}
	right := parent.right() or {
		assert false, 'TreeNode link should expose the right child'
		return
	}
	assert left.value() == left_value, 'TreeNode link should store the left value'
	assert right.value() == right_value, 'TreeNode link should store the right value'
}

fn test_tree_node_traverse_each_link() {
	parent := linked_parent()
	left := parent.left() or {
		assert false, 'TreeNode traverse should follow left'
		return
	}
	right := parent.right() or {
		assert false, 'TreeNode traverse should follow right'
		return
	}
	assert left.value() == left_value, 'TreeNode traverse should lead left to 20'
	assert right.value() == right_value, 'TreeNode traverse should lead right to 30'
	assert_links('TreeNode traverse left child', left, false, false)
	assert_links('TreeNode traverse right child', right, false, false)
}

fn test_tree_node_unlink_children() {
	mut parent := linked_parent()
	parent.set_left(none)
	assert parent.value() == parent_value, 'TreeNode unlink left should preserve value 10'
	assert_links('TreeNode unlink left', parent, false, true)
	right := parent.right() or {
		assert false, 'TreeNode unlink left should preserve the right child'
		return
	}
	assert right.value() == right_value, 'TreeNode unlink left should preserve right child 30'
	parent.set_right(none)
	assert parent.value() == parent_value, 'TreeNode unlink right should preserve value 10'
	assert_links('TreeNode unlink right', parent, false, false)
}

// BinaryTree

fn test_binary_tree_create_empty() {
	tree := ds.new_binary_tree()
	assert_tree_state('BinaryTree create empty', tree, [], 0)
	assert !tree.contains(50), 'BinaryTree create empty should not contain 50'
}

fn test_binary_tree_insert_root() {
	mut tree := ds.new_binary_tree()
	insert_all('BinaryTree insert root', mut tree, [50])
	assert_tree_state('BinaryTree insert root', tree, [50], 1)
}

fn test_binary_tree_insert_lower_and_higher() {
	mut tree := ds.new_binary_tree()
	insert_all('BinaryTree lower and higher', mut tree, [50, 30, 70])
	assert_tree_state('BinaryTree lower and higher', tree, [50, 30, 70], 3)
}

fn test_binary_tree_multilevel_branches() {
	mut tree := ds.new_binary_tree()
	insert_all('BinaryTree multilevel', mut tree, [50, 30, 70, 20, 40])
	assert_tree_state('BinaryTree multilevel', tree, [50, 30, 70, 20, 40], 5)
}

fn test_binary_tree_missing_value_in_nonempty_tree() {
	mut tree := ds.new_binary_tree()
	insert_all('BinaryTree missing value', mut tree, [50])
	assert !tree.contains(absent_value), 'BinaryTree missing value should not contain 99'
	assert_tree_state('BinaryTree missing value', tree, [50], 1)
}

fn test_binary_tree_idempotent_duplicate() {
	mut tree := ds.new_binary_tree()
	insert_all('BinaryTree duplicate', mut tree, [50, 30, 70, 30])
	assert_tree_state('BinaryTree duplicate', tree, [50, 30, 70], 3)
}

fn test_binary_tree_ordered_insertions() {
	mut tree := ds.new_binary_tree()
	insert_all('BinaryTree ordered', mut tree, [20, 30, 40, 50, 70])
	assert_tree_state('BinaryTree ordered', tree, [20, 30, 40, 50, 70], 5)
	assert !tree.contains(absent_value), 'BinaryTree ordered should not contain 99'
}

// Graph

fn test_graph_create_empty() {
	graph := ds.new_graph()
	assert_counts('Graph create empty', graph, 0, 0)
	assert !graph.has_edge(10, 30), 'Graph create empty should fail has_edge(10, 30)'
	assert_no_neighbors_result('Graph create empty', graph, 10)
}

fn test_graph_isolated_vertex() {
	mut graph := ds.new_graph()
	add_vertices('Graph isolated vertex', mut graph, [10])
	assert_counts('Graph isolated vertex', graph, 1, 0)
	assert_neighbors('Graph isolated vertex', graph, 10, [])
}

fn test_graph_nonconsecutive_labels_directed_edge() {
	mut graph := ds.new_graph()
	add_vertices('Graph directed edge', mut graph, [10, 70])
	assert graph.add_edge(10, 70), 'Graph directed edge should add 10 -> 70'
	assert graph.has_edge(10, 70), 'Graph directed edge should report forward edge'
	assert !graph.has_edge(70, 10), 'Graph directed edge should not report reverse edge'
	assert_counts('Graph directed edge', graph, 2, 1)
}

fn test_graph_duplicate_vertex_preserves_adjacency() {
	mut graph := ds.new_graph()
	add_vertices('Graph duplicate vertex', mut graph, [10, 30])
	assert graph.add_edge(10, 30), 'Graph duplicate vertex should add 10 -> 30'
	assert graph.add_vertex(10), 'Graph duplicate vertex should succeed on repeated 10'
	assert_counts('Graph duplicate vertex', graph, 2, 1)
	assert_neighbors('Graph duplicate vertex', graph, 10, [30])
}

fn test_graph_duplicate_edge() {
	mut graph := ds.new_graph()
	add_vertices('Graph duplicate edge', mut graph, [10, 30])
	assert graph.add_edge(10, 30), 'Graph duplicate edge should add 10 -> 30 first time'
	assert graph.add_edge(10, 30), 'Graph duplicate edge should succeed the second time'
	assert_counts('Graph duplicate edge', graph, 2, 1)
	assert_neighbors('Graph duplicate edge', graph, 10, [30])
}

fn test_graph_missing_endpoint_without_mutation() {
	mut graph := ds.new_graph()
	add_vertices('Graph missing endpoint', mut graph, [10, 30])
	assert graph.add_edge(10, 30), 'Graph missing endpoint should add 10 -> 30'
	assert !graph.add_edge(10, 99), 'Graph missing endpoint should fail (10, 99)'
	assert !graph.add_edge(99, 10), 'Graph missing endpoint should fail (99, 10)'
	assert !graph.add_edge(98, 99), 'Graph missing endpoint should fail (98, 99)'
	assert !graph.add_edge(99, 99), 'Graph missing endpoint should fail (99, 99)'
	assert_counts('Graph missing endpoint', graph, 2, 1)
	assert_neighbors('Graph missing endpoint', graph, 10, [30])
	assert_neighbors('Graph missing endpoint', graph, 30, [])
	assert !graph.has_edge(10, 99), 'Graph missing endpoint should keep (10, 99) absent'
	assert !graph.has_edge(99, 10), 'Graph missing endpoint should keep (99, 10) absent'
	assert !graph.has_edge(98, 99), 'Graph missing endpoint should keep (98, 99) absent'
	assert !graph.has_edge(99, 99), 'Graph missing endpoint should keep (99, 99) absent'
	assert_no_neighbors_result('Graph missing endpoint', graph, 98)
	assert_no_neighbors_result('Graph missing endpoint', graph, 99)
}

fn test_graph_sorted_neighbors_and_counts() {
	mut graph := ds.new_graph()
	add_vertices('Graph sorted neighbours', mut graph, [10, 30, 50, 70])
	assert graph.add_edge(10, 70), 'Graph sorted neighbours should add 10 -> 70'
	assert graph.add_edge(10, 30), 'Graph sorted neighbours should add 10 -> 30'
	assert graph.add_edge(10, 50), 'Graph sorted neighbours should add 10 -> 50'
	assert graph.add_edge(30, 50), 'Graph sorted neighbours should add 30 -> 50'
	assert_neighbors('Graph sorted neighbours', graph, 10, [30, 50, 70])
	assert_neighbors('Graph sorted neighbours', graph, 30, [50])
	assert_neighbors('Graph sorted neighbours', graph, 50, [])
	assert_neighbors('Graph sorted neighbours', graph, 70, [])
	assert_counts('Graph sorted neighbours', graph, 4, 4)
}

fn test_graph_missing_edge_query() {
	mut graph := ds.new_graph()
	add_vertices('Graph missing edge', mut graph, [10, 30])
	assert !graph.has_edge(10, 30), 'Graph missing edge should fail has_edge(10, 30)'
	assert_counts('Graph missing edge', graph, 2, 0)
}

fn test_graph_neighbors_of_missing_vertex() {
	mut graph := ds.new_graph()
	add_vertices('Graph missing vertex', mut graph, [10])
	assert_no_neighbors_result('Graph missing vertex', graph, absent_value)
	assert_neighbors('Graph missing vertex', graph, 10, [])
	assert_counts('Graph missing vertex', graph, 1, 0)
}

fn test_graph_self_loop_and_duplicate() {
	mut graph := ds.new_graph()
	add_vertices('Graph self-loop', mut graph, [10])
	assert graph.add_edge(10, 10), 'Graph self-loop should add 10 -> 10'
	assert graph.add_edge(10, 10), 'Graph self-loop should succeed on the duplicate'
	assert graph.has_edge(10, 10), 'Graph self-loop should report the loop'
	assert_neighbors('Graph self-loop', graph, 10, [10])
	assert_counts('Graph self-loop', graph, 1, 1)
}

fn test_graph_neighbor_result_isolation() {
	mut graph := ds.new_graph()
	add_vertices('Graph isolation', mut graph, [10, 30, 50])
	assert graph.add_edge(10, 30), 'Graph isolation should add 10 -> 30'
	saved, saved_ok := graph.neighbors(10)
	assert saved_ok, 'Graph isolation should find neighbours of 10'
	mut copy, copy_ok := graph.neighbors(10)
	assert copy_ok, 'Graph isolation should return a second copy'
	copy << absent_value
	copy[0] = absent_value
	assert graph.add_edge(10, 50), 'Graph isolation should add 10 -> 50'
	assert saved == [30], 'Graph isolation should keep the saved result [30]'
	assert_neighbors('Graph isolation', graph, 10, [30, 50])
	assert_counts('Graph isolation', graph, 3, 2)
}
