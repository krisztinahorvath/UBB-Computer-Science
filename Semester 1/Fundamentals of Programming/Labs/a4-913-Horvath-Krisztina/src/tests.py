"""
    Function tests
"""
from functions import split_command_params, reformat_user_cmd, parse_number, add, insert, \
    remove, cmd_params_breakdown, filter_real_modulo, replace, sum, product, transform_to_tuple, undo


def test_split_command_params():
    assert split_command_params("exit") == ("exit", None)
    assert split_command_params("add 7+3i") == ("add", "7+3i")
    assert split_command_params("add       7+3i") == ("add", "7+3i")
    assert split_command_params("     aDd    7+3i     ") == ("add", "7+3i")
    assert split_command_params(" REMOVE  7 + 3i   ") == ("remove", "7 + 3i")
    assert split_command_params(" replace   1+3i with  5-3i") == ("replace", "1+3i with  5-3i")


# test_split_command_params()


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


def test_transform_to_tuple():
    assert transform_to_tuple("5 - 9i") == (5, -9)
    assert transform_to_tuple("12 + 0i") == (12, 0)
    assert transform_to_tuple("0i") == (0, 0)
    assert transform_to_tuple("5 - 1i") == (5, -1)
    assert transform_to_tuple("7") == (7, 0)
    assert transform_to_tuple("- 9") == (-9, 0)
    assert transform_to_tuple("+3i") == (0, -3)


# test_transform_to_tuple()


def test_cmd_params_breakdown():
    assert cmd_params_breakdown("insert", "1+1i at 1") == ("1+1i", "1")
    assert cmd_params_breakdown("remove", "1 to 3") == ("1", "3")
    assert cmd_params_breakdown("replace", "1+3 i with 5-3 i") == ("1+3 i", "5-3 i")
    assert cmd_params_breakdown("list", "real 1 to 5") == ("1", "5")
    assert cmd_params_breakdown("list", "modulo < 10") == ("10", "<")


# test_cmd_params_breakdown()


def test_add():
    l = [[15, 16], [17, 19], [23, 24], [25, 26], [27, 90], [52, 53], [110, 20]]
    add(l, "add", "19 + 5i ")
    assert l[-1] == (19, 5)

    l = [[15, 16], [17, 19], [23, 24], [25, 26], [27, 90], [52, 53], [110, 20]]
    add(l, "add", "0")
    assert l[-1] == (0, 0)

    l = [[15, 16], [17, 19], [23, 24], [25, 26], [27, 90], [52, 53], [110, 20]]
    add(l, "add", "18 + 0i")
    assert l[-1] == (18, 0)


#test_add()


def test_insert():
    l = [[15, 16], [17, 19], [23, 24], [25, 26], [27, 90], [52, 53], [110, 20]]
    insert(l, "insert", "19 + 20 i at 2")
    assert l[2] == (19, 20)

    l = [[15, 16], [17, 19], [23, 24], [25, 26], [27, 90], [52, 53], [110, 20]]
    insert(l, "insert", "0 at 0")
    assert l[0] == (0, 0)

    l = [[15, 16], [17, 19], [23, 24], [25, 26], [27, 90], [52, 53], [110, 20]]
    insert(l, "insert", "100+100i at 6 ")
    assert l[6] == (100, 100)


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


def test_replace():
    l = [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3], [23, 67], [-7, -2], [10, 11]]
    replace(l, "replace", "1+5i with 2")

    assert replace(l, "replace", "1+5i with 2") == [[2, 0], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3],
                                                    [23, 67], [-7, -2], [10, 11]]

    l = [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3], [23, 67], [-7, -2], [10, 11]]
    assert replace(l, "replace", "55+100i at -2i") == [[1, 5], [23, 67], [0, -2], [1, 0], [0, 0], [1, -2], [-9, 3],
                                                       [23, 67], [0, 0], [10, 11]]

    l = [[1, 5], [23, 67], [55, 100], [1, 5], [0, 0], [1, -2], [-9, 3], [23, 67], [1, 5], [1, 5]]
    assert replace(l, "replace", "1+5i with -19-19i") == [[-19, -19], [23, 67], [55, 100], [-19, -19], [0, 0], [1, -2],
                                                          [-9, 3], [23, 67], [-19, -19], [-19, -19]]

    l = [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3], [23, 67], [-7, -2], [10, 11]]
    assert replace(l, "replace", "-20i with 2+3i") == "The number that you are trying to replace does not exist " \
                                                      "in the list or unsupported form"

# test_replace()


def test_sum():
    l = [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3], [23, 67], [-7, -2], [10, 11]]
    assert sum(l, "sum", "1 to 5") == (80, 165)
    assert sum(l, "sum", "0 to 0") == (1, 5)
    assert sum(l, "sum", "2 to 6") == (48, 101)
    assert sum(l, "sum", "8 to 9") == (3, 9)

# test_sum()


def test_product():
    l = [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3], [23, 67], [-7, -2], [10, 11]]
    assert product(l, "product", "1 to 5") == (0, 0)
    assert product(l, "product", "0 to 0") == (1, 5)
    assert product(l, "product", "9 to 9") == (10, 11)
    assert product(l, "product", "7 to 9") == (-1610, -1474)

# test_product()


def test_filter_real_modulo():
    l = [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3], [23, 67], [-7, -2], [10, 11], [19, 0]]
    filter_real_modulo(l, -1, "0")
    assert l == [[1, 0], [0, 0], [19, 0]]

    l = [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3], [23, 67], [-7, -2], [10, 11]]
    filter_real_modulo(l, -1, ">")
    assert l == [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3], [23, 67],
                                              [-7, -2], [10, 11]]

    l = [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3], [23, 67], [-7, -2], [10, 11]]
    filter_real_modulo(l, 0, "<")
    assert l == [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3], [23, 67],
                                             [-7, -2], [10, 11]]

# test_filter_real_modulo()


def test_undo():
    l = [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3], [23, 67], [-7, -2], [10, 11], [19, 0]]
    # after an add, replace, remove
    l_undo = [[[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3], [23, 67], [-7, -2], [10, 11], [19, 0]],
                 [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3], [23, 67], [-7, -2], [10, 11], [19, 0], (7, 7)],
                 [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [100, 100], [-9, 3], [23, 67], [-7, -2], [10, 11], [19, 0], (7, 7)],
                 [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [100, 100], [-9, 3], [23, 67], [-7, -2], [10, 11], [19, 0], (7, 7)]]

    undo(l_undo, " ")
    l = l_undo[-1]
    assert l == [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [100, 100], [-9, 3], [23, 67], [-7, -2], [10, 11], [19, 0], (7, 7)]

    undo(l_undo, " ")
    l = l_undo[-1]
    assert l == [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3], [23, 67], [-7, -2], [10, 11], [19, 0], (7, 7)]

    undo(l_undo, " ")
    l = l_undo[-1]
    assert l == [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3], [23, 67], [-7, -2], [10, 11], [19, 0]]


test_undo()