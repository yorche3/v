module src

pub fn sum_of_first_n_rec(n int) int {
    if n <= 0 {
        return 0
    }
    return n + sum_of_first_n_rec(n - 1)
}

pub fn factorial_rec(n int) int {
    if n <= 1 {
        return 1
    }
    return n * factorial_rec(n - 1)
}

pub fn fibonacci_rec(n int) int {
    if n <= 1 {
        return n
    }
    return fibonacci_rec(n - 1) + fibonacci_rec(n - 2)
}

pub fn greatest_common_divisor_rec(a int, b int) int {
    if b == 0 {
        return a
    }
    return greatest_common_divisor_rec(b, a % b)
}

pub fn least_common_multiple_rec(a int, b int) int {
    if a == 0 || b == 0 {
        return 0
    }
    return (a / greatest_common_divisor_rec(a, b)) * b
}

pub fn sum_of_first_n_acc(n int) int {
    return sum_of_first_n_acc_help(n, 0)
}

fn sum_of_first_n_acc_help(current int, accumulator int) int {
    if current <= 0 {
        return accumulator
    }
    return sum_of_first_n_acc_help(current - 1, current + accumulator)
}

pub fn factorial_acc(n int) int {
    return factorial_acc_help(n, 1)
}

fn factorial_acc_help(current int, accumulator int) int {
    if current <= 1 {
        return accumulator
    }
    return factorial_acc_help(current - 1, current * accumulator)
}

pub fn fibonacci_acc(n int) int {
    return fibonacci_acc_help(n, 0, 1)
}

fn fibonacci_acc_help(position int, previous int, current int) int {
    if position <= 0 {
        return previous
    }
    if position == 1 {
        return current
    }
    return fibonacci_acc_help(position - 1, current, previous + current)
}

pub fn greatest_common_divisor_acc(a int, b int) int {
    return greatest_common_divisor_acc_help(a, b)
}

fn greatest_common_divisor_acc_help(a int, b int) int {
    if b == 0 {
        return a
    }
    return greatest_common_divisor_acc_help(b, a % b)
}

pub fn least_common_multiple_acc(a int, b int) int {
    if a == 0 || b == 0 {
        return 0
    }
    return (a / greatest_common_divisor_acc(a, b)) * b
}

pub fn sum_of_first_n_ite(n int) int {
    mut result := 0
    for current in 1 .. n + 1 {
        result += current
    }
    return result
}

pub fn factorial_ite(n int) int {
    mut result := 1
    for current in 2 .. n + 1 {
        result *= current
    }
    return result
}

pub fn fibonacci_ite(n int) int {
    if n <= 1 {
        return n
    }

    mut previous := 0
    mut current := 1
    for _ in 2 .. n + 1 {
        next := previous + current
        previous = current
        current = next
    }
    return current
}

pub fn greatest_common_divisor_ite(a int, b int) int {
    mut x := a
    mut y := b
    for y != 0 {
        remainder := x % y
        x = y
        y = remainder
    }
    return x
}

pub fn least_common_multiple_ite(a int, b int) int {
    if a == 0 || b == 0 {
        return 0
    }
    return (a / greatest_common_divisor_ite(a, b)) * b
}
