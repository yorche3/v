import numbers.src

fn test_sum_of_first_n_rec() {
    assert src.sum_of_first_n_rec(0) == 0
    assert src.sum_of_first_n_rec(3) == 6
}

fn test_factorial_rec() {
    assert src.factorial_rec(0) == 1
    assert src.factorial_rec(4) == 24
}

fn test_fibonacci_rec() {
    assert src.fibonacci_rec(0) == 0
    assert src.fibonacci_rec(1) == 1
    assert src.fibonacci_rec(6) == 8
}

fn test_greatest_common_divisor_rec() {
    assert src.greatest_common_divisor_rec(12, 8) == 4
    assert src.greatest_common_divisor_rec(7, 5) == 1
}

fn test_least_common_multiple_rec() {
    assert src.least_common_multiple_rec(4, 6) == 12
    assert src.least_common_multiple_rec(6, 8) == 24
}
