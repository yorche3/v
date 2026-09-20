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

pub fn selection_sort(arr []int) []int {
	mut result := arr.clone()
	n := result.len
	if n < 2 {
		return result
	}
	for i in 0 .. n - 1 {
		mut min_index := i
		for j in i + 1 .. n {
			if result[j] < result[min_index] {
				min_index = j
			}
		}
		if min_index != i {
			result[i], result[min_index] = result[min_index], result[i]
		}
	}
	return result
}

pub fn bubble_sort(arr []int) []int {
	mut result := arr.clone()
	n := result.len
	if n < 2 {
		return result
	}
	for i in 0 .. n - 1 {
		mut swapped := false
		for j in 0 .. n - 1 - i {
			if result[j] > result[j + 1] {
				result[j], result[j + 1] = result[j + 1], result[j]
				swapped = true
			}
		}
		if !swapped {
			break
		}
	}
	return result
}

pub fn insertion_sort(arr []int) []int {
	mut result := arr.clone()
	n := result.len
	if n < 2 {
		return result
	}
	for i in 1 .. n {
		key := result[i]
		mut j := i - 1
		for j >= 0 && result[j] > key {
			result[j + 1] = result[j]
			j--
		}
		result[j + 1] = key
	}
	return result
}