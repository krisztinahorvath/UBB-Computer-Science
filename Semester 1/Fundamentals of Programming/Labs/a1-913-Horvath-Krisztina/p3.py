# Solve the problem from the third set here

# 13.Determine the n-th element of the sequence 1,2,3,2,5,2,3,7,2,3,2,5,...
# obtained from the sequence of natural numbers by replacing composed numbers with
# their prime divisors, without memorizing the elements of the sequence.

def primeDivisors(n: int, crtNr: int, crtIndex: int):
    """
    This function decomposes numbers into their prime divisors(works on prime numbers too - crtIndex modification)
    :param n: the given number
    :param crtNr: current number from the sequence, which has to be decomposed in prime numbers
    :param crtIndex: current index of the number in the sequence
    :return: 0 and current index, if we didn't find the number with the nth index
             the nth number in the sequence and 0
    """
    d = 2
    while crtNr != 1:
        if crtNr % d == 0:
            crtIndex += 1
            if crtIndex == n:
                return d, 0
        while crtNr % d == 0:
            crtNr /= d
        d += 1
    return 0, crtIndex


def determineElement(n: int):
    # Determines the nth number of the sequence, and it returns it.

    crtNr = 1  # current number:1, 2, 3, 4, 5 etc.
    crtIndex = 1  # current index of crtNr in the sequence
    if n == 1:  # we verify if 1 is the nth number separately, because the used function for that misses this case
        return 1
    number = 0  # number - the number that we are trying to find(the nth in the sequence)
    while number == 0:
        number, crtIndex = primeDivisors(n, crtNr, crtIndex)
        crtNr += 1
    return number


def read():  # reads and validates the input
    n = int(input("Give a natural value for n = "))
    if n <= 0:
        return -1
    return n


def write():  # prints out the result
    n = read()
    if n == -1:
        print("Invalid input, please introduce a natural number!")
    else :
        print("The nth number of the sequence is: " + str(determineElement(n)))


write()
