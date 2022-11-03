# Solve the problem from the first set here
# problem numbers: 3, 6 ,13

# 3.For a given natural number n find the minimal natural number m formed with the same digits.
# (e.g. n=3658, m=3568). 100-100,3002-2003,3501,1035

def addDigits(n, fr):  # adds the frequencies of n's digits to fr(list)
    n = int(n)
    while n > 0:
        # d = n % 10    # current digit of n
        if n % 10 == 0:
            fr[0] += 1
        else:
            fr[n % 10] = fr[n % 10] + 1
        n = int(n / 10)


def multiplyDigits(m, digit, nr):
    """
     We add the digits of n as many times as they appear.
    :param m: the number that we are trying to form,from n's digits
    :param digit: the digit that we have to add to m
    :param nr: the number of times that the current digits appears in n
    :return: m
    """

    while nr != 0:
        m = m * 10 + digit
        nr -= 1
    return m


def newNumber(fr):  # here we create m, the minimal number formed with the digits of n
    m = 0
    zeroExists = 0
    if fr[0] != 0:  # we verify if there was a 0 in n
        zeroExists = 1
    for i in range(1, 10):
        if fr[i] > 0:  # if the digit i appears in n, then we add it to the new number(m)
            m = multiplyDigits(m, i, fr[i])
            if zeroExists == 1:  # we add 0 to the second position of m(from left to right) to obtain the smallest number possible
                zeroExists = 0
                m = multiplyDigits(m, 0, fr[0])
    return m


def read():  # reads and validates the input
    n = int(input("Give a natural value for n = "))
    if n <= 0:
        return -1
    return n


def write():  # writes and calculates the solution
    n = read()
    if n < 0:
        print("Invalid input, try introducing a natural number.")
    elif n < 10:
        print(n)
    else:
        fr = [0] * 10
        addDigits(n, fr)
        print("The minimal natural number m formed with the same digits as n is: " + str(newNumber(fr)))


write()
