from math import gcd
import random
import sympy as sp

# 2. Pollard’s ρ algorithm. The implicit function will be f(x) = x^2 + 1, but it will also allow the use
# of a function f given by the user.
def pollards_rho(n, f):
    if f is None:
        f = default_f

    x = (random.randint(0, 2) % (n - 2)) # x0
    y = x
    d = 1

    while d == 1:
        x = f(x) % n  # tortoise move
        y = f(f(y)) % n  # hare move
        d = gcd(abs(x - y), n)

    if d == n:
        return pollards_rho(n, f)  # algorithm failed, try again with a different initial value
    else:
        return d  # found a non-trivial factor

def default_f(x):
    return x**2 + 1

def get_user_defined_function():
    print("\nThe function ax^2 + bx + c is represented as a*x**2 + b*x + c")
    expression = input("Enter a mathematical expression for the function in terms of 'x': ")
    x = sp.symbols('x')
    user_defined_function = sp.lambdify(x, expression, 'numpy')
    return user_defined_function

if __name__ == '__main__':
    user_choice = input("Do you want to use the default function? (y/n): ").lower()

    if user_choice == 'y':
        user_function = None  # use the default function
    else:
        user_function = get_user_defined_function()

    n = 7123
    factor = pollards_rho(n, user_function)
    print("Factors: {}, {}".format(factor, n // factor))
