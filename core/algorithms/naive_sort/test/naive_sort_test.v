// Casos de prueba de la especificación 05_Naive_Sort.md
//
// Caso nulo omitido: en V `[]int` es un tipo de valor y no admite `null`; los
// opcionales (`?[]int`) se formalizan más adelante, en la fase de abstracción y
// persistencia. Se conservan los 7 casos de la especificación.
//
// Aislamiento: los arrays de V son valores, así que cada caso ordena una copia
// (`clone()`) del fixture compartido.

import naive_sort.src

struct SortCase {
	description string
	input       []int
	expected    []int
}

// Entradas y salidas de la especificación
const standard_input = [5, 2, 9, 1, 5, 6]
const standard_output = [1, 2, 5, 5, 6, 9]

const sorted_input = [1, 2, 3, 4, 5]
const sorted_output = [1, 2, 3, 4, 5]

const reverse_input = [5, 4, 3, 2, 1]
const reverse_output = [1, 2, 3, 4, 5]

const identical_input = [7, 7, 7, 7]
const identical_output = [7, 7, 7, 7]

const negative_input = [3, -1, 4, -5, 0]
const negative_output = [-5, -1, 0, 3, 4]

const single_input = [42]
const single_output = [42]

const empty_input = []int{}
const empty_output = []int{}

// Helper compartido: recibe el nombre del algoritmo y la función a probar, y
// ejecuta todos los casos con el mensaje descriptivo del contrato.
fn assert_sorts_all_cases(algorithm string, sort fn ([]int) []int) {
	cases := [
		SortCase{'an unsorted array', standard_input, standard_output},
		SortCase{'an already sorted array', sorted_input, sorted_output},
		SortCase{'a reverse ordered array', reverse_input, reverse_output},
		SortCase{'an array of identical elements', identical_input, identical_output},
		SortCase{'an array with negative numbers', negative_input, negative_output},
		SortCase{'a single element array', single_input, single_output},
		SortCase{'an empty array', empty_input, empty_output},
	]

	for test_case in cases {
		assert sort(test_case.input.clone()) == test_case.expected, '${algorithm} should sort ${test_case.description}'
	}
}

fn test_selection_sort() {
	assert_sorts_all_cases('selection_sort', src.selection_sort)
}

fn test_bubble_sort() {
	assert_sorts_all_cases('bubble_sort', src.bubble_sort)
}

fn test_insertion_sort() {
	assert_sorts_all_cases('insertion_sort', src.insertion_sort)
}
