"""
  Program functionalities module
"""
import math

from ui import print_number, print_list, print_list_real, print_list_modulus


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
    if a == "empty":
        raise ValueError("Incorrect number, can't parse correctly")
    elif a.find('+') == len(a) - 1 or a.find('-') == len(a) - 1:
        raise ValueError("Incorrect number, can't parse correctly")
    elif (a.find('+') > 0 or a.find('-') > 0) and a.find('i') == -1:
        raise ValueError("Incorrect number, can't parse correctly")
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
                start = start[5:]  # removing 'real ' from the string start
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
    elif cmd_word == "sum":
        if cmd_params.find(" to ") == -1:
            raise ValueError("Invalid input")
        else:
            word = cmd_params.split(sep=" to ", maxsplit=1)
            pos1 = word[0].strip() if len(word[0]) > 0 else None
            pos2 = word[1].strip() if len(word[1]) > 0 else None
            return pos1, pos2
    elif cmd_word == "product":
        if cmd_params.find(" to ") == -1:
            raise ValueError("Invalid input")
        else:
            word = cmd_params.split(sep=" to ", maxsplit=1)
            pos1 = word[0].strip() if len(word[0]) > 0 else None
            pos2 = word[1].strip() if len(word[1]) > 0 else None
            return pos1, pos2
    elif cmd_word == "filter":
        if cmd_params.find("modulo") != -1:
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
            if len(word) <= 1:
                raise ValueError("Invalid input")
            nr = word[1].strip() if len(word[0]) > 0 else None
            if sign != " ":
                return nr, sign
            else:
                raise ValueError("Invalid input")
        else:
            raise ValueError("Invalid input")
    else:
        raise ValueError("Invalid input")


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
    :param cmd_word: command word
    :param cmd_params: command parameters
    :return:
    """
    try:
        if cmd_params is None:
            raise ValueError("No value introduced")
        nr = transform_to_tuple(parse_number(cmd_params))
        l.append(nr)
    except ValueError as ve:
        raise ValueError("Invalid input")


def insert(l, cmd_word, cmd_params):
    """
    Inserts a number to a certain position
    :param l: the list with the complex numbers
    :param cmd_word: command word
    :param cmd_params: command parameters
    :return:
    """
    try:
        word = cmd_params_breakdown(cmd_word, cmd_params)
        if len(word) < 2:
            raise ValueError("Invalid input")
        nr = word[0].strip() if len(word[0]) > 0 else None
        pos = word[1].strip() if len(word[1]) > 0 else None
        if nr is None or pos is None:
            raise ValueError("Invalid input")
        else:
            pos = int(pos)
            nr = transform_to_tuple(parse_number(nr))
            l.insert(pos, nr)
    except ValueError:
        raise ValueError("Invalid input")


def remove(l, cmd_word, cmd_params):
    """
    This function removes form the list 'l' elements starting from position start to finish
    :param cmd_params: command parameters
    :param cmd_word: command word
    :param l: the list with the complex numbers
    !! the return commands were used for the test function, otherwise they are not needed
    """
    try:
        try:
            pos = int(cmd_params)
            l.remove(l[pos])
        except:
            word = cmd_params_breakdown(cmd_word, cmd_params)
            if len(word) < 2:
                raise ValueError("Invalid input!")
            start = word[0].strip() if len(word[0]) > 0 else None
            finish = word[1].strip() if len(word[1]) > 0 else None
            if start is None or finish is None:
                raise ValueError("Invalid input")
            else:
                if start is None:
                    finish = start
                finish = int(finish)
                start = int(start)
                if start < 0 or start > len(l) - 1 or finish < 0 or finish > len(l) - 1 or start > finish:
                    raise IndexError("Index out of range")
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
    except ValueError:
        raise ValueError("Invalid input")


def replace(l, cmd_word, cmd_params):
    """
    Replaces all the appearances of old_nr with new_nr
    :param l: list of the complex numbers
    :param cmd_word: command word
    :param cmd_params: command parameters
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
        raise ValueError("The number that you are trying to replace does not exist in the list or unsupported form")


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
                raise ValueError("Value error")
            else:
                try:
                    a = int(a)
                except TypeError:
                    raise TypeError("Type error")
                if b in ['<', '=', '>']:  # modulo command
                    print_list_modulus(l, a, b)
                else:  # real command
                    try:
                        a = int(a)
                        b = int(b)
                        print_list_real(l, a, b)
                    except TypeError:
                        raise TypeError("Type error")
                    if a < 0 or a > len(l) or b < 0 or b > len(l):
                        raise IndexError
    except ValueError:
        raise ValueError("Invalid input")


"""
    **************** A4 ****************
"""


