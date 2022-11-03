# P1
"""
  Write non-UI functions below
"""
import math


def split_command_params(user_cmd):
    """
    Splits the user's command into the command word and a parameters string
    :param user_cmd: the command that the user introduced
    :return: command word and command parameters in lower case
    """
    user_cmd = user_cmd.strip()
    tokens = user_cmd.split(maxsplit=1)
    cmd_words = tokens[0].lower() if len(tokens[0]) > 0 else None
    if len(tokens) > 1:
        cmd_params = tokens[1].lower()
    else:
        cmd_params = None
    return cmd_words, cmd_params


def reformat_user_cmd(user_cmd):
    """
    Reformats the input given by the user (deletes all extra spaces, leaving only one space between each word/number)
    :param user_cmd: input command by user
    :return:
    """
    user_cmd = user_cmd.strip()
    user_cmd = user_cmd.lower()
    new = ""
    for i in range(0, len(user_cmd)):
        if user_cmd[i] != ' ':
            new += user_cmd[i]
        elif new[len(new) - 1] != ' ':
            new += ' '
    return new


def parse_number(number):
    """
    This function eliminates all white spaces in a string formed of a complex number(a +   bi => a+bi)
    :param number: a complex number(string)
    :return: a compressed version of the input string(no spaces)
         or raises a ValueError if the format isn't correct and can't pe parsed into a representation of a complex nr
    """
    number = number.strip()  # we eliminate white spaces before and after the string
    a = "empty"
    nr = 0
    for i in range(len(number)):
        if number[i] == '-' or number[i] == '+' or number[i].isdigit() or number[i] == 'i':
            if a == "empty":
                a = number[i]
                nr += 1
            elif nr == 1:
                a += number[i]
        elif number[i] != ' ':
            raise ValueError("Incorrect number, can't parse correctly")
            # return "Incorrect number, can't parse correctly"
    if a == "empty":
        raise ValueError("Incorrect number, can't parse correctly")
        # return "Incorrect number, can't parse correctly"
    elif a.find('+') == len(a) - 1 or a.find('-') == len(a) - 1:
        raise ValueError("Incorrect number, can't parse correctly")
        # return "Incorrect number, can't parse correctly"
    elif (a.find('+') > 0 or a.find('-') > 0) and a.find('i') == -1:
        raise ValueError("Incorrect number, can't parse correctly")
        # return "Incorrect number, can't parse correctly"
    return a


def transform_to_tuple(nr):
    """
    Transforms a complex number as a string into a tuple of two integer numbers.
    :param nr: a complex number (string) => a+bi
    :return: a tuple formed of the real and imaginary part of the given number => (a,b)
    """
    iFind = nr.find('i')
    re = 'empty'
    im = 'empty'
    for i in range(len(nr)):
        if nr[i] == '-' or nr[i] == '+':  # -/+ means that a new number is starting
            if re == 'empty':
                re = nr[i]
            else:
                im = nr[i]
        else:  # it's a digit or character 'i'
            if re == 'empty':
                re = nr[i]
            elif re != 'empty' and im == 'empty':
                re += nr[i]
            elif im != 'empty':
                im += nr[i]

    if iFind != -1:  # if there is an i in the number(imaginary part exists)
        if re.find('i') != -1:
            im = int(re[:re.find('i')])
            re = 0
        else:
            re = int(re)
            im = int(im[:im.find('i')])
    else:
        re = int(re)
        im = 0
    return re, im


