"""
  Start the program by running this module
"""

from copy import deepcopy


from functions import add, insert, remove, replace, reformat_user_cmd, split_command_params, list, \
    sum, product, filter, undo

from ui import print_number


def start_command_ui():
    l = [[1, 5], [23, 67], [55, 100], [1, 0], [0, 0], [1, -2], [-9, 3], [23, 67], [-7, -2], [10, 11]]
    cmd_dict = {"add": add, "insert": insert, "remove": remove, "replace": replace,
                "list": list, "sum": sum, "product": product, "filter": filter, "undo": undo}
    undo_list = [deepcopy(l)]

    while True:
        user_cmd = input(">>")
        user_cmd = reformat_user_cmd(user_cmd)
        cmd_word, cmd_params = split_command_params(user_cmd)
        if cmd_word == "exit":
            return

        if cmd_word not in cmd_dict:
            print("Invalid command")
        else:
            try:
                if cmd_word != "undo":
                    cmd_dict[cmd_word](l, cmd_word, cmd_params)
                    if cmd_word not in ["list", "sum", "product"]:
                        undo_list.append(deepcopy(l))
                    if cmd_word in ["sum", "product"]:
                        a, b = cmd_dict[cmd_word](l, cmd_word, cmd_params)
                        print_number((a, b))
                else:
                    undo(undo_list, cmd_params)
                    l = deepcopy(undo_list[-1])
            except ValueError or IndexError or TypeError as ve:
                print(ve)


start_command_ui()
