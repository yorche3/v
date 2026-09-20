// naive_sort — ordenamientos elementales O(n²).
//
// Especificación: 05_Naive_Sort
//
// Contrato: las tres funciones reciben un array de enteros y devuelven el array
// ordenado de menor a mayor (in-place o como copia ordenada), sin invocar
// `sort` ni ninguna otra ayuda de ordenamiento de la biblioteca estándar y sin
// estructuras auxiliares complejas. Los arrays de V son valores, así que el
// resultado vuelve por el valor devuelto.
// API (naming snake_case, el mismo de la especificación y de `core/foundations/
// numbers/`): `selection_sort`, `bubble_sort` e `insertion_sort`, públicas del
// módulo `src`.
// El caso nulo se omite: en V `[]int` es un tipo de valor y no admite `null`.
// Si el array está vacío o tiene un solo elemento se devuelve sin cambios. No
// lanza excepciones.
//
// Implementación pendiente: la escribe el autor. Esta delegación solo genera el
// esqueleto y las pruebas unitarias.

module src

pub fn selection_sort(array []int) []int {
	mut array := array.clone()
	n := array.len
	if n < 2 {
		return array
	}
	for i in 0 .. n - 1 {
		mut min_index := i
		for j in i + 1 .. n {
			if array[j] < array[min_index] {
				min_index = j
			}
		}
		if min_index != i {
			array[i], array[min_index] = array[min_index], array[i]
		}
	}
	return array
}

pub fn bubble_sort(array []int) []int {
	mut array := array.clone()
	n := array.len
	if n < 2 {
		return array
	}
	for i in 0 .. n - 1 {
		mut swapped := false
		for j in 0 .. n - 1 - i {
			if array[j] > array[j + 1] {
				array[j], array[j + 1] = array[j + 1], array[j]
				swapped = true
			}
		}
		if !swapped {
			break
		}
	}
	return array
}

pub fn insertion_sort(array []int) []int {
	mut array := array.clone()
	n := array.len
	if n < 2 {
		return array
	}
	for i in 1 .. n {
		key := array[i]
		mut j := i - 1
		for j >= 0 && array[j] > key {
			array[j + 1] = array[j]
			j--
		}
		array[j + 1] = key
	}
	return array
}