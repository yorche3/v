import calculator.src

fn test_addition() {
    assert src.addition(2, 3) == 5
}

fn test_subtraction() {
    assert src.subtraction(5, 2) == 3
}

fn test_multiplication() {
    assert src.multiplication(3, 4) == 12
}

fn test_division() {
    assert src.division(10, 3) == 3
}

fn test_modulus() {
    assert src.modulus(10, 3) == 1
}
