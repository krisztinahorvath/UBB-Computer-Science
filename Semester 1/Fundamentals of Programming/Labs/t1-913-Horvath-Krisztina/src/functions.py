from random import choice



def random_secret_number():  #TODO give pram here
    """
    This function generates a random secret number as it follows: from a list with all the digits in it(0-9)
    we choose four times randomly a digit and add it to the new number, after we add a digit we remove it from
    the list with digits(distinct). The first digit can't be zero, so we do that separately.
    :param nr: the number that we have to generate, initially zero
    :return: random secret number
    """
    nr = 0
    digit = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    d = choice(digit)
    while d == 0:  # nr can't start with 0
        d = choice(digit)

    nr = d
    digit.remove(d)

    for i in range(0, 3):
        d = choice(digit)
        nr = nr * 10 + d
        digit.remove(d)

    return nr


def valid_number(nr):
    try:
        nr = int(nr)
    except ValueError:
        return False
    if nr // 1000 == 0:
        return False
    digit = []
    while nr != 0:
        digit.append(nr % 10)
        nr = nr // 10
    diff = [0] * 10
    for i in range(0, 4):
        diff[digit[i]] += 1
    for i in range(0, 4):
        if diff[i] > 1:
            return False
    return True


def correctness(nr, secret):
    nr = int(nr)
    secret = int(secret)
    digit_nr = []
    while nr != 0:
        digit_nr.append(nr % 10)
        nr = nr // 10

    secret_nr = []
    while secret != 0:
        secret_nr.append(secret % 10)
        secret = secret // 10
    runners = 0
    codes = 0
    for i in range(0, 4):
        if secret_nr[i] == digit_nr[i]:
            codes += 1
        elif digit_nr[i] in secret_nr:
            runners += 1
    return codes, runners


