import numbers.src

fn test_sum_of_first_n_ite() {
    assert src.sum_of_first_n_ite(0) == 0
    assert src.sum_of_first_n_ite(3) == 6
}

fn test_factorial_ite() {
    assert src.factorial_ite(0) == 1
    assert src.factorial_ite(4) == 24
}

fn test_fibonacci_ite() {
    assert src.fibonacci_ite(0) == 0
    assert src.fibonacci_ite(1) == 1
    assert src.fibonacci_ite(6) == 8
}

fn test_greatest_common_divisor_ite() {
    assert src.greatest_common_divisor_ite(12, 8) == 4
    assert src.greatest_common_divisor_ite(7, 5) == 1
}

fn test_least_common_multiple_ite() {
    assert src.least_common_multiple_ite(4, 6) == 12
    assert src.least_common_multiple_ite(6, 8) == 24
}
