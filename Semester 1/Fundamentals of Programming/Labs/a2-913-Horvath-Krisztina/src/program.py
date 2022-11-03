# properties: 7,11

# UI section
# (write all functions that have input or print statements here). 
# Ideally, this section should not contain any calculations relevant to program functionalities

import math


def read(l):  # reads the complex numbers
    n = int(input("Please say how long your sequence of complex numbers will be = "))
    print("Please introduce " + str(n) + " complex numbers!")
    print("Start with the real part, then the imaginary one for each number.")
    for i in range(n):
        c = [0, 0]  # a complex number
        c[0] = int(input("Re = "))
        c[1] = int(input("Im = "))
        l.append(c)


def write_sequence(l, start, finish):
    """
    Prints a sequence of complex numbers from a starting point to a finishing point
    :param l: the list with the complex numbers
    :param start: the starting position from where we want to print the numbers
    :param finish: the position where the printing stops
    """
    i = start
    while i < finish:
        real = get_real(l[i])
        imag = get_imag(l[i])
        if real == 0 and imag == 0:
            print(0)
        elif real == 0:
            print(str(imag) + "i")
        elif imag == 0:
            print(real)
        else:
            print(str(get_real(l[i])) + " + " + str(get_imag(l[i])) + "i")
        i += 1


def print_menu():
    print("Press the following keys to navigate through the menu options:")
    print("\tr to read a sequence of complex numbers ")
    print("\tw to display all the numbers from the list")
    print("\t1 to display the longest sequence with property P7")
    print("\t2 to display the longest sequence with property P11")
    print("\tx to exit the application")


def main():
    l = [[3, 2], [5, 7], [3, 2], [0, 0], [5, 2], [4, 1], [12, 4], [2, 10], [7, 2], [5, 2]]
    # list with all the complex numbers, i chose these numbers because they work for both properties
    n = len(l)
    while True:
        print_menu()
        option = input("Option: ")
        if option == 'r':
            l.clear()  # we empty the list so that we can read new numbers
            read(l)
            n = len(l)
        elif option == 'w':
            write_sequence(l, 0, n)
        elif option == '1':
            start, finish = solve_P7(l)
            if start == -1:
                print("\tThere is no sequence in the list with that property.")
            else:
                write_sequence(l, start, finish)
        elif option == '2':
            start, finish = mountain(l)
            if start == -1:
                print("\tThere is no sequence in the list with that property.")
            else:
                write_sequence(l, start, finish + 1)
        elif option == 'x':
            return
        else:
            print("\tInvalid input!")


# Function section
# (write all non-UI functions in this section)
# There should be no print or input statements below this comment
# Each function should do one thing only
# Functions communicate using input parameters and their return values
# print('Hello A2'!) -> prints aren't allowed here!

# P7
def is_prime(n: int):
    """
    Verifies if the integer n is a prime number.
    :param n: an integer number
    :return: True - for prime numbers
             False - for numbers that aren't prime
    """
    if n < 2:
        return False
    d = 2
    while d * d <= n:
        if n % d == 0:
            return False
        d += 2
    return True


def modulus(z):  # returns the modulus of z, a complex number (|z|)
    return int(math.sqrt(get_real(z) * get_real(z) + get_imag(z) * get_imag(z)))


def test_modulus():  # tests the function modulus()
    assert modulus([2, 1]) == 2
    assert modulus([7, -2]) == 7
    assert modulus([3, 2]) == 3


def difference_modulus(a, b):  # returns the difference: |a|-|b|, a and b - complex numbers
    return int(modulus(a) - modulus(b))


def solve_P7(l):
    """
    We find and return the starting and finishing position of the longest sequence having property P7.
    :param l: the list with the complex numbers
    :return: the position where the longest sequence with P7 starts and where it ends
             if there is no sequence with P7 then -1, -1
    """
    max_length = -1  # the length of the longest sequence
    max_start = -1  # the starting position of the longest sequence
    max_finish = -1  # the finishing position of the longest sequence
    current_length = 0  # the length of the current sequence
    start = -1  # the starting position of the current sequence
    for i in range(0, len(l) - 1):
        if is_prime(difference_modulus(l[i], l[i + 1])):
            # we verify if the current pair of consecutive numbers holds for P7
            current_length += 1
            if start == -1:  # a new sequence starts and we memorize its starting position
                start = i
        elif start != -1:
            current_length += 1
            # we add one to get the correct length,
            # because we verify in pairs and only count one number in each verification
            if max_length <= current_length:
                # we memorize the position of the last longest sequence with P7(if there are more with the same length)
                # we memorize the maximum sequences length, starting and ending position
                max_length = current_length
                max_start = start
                max_finish = i
                start = -1  # reinit and current_length for the next sequences
                current_length = 0
    if start != -1 and max_length <= current_length + 1:
        # we verify the last sequence separately, because if the longest sequence ends on the last position of l,
        # we don't get the correct length/sequence
        max_start = start
        max_finish = len(l)
    return max_start, max_finish


# P11
def mountain(l):
    """
    Finds and returns the starting and ending position of the longest sequence where the real part is in form of a mountain
    :param l: the list with the complex numbers
    :return: the position where the longest sequence with P11 starts and where it ends
             if there is no sequence with P11 then -1, -1
    """
    max_length = 0  # the length of the longest sequence
    max_start = -1  # the starting position of the longest sequence
    max_finish = -1  # the finishing position of the longest sequence
    current_length = 0  # the length of the current sequence
    start = -1  # the starting position of the current sequence
    m = 0  # mountain counter
    for i in range(0, len(l) - 1):
        if get_real(l[i]) < get_real(l[i + 1]):
            if m == 0 or m == 1:
                current_length += 1
                if start == -1:  # a new sequence starts and we memorize its starting position
                    start = i
                    m += 1   # m = 1 means that we found a mountain and its increasing
            else:  # reinitialize variables
                m = 0  # no mountain
                current_length = 0
                start = - 1
        else:
            if m == 1:   # m = 2 means that we found the decreasing part of a mountain
                m = 2
            if m == 2:   # we are in the decreasing part of the mountain
                current_length += 1
                # print("lung " + str(current_length))
                if max_length <= current_length:
                    max_length = current_length + 1
                    # we add one to get the correct length,
                    # because we verify in pairs and only count one number in each verification
                    max_start = start
                    max_finish = i + 1
    if m == 2:
        if max_length <= current_length + 1:
            # we verify the last sequence separately, because if the longest sequence ends on the last position of l,
            # we don't get the correct length/sequence
            max_start = start
            max_finish = len(l)
    return max_start, max_finish


def get_real(z):  # returns the real part of a complex number
    return z[0]


def get_imag(z):  # returns the imaginary part of a complex number
    return z[1]


main()
# test_modulus()