def cmd_params_breakdown(cmd_word, cmd_params):
    """
    Based on the cmd_word and cmd_params we return the actual data that we need
    ex: replace 5 + 9i with 7 + 3i => (5 + 9i, 7 + 3i)
    :param cmd_word: command word
    :param cmd_params: command parameters
    :return: for every command there are two different values returned
    """
    if cmd_word == "insert":
        if cmd_params.find('at') != -1:
            word = cmd_params.split(sep=" at ", maxsplit=1)
            nr = word[0].strip() if len(word[0]) > 0 else None
            pos = word[1].strip() if len(word[1]) > 0 else None
            return nr, pos
        else:
            raise ValueError("Invalid input")
    elif cmd_word == "remove":
        if cmd_params.find(" to ") != -1:
            word = cmd_params.split(sep=" to ", maxsplit=1)
            start = word[0].strip() if len(word[0]) > 0 else None
            finish = word[1].strip() if len(word[1]) > 0 else None
            return start, finish
        else:
            raise ValueError("Invalid input")
    elif cmd_word == "replace":
        if cmd_params.find(" with ") != -1:
            word = cmd_params.split(sep=" with ", maxsplit=1)
            old = word[0].strip() if len(word[0]) > 0 else None
            new = word[1].strip() if len(word[1]) > 0 else None
            return old, new
        else:
            raise ValueError("Invalid input")
    elif cmd_word == "list":
        if (cmd_params.find(" to ") == -1 and cmd_params.find("real") == -1) and cmd_params.find("modulo"):
            raise ValueError("Invalid input")
        else:
            if cmd_params.find("real") != -1:
                word = cmd_params.split(sep=" to ", maxsplit=1)
                start = word[0].strip() if len(word[0]) > 0 else None
                finish = word[1].strip() if len(word[1]) > 0 else None
                start = start[5:] # removing 'real ' from the string start
                start.strip()
                return start, finish
            else:  # modulo
                less = cmd_params.find('<')
                equal = cmd_params.find('=')
                more = cmd_params.find('>')
                sign = " "
                if less != -1:
                    word = cmd_params.split(sep='<', maxsplit=1)
                    sign = '<'
                elif equal != -1:
                    word = cmd_params.split(sep='=', maxsplit=1)
                    sign = '='
                else:
                    word = cmd_params.split(sep='>', maxsplit=1)
                    sign = '>'
                nr = word[1].strip() if len(word[0]) > 0 else None
                if sign != " ":
                    return nr, sign
                else:
                    raise ValueError("Invalid input")
    else:
        raise ValueError("Invalid input")


def test_cmd_params_breakdown():
    a, b = cmd_params_breakdown("list", "real 1 to 5")
    assert cmd_params_breakdown("insert", "1+1i at 1") == ("1+1i", "1")
    assert cmd_params_breakdown("remove", "1 to 3") == ("1", "3")
    assert cmd_params_breakdown("replace", "1+3 i with 5-3 i") == ("1+3 i", "5-3 i")
    assert cmd_params_breakdown("list", "real 1 to 5") == ("1", "5")
    assert cmd_params_breakdown("list", "modulo < 10") == ("10", "<")


# test_cmd_params_breakdown()


def set_real(z, nr):
    # sets the real part of z to nr(Rez = nr)
    z[0] = nr


def set_imag(z, nr):
    # sets the real part of z to nr(Imz = nr)
    z[1] = nr


def get_real(z):
    # returns the real part of the complex number z
    return z[0]


def get_imag(z):
    # returns the imaginary part of the complex number z
    return z[1]


def modulus(z):
    """
    Computes the modulus of a given complex number.
    :param z: a complex number
    :return: the modulus of a complex number
    """
    return int(math.sqrt(get_real(z) * get_real(z) + get_imag(z) * get_imag(z)))


def add(l, cmd_word, cmd_params):
    """
    Adds a number to the list 'l'
    :param l: the list with the complex numbers
    :param nr: the number that we want to add
    :param cmd_word:
    :param cmd_params:
    :return:
    """
    try:
        if cmd_params is None:
            raise ValueError("No value introduced")
        nr = transform_to_tuple(parse_number(cmd_params))
        l.append(nr)
    except ValueError as ve:
        print(ve)


