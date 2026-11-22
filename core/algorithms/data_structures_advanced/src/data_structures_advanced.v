module src

@[heap]
pub struct TreeNode {
mut:
	value int
	left  ?&TreeNode
	right ?&TreeNode
}

pub fn new_tree_node(value int) &TreeNode {
	return &TreeNode{}
}

pub fn (node &TreeNode) value() int {
	return 0
}

pub fn (node &TreeNode) left() ?&TreeNode {
	return none
}

pub fn (node &TreeNode) right() ?&TreeNode {
	return none
}

pub fn (mut node TreeNode) set_left(left ?&TreeNode) {
}

pub fn (mut node TreeNode) set_right(right ?&TreeNode) {
}

pub struct BinaryTree {
mut:
	root  ?&TreeNode
	count int
}

pub fn new_binary_tree() &BinaryTree {
	return &BinaryTree{}
}

pub fn (mut tree BinaryTree) insert(value int) bool {
	return false
}

pub fn (tree &BinaryTree) contains(value int) bool {
	return false
}

pub fn (tree &BinaryTree) is_empty() bool {
	return false
}

pub fn (tree &BinaryTree) size() int {
	return 0
}

@[heap]
struct NeighborNode {
mut:
	label int
	next  ?&NeighborNode
}

@[heap]
struct GraphNode {
mut:
	value       int
	neighbors   ?&NeighborNode
	next_vertex ?&GraphNode
}

fn new_graph_node(_ int) &GraphNode {
	return &GraphNode{}
}

pub struct Graph {
mut:
	vertices     ?&GraphNode
	vertex_total int
	edges        int
}

pub fn new_graph() &Graph {
	return &Graph{}
}

pub fn (mut graph Graph) add_vertex(label int) bool {
	return false
}

pub fn (mut graph Graph) add_edge(u int, v int) bool {
	return false
}

pub fn (graph &Graph) has_edge(u int, v int) bool {
	return false
}

pub fn (graph &Graph) neighbors(u int) ([]int, bool) {
	return []int{}, false
}

pub fn (graph &Graph) is_empty() bool {
	return false
}

pub fn (graph &Graph) vertex_count() int {
	return 0
}

pub fn (graph &Graph) edge_count() int {
	return 0
}