def sum(l, cmd_word, cmd_params):
    """
    This function computes the sum of the numbers of the list between two given positions
    :param l: list with complex numbers
    :param cmd_word: command word
    :param cmd_params: command parameters
    :return: the sum of the numbers(a tuple) between two positions in the list
             => (sum of real part, sum of imaginary part)
    """
    try:
        pos1, pos2 = cmd_params_breakdown(cmd_word, cmd_params)
        if pos1 is None or pos2 is None:
            raise ValueError("Invalid input")
        else:
            try:
                pos1 = int(pos1)
                pos2 = int(pos2)
                if pos1 > pos2 or pos1 < 0 or pos1 > len(l) - 1 or pos2 < 0 or pos2 > len(l) - 1:
                    raise ValueError("Invalid indexes")
                else:
                    reSum = 0  # the sum of the real part of the complex numbers
                    imSum = 0  # the sum of the imaginary part of the complex numbers
                    for i in range(pos1, pos2 + 1):
                        reSum += get_real(l[i])
                        imSum += get_imag(l[i])
                    return reSum, imSum
            except TypeError:
                raise TypeError("Type error")
    except ValueError:
        raise ValueError("Invalid input")


def product(l, cmd_word, cmd_params):
    """
    This function computes the product of the numbers of the list between two given positions
    :param l: list with complex numbers
    :param cmd_word: command word
    :param cmd_params: command parameters
    :return: the product of the numbers between two given positions in the list
    """
    try:
        pos1, pos2 = cmd_params_breakdown(cmd_word, cmd_params)
        if pos1 is None or pos2 is None:
            raise ValueError("Invalid input")
        else:
            try:
                pos1 = int(pos1)
                pos2 = int(pos2)
                if pos1 > pos2 or pos1 < 0 or pos1 > len(l) - 1 or pos2 < 0 or pos2 > len(l) - 1:
                    raise ValueError("Invalid indexes")
                else:
                    reProd = 1  # the product of the real part of the complex numbers
                    imProd = 1  # the product of the imaginary part of the complex numbers
                    for i in range(pos1, pos2 + 1):
                        reProd *= get_real(l[i])
                        imProd *= get_imag(l[i])
                    return reProd, imProd
            except TypeError:
                raise TypeError("Type error")
    except ValueError:
        raise ValueError("Invalid input")


def filter_real_modulo(l, nr, sign):
    """
    Removes numbers from the list with a given property:
        - removes complex numbers with imaginary part not null
        - removes complex numbers who's modulus is not as requested
    :param l: list with complex numbers
    :param nr: a positive number if remove is for modulo, else -1
    :param sign: for modulo, </=/>, else sign = "0", for real
    :return: the modified list(through reference)
    """
    if sign == "0":
        i = 0
        length = len(l)
        while i < length:
            if get_imag(l[i]) != 0:
                l.remove(l[i])
                length -= 1
            else:
                i += 1

    else:
        if sign == '<':
            i = 0
            length = len(l)
            while i < length:
                if modulus(l[i]) < nr:
                    l.remove(l[i])
                    length -= 1
                else:
                    i += 1
        elif sign == '=':
            i = 0
            length = len(l)
            while i < length:
                if modulus(l[i]) == nr:
                    l.remove(l[i])
                    length -= 1
                else:
                    i += 1
        elif sign == '>':
            i = 0
            length = len(l)
            while i < length:
                if modulus(l[i]) > nr:
                    l.remove(l[i])
                    length -= 1
                else:
                    i += 1
        else:
            raise ValueError("Invalid sign input")


def filter(l, cmd_word, cmd_params):
    """
    This function filters out the list according to the given parameters
    (removes numbers that don't have a given property)
    :param l: list with complex numbers
    :param cmd_word: command word
    :param cmd_params: command parameters
    :return:
    """
    try:
        if cmd_params.find("real") != -1:
            cmd_params = cmd_params.strip()
            if cmd_params != "real":
                raise ValueError("Invalid input")
            else:
                filter_real_modulo(l, -1, "0")
        else:
            try:
                nr, sign = cmd_params_breakdown(cmd_word, cmd_params)
                if nr is None or sign is None:
                    raise ValueError("Invalid input")
                else:
                    nr = int(nr)
                    filter_real_modulo(l, nr, sign)
            except ValueError as ve:
                raise ValueError("Invalid input")
    except ValueError or IndexError as ve:
        raise ValueError("Invalid input")


def undo(undo_list, cmd_params):
    """
    This function reverses the last operation that modified the program data
    :param undo_list: the list that stores l(the list with the complex numbers) w
    :param cmd_params: command parameters
    """
    if cmd_params is not None:
        raise ValueError("Invalid input")
    try:
        if len(undo_list) == 1:
            raise ValueError("There were no operations executed that can be undone")
        elif len(undo_list) > 1:
            undo_list.pop(-1)
        else:
            raise ValueError("Can't undo operation")
    except ValueError as ve:
        raise ValueError("Invalid input")