def insert(l, cmd_word, cmd_params):
    """
    Inserts a number to a certain position
    :param l: the list with the complex numbers
    :param nr: the number that we want to insert(a list with two positions)
    :param pos: the position that we want to insert on
    :return:
    """
    try:
        word = cmd_params_breakdown(cmd_word, cmd_params)
        nr = word[0].strip() if len(word[0]) > 0 else None
        pos = word[1].strip() if len(word[1]) > 0 else None
        if nr is None or pos is None:
            print("Invalid input")
        else:
            pos = int(pos)
            nr = transform_to_tuple(parse_number(nr))
            l.insert(pos, nr)
    except ValueError or IndexError as ve:
        print(ve)


def remove(l, cmd_word, cmd_params):
    """
    This function removes form the list 'l' elements starting from position start to finish
    :param l: the list with the complex numbers
    :param start: the position from where the removing starts
    :param finish: the position where the removing stops
    !! the return commands were used for the test function, otherwise they are not needed
    """
    try:
        try:
            pos = int(cmd_params)
            l.remove(l[pos])
        except:
            word = cmd_params_breakdown(cmd_word, cmd_params)
            start = word[0].strip() if len(word[0]) > 0 else None
            finish = word[1].strip() if len(word[1]) > 0 else None
            if start is None or finish is None:
                print("Invalid input")
            else:
                if start is None:
                    finish = start
                finish = int(finish)
                start = int(start)
                if start < 0 or start > len(l) - 1 or finish < 0 or finish > len(l) - 1 or start > finish:
                    print("Index out of range")
                else:
                    if start == finish:
                        nr = 1
                    else:
                        nr = finish - start + 1  # nr = how many elements we have to remove
                    # i = start
                    if len(l) == 1:
                        l.remove(l[0])
                    else:
                        while nr != 0:
                            l.remove(l[start])
                            nr -= 1
    except ValueError or IndexError as ve:
        print(ve)


def replace(l, cmd_word, cmd_params):
    """
    Replaces all the appearances of old_nr with new_nr
    :param l: list of the complex numbers
    :param old_nr: the number that we want to replace(a list) => [5,2]
    :param new_nr: the number that has to replace the other one(a list) => [10,11]
    """
    try:
        word = cmd_params_breakdown(cmd_word, cmd_params)
        old_nr = word[0].strip()
        old_nr = transform_to_tuple(parse_number(old_nr))
        new_nr = word[1].strip()
        new_nr = transform_to_tuple(parse_number(new_nr))
        for i in range(0, len(l)):
            if get_real(l[i]) == get_real(old_nr) and get_imag(l[i]) == get_imag(old_nr):
                set_real(l[i], get_real(new_nr))
                set_imag(l[i], get_imag(new_nr))
    except ValueError:
        print("The number that you are trying to replace does not exist in the list or unsupported form")


def print_number(nr):
    #  prints one complex number
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


def list(l, cmd_word, cmd_params):
    """
    Display numbers having different properties
    :param l: list with the complex numbers
    :param cmd_word: command word
    :param cmd_params: command parameters
    """
    try:
        if cmd_params is None:
            print_list(l)
        else:
            a, b = cmd_params_breakdown(cmd_word, cmd_params)
            if b is None:
                print("Value error")
            else:
                try:
                    a = int(a)
                except TypeError as ve:
                    print(ve)
                if b in ['<', '=', '>']:  # modulo command
                    print_list_modulus(l, a, b)
                else:  # real command
                    try:
                        a = int(a)
                        b = int(b)
                        print_list_real(l,a,b)
                    except TypeError as ve:
                        print(ve)
                    if a < 0 or a > len(l) or b < 0 or b > len(l):
                        raise IndexError
    except ValueError as ve:
        print(ve)


"""
    Function tests
"""


def test_split_command_params():
    assert split_command_params("exit") == ("exit", None)
    assert split_command_params("add 7+3i") == ("add", "7+3i")
    assert split_command_params("add       7+3i") == ("add", "7+3i")
    assert split_command_params("     aDd    7+3i     ") == ("add", "7+3i     ")
    assert split_command_params(" REMOVE  7 + 3i   ") == ("remove", "7 + 3i   ")
    assert split_command_params(" replace   1+3i with  5-3i") == ("replace", "1+3i with  5-3i")


