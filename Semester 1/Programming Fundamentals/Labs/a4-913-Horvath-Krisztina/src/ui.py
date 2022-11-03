"""
  User interface module
"""


def print_number(nr):
    #  prints one complex number
    from functions import get_real, get_imag
    a = get_real(nr)
    b = get_imag(nr)
    if a == 0 and b == 0:
        print(0)
    elif a == 0:
        print(str(b) + "i")
    elif b == 0:
        print(str(a))
    else:
        if b < 0:
            print(str(a) + str(b) + "i")
        else:
            print(str(a) + "+" + str(b) + "i")


def print_list(l):
    #  prints all the elements of the list 'l' as complex numbers
    from functions import get_real, get_imag
    for i in range(len(l)):
        a = get_real(l[i])
        b = get_imag(l[i])
        if a == 0 and b == 0:
            print(0)
        elif a == 0:
            print(str(b) + "i")
        elif b == 0:
            print(str(a))
        else:
            if b < 0:
                print(str(a) + str(b) + "i")
            else:
                print(str(a) + "+" + str(b) + "i")


def print_list_real(l, start, finish):
    """
    Writes on the screen just the real part of the complex numbers starting from position start to finish
    :param l: the list with the complex numbers
    :param start: the starting position of the sequence
    :param finish: the finishing position of the sequence
    """
    from functions import get_real, get_imag
    for i in range(start, finish):
        if get_imag(l[i]) == 0:
            print(get_real(l[i]))


def print_list_modulus(l, nr: int, sign):
    """
    Displays the complex numbers that are less, equal or greater than a given number.
    :param l: list of complex numbers
    :param nr: an integer
    :param sign: a character which is '<', '=' or '>'
    """
    from functions import modulus
    if sign == '<':
        for i in range(0, len(l)):
            if modulus(l[i]) < nr:
                print_number(l[i])
    elif sign == '=':
        for i in range(0, len(l)):
            if modulus(l[i]) == nr:
                print_number(l[i])
    else:
        for i in range(0, len(l)):
            if modulus(l[i]) > nr:
                print_number(l[i])
