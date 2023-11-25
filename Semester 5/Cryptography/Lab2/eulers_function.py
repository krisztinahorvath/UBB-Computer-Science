# 5. Algorithm for computing the value of Euler’s function for natural numbers. For a given value
# v and a given bound b, list all natural numbers less than b which have v as the value of Euler’s
# function.

# function to compute Euler's Totient Function φ(n) for a number n
# Euler's Totient function for a number n is the count of numbers in [1, n-1] that are relatively prime to n
# => gcd(x, n) = 1
def euler_function(n):
    result = n

    p = 2
    while p * p <= n:
        if n % p == 0:
            while n % p == 0:
                n = n // p
            result -= result // p  # subtract all multiples of p
        p += 1

    if n > 1:
        result -= result // n # remove all multiples of n from the result

    return result

def numbers_with_euler_value(v, b):
    numbers = []

    for nr in range(1, b):
        if euler_function(nr) == v:
            numbers.append(nr)

    return numbers


if __name__ == '__main__':
    v = 16 # value
    b = 100 # bound
    result = numbers_with_euler_value(v, b)
    print(f"All the natural numbers that are less than {b} with Euler's function value {v}: {result}")