def test_reformat_user_cmd():
    assert reformat_user_cmd("inSert 15 +          19 i at   1") == "insert 15 + 19 i at 1"
    assert reformat_user_cmd(" reMoVE   1 to     6    7") == "remove 1 to 6 7"
    assert reformat_user_cmd("add 8        I") == "add 8 i"
    assert reformat_user_cmd("list           ModU   lo     =    9 ") == "list modu lo = 9"
    assert reformat_user_cmd("replace 16 WIth 5-      2 ") == "replace 16 with 5- 2"


# test_reformat_user_cmd()

def test_parse_number():
    assert parse_number("          5 +     3        i     ") == "5+3i"
    assert parse_number("< 9 +  10  ") == "Incorrect number, can't parse correctly"
    assert parse_number("19 + 20     ") == "Incorrect number, can't parse correctly"
    assert parse_number("16 < 20i") == "Incorrect number, can't parse correctly"
    assert parse_number("     17 ") == "17"
    assert parse_number(" + ") == "Incorrect number, can't parse correctly"
    assert parse_number(" - 29 i") == "-29i"
    assert parse_number("       ") == "Incorrect number, can't parse correctly"
    assert parse_number(" 17 +    ") == "Incorrect number, can't parse correctly"


# test_parse_number()

def test_insert():
    l = [[15, 16], [17, 19], [23, 24], [25, 26], [27, 90], [52, 53], [110, 20]]
    assert insert(l, [19, 20], 2) == [[15, 16], [17, 19], [19, 20], [23, 24], [25, 26], [27, 90], [52, 53], [110, 20]]

    l = [[15, 16], [17, 19], [23, 24], [25, 26], [27, 90], [52, 53], [110, 20]]
    assert insert(l, [20, 99], 0) == [[20, 99], [15, 16], [17, 19], [23, 24], [25, 26], [27, 90], [52, 53], [110, 20]]

    l = [[15, 16], [17, 19], [23, 24], [25, 26], [27, 90], [52, 53], [110, 20]]
    assert insert(l, [100, 100], 6) == [[15, 16], [17, 19], [23, 24], [25, 26], [27, 90], [52, 53], [100, 100],
                                        [110, 20]]


# test_insert()

def test_remove():
    l = [[15, 16], [17, 19], [23, 24], [25, 26], [27, 90], [52, 53], [110, 20]]
    assert remove(l, "remove", "2") == [[15, 16], [17, 19], [25, 26], [27, 90], [52, 53], [110, 20]]

    l = [[15, 16], [17, 19], [23, 24], [25, 26], [27, 90], [52, 53], [110, 20]]
    assert remove(l, "remove", "0 to 5") == [[110, 20]]

    l = [[15, 16], [17, 19], [23, 24], [25, 26], [27, 90], [52, 53], [110, 20]]
    assert remove(l, "remove", "13 to 5") == "Index out of range"

    l = [[15, 16], [17, 19], [23, 24], [25, 26], [27, 90], [52, 53], [110, 20]]
    assert remove(l, "remove", "6") == [[15, 16], [17, 19], [23, 24], [25, 26], [27, 90], [52, 53]]


# test_remove()

"""
  Write the command-driven UI below
"""


def start_command_ui():
    l = [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3], [23, 67], [-7, -2], [10, 11]]
    cmd_dict = {"add": add, "insert": insert, "remove": remove, "replace": replace,
                "list": list}

    while True:
        user_cmd = input(">>")
        user_cmd = reformat_user_cmd(user_cmd)
        cmd_word, cmd_params = split_command_params(user_cmd)

        if cmd_word == "exit":
            return

        if cmd_word not in cmd_dict:
            print("Invalid command")
        else:
            cmd_dict[cmd_word](l, cmd_word, cmd_params)

start_command_ui()