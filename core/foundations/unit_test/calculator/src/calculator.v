module src

pub fn addition(a int, b int) int {
    return a + b
}

pub fn subtraction(a int, b int) int {
    return a - b
}

pub fn multiplication(a int, b int) int {
    if b < 0 {
        panic('The multiplier must be non-negative')
    }

    mut result := 0
    for _ in 0 .. b {
        result = addition(result, a)
    }
    return result
}

pub fn division(a int, b int) int {
    if b <= 0 {
        panic('The divisor must be positive')
    }

    mut dividend := a
    mut quotient := 0
    for dividend >= b {
        dividend = subtraction(dividend, b)
        quotient++
    }
    return quotient
}

pub fn modulus(a int, b int) int {
    if b <= 0 {
        panic('The divisor must be positive')
    }

    quotient := division(a, b)
    product := multiplication(quotient, b)
    return subtraction(a, product)
}
