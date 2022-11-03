"""
              problem 1

"""
from copy import deepcopy

from src.services.exceptions import StudentError, DisciplineError, GradeError
from src.services.studentServices import StudentServices
from src.services.gradeServices import GradeServices
from src.services.disciplineServices import DisciplineServices
from src.services.undoServices import UndoRedoServices
from src.ui.prints import Prints


class UI:
    def __init__(self):
        self.srvStud = StudentServices()
        self.srvDisc = DisciplineServices()
        self.srvGrade = GradeServices(self.srvDisc.repoDisc.dictionary, self.srvStud.repoStud.dictionary)
        self.prints = Prints(self.srvStud.repoStud, self.srvDisc.repoDisc, self.srvGrade.repoGrade)
        self.srvUndoRedo = UndoRedoServices(self.srvStud, self.srvDisc, self.srvGrade)
        self.undo_list = []  # undo_list_options => addStud, removeStud etc
        self.undo_params = [[]]
        self.redo_list = [[]]
        self.redo_params = [[]]
        self.add_back_grades_undo = [[]]
        self.add_back_grades_redo = [[]]

    def start(self):

        self.prints.print_menu()

        option = ""
        previous_option = ""
        search_option = ""
        stud_disc = ["students", "disciplines"]
        search_dict = ["student", "discipline"]  # we can search for a student or discipline

        while True:

            clear_redo = 0
            if option in ["students", "disciplines", "grades", "search", "statistics", "undo", "redo"]:
                previous_option = option
            if option in  ["students", "disciplines", "grades", "search", "statistics"]:
                clear_redo = 1
            elif option in search_dict:
                search_option = option

            option = input(">>>")
            option = option.lower()
            option = option.strip()

            if option == "menu":
                self.prints.print_menu()
            elif option in stud_disc:  # students and disciplines
                self.prints.print_menu_stud_disc()
            elif option == "add" and previous_option in stud_disc:
                if previous_option == "students":
                    try:
                        ids = input("id: ")
                        name = input("name: ")
                        self.srvStud.add_stud_disc(ids, name)
                        print("You added student: " + str(name) + " with id: " + str(ids))

                        # undo/redo
                        self.undo_list.append("addStud")
                        self.undo_params.append([ids, name])

                        # self.redo_list.append("addStud")
                        # self.redo_params.append([ids, name])
                        # self.redo_list = deepcopy(self.undo_list)
                        # self.redo_params = deepcopy(self.undo_params)


                        # self.redo_list.append(0)  # "Cannot add a student with the same id twice!"

                    except StudentError as ve:
                        print(ve)
                else:
                    try:
                        ids = input("id: ")
                        name = input("name: ")
                        self.srvDisc.add_stud_disc(ids, name)
                        print("You added the discipline: " + str(name) + " with id: " + str(ids))

                        # undo/redo
                        self.undo_list.append("addDisc")
                        self.undo_params.append([ids, name])

                        # self.redo_list = deepcopy(self.undo_list)
                        # self.redo_params = deepcopy(self.undo_params)

                        # self.redo_list.append(0)  # "Cannot add a discipline with the same id twice!"
                    except DisciplineError as ve:
                        print(ve)
            elif option == "remove" and previous_option in stud_disc:
                if previous_option == "students":
                    try:
                        ids = input("id: ")

                        # undo/redo
                        self.undo_list.append("removeStud")
                        self.undo_params.append([ids, self.srvStud.repoStud.dictionary[ids].name])
                        self.add_back_grades_undo.append(
                            self.srvUndoRedo.grades_that_have_to_be_added_back_stud(ids, {}))

                        # self.redo_list = deepcopy(self.undo_list)
                        # self.redo_params = deepcopy(self.undo_params)
                        # self.add_back_grades_redo = deepcopy(self.add_back_grades_undo)

                        self.srvStud.remove_stud(ids, self.srvGrade.repoGrade.dictionary)
                        print("Student with id: " + str(ids) + " has been removed!")

                        # self.redo_list.append(0)  # "Cannot add a discipline with the same id twice!"
                    except StudentError as ve:
                        print(ve)
                else:
                    try:
                        ids = input("id: ")

                        # undo/redo
                        self.undo_list.append("removeDisc")
                        self.undo_params.append([ids, self.srvDisc.repoDisc.dictionary[ids].name])
                        self.add_back_grades_undo.append(
                            self.srvUndoRedo.grades_that_have_to_be_added_back_disc(ids, {}))

                        # self.redo_list = deepcopy(self.undo_list)
                        # self.redo_params = deepcopy(self.undo_params)
                        # self.add_back_grades_redo = deepcopy(self.add_back_grades_undo)

                        self.srvDisc.remove_disc(ids, self.srvGrade.repoGrade.dictionary)
                        print("Discipline with id: " + str(ids) + " has been removed!")

                        # self.redo_list.append(0)  # "Cannot add a discipline with the same id twice!"
                    except DisciplineError as ve:
                        print(ve)
            elif option == "update" and previous_option in stud_disc:
                if previous_option == "students":
                    ids = input("id: ")
                    name = input("name: ")
                    try:
                        old_name = self.srvStud.repoStud.dictionary[ids].name
                        self.srvStud.update_stud_disc(ids, name)
                        print("Student with id: " + str(ids) + " was updated")

                        # undo/redo
                        self.undo_list.append("updateStud")
                        self.undo_params.append([ids, name, old_name])

                        # self.redo_list = deepcopy(self.undo_list)
                        # self.redo_params.append([ids, old_name, name])
                        # self.redo_list.append(0)  # "Cannot add a discipline with the same id twice!"

                    except StudentError as ve:
                        print(ve)
                else:
                    ids = input("id: ")
                    name = input("name: ")
                    try:
                        old_name = self.srvDisc.repoDisc.dictionary[ids].name
                        self.srvDisc.update_stud_disc(ids, name)
                        print("Discipline with id: " + str(ids) + " was updated")

                        # undo/redo
                        self.undo_list.append("updateDisc")
                        self.undo_params.append([ids, name, old_name])

                        # self.redo_list = deepcopy(self.undo_list)
                        # self.redo_params.append([ids, old_name, name])

                    except DisciplineError as ve:
                        print(ve)
            elif option == "list" and previous_option in stud_disc:
                if previous_option == "students":
                    self.prints.print_stud()
                else:
                    self.prints.print_disc()
            elif option == "grades":  # grades
                self.prints.print_menu_grades()
            elif option == "list" and previous_option == "grades":
                self.prints.print_grades()
            elif option == "add" and previous_option == "grades":
                id_student = input("student id: ")
                id_discipline = input("discipline id: ")
                grade = input("grade: ")
                try:
                    self.srvGrade.add_grade(id_discipline, id_student, grade, self.srvStud.repoStud.dictionary,
                                            self.srvDisc.repoDisc.dictionary)
                    print("Grade added!")

                    # undo/redo
                    self.undo_list.append("addGrade")
                    self.undo_params.append([self.srvGrade.repoGrade.last_pos()])

                    # self.redo_list = deepcopy(self.undo_list)
                    # self.redo_params = deepcopy(self.undo_params)

                except GradeError as ve:
                    print(ve)
            elif option == "search":  # search
                self.prints.print_menu_search()
            elif option in search_dict and previous_option == "search":
                self.prints.print_menu_search_student_discipline()
            elif option in ["id", "name"] and previous_option == "search":
                if option == "id":
                    idd = input("id: ")
                    if search_option == "student":
                        self.prints.print_stud_disc_search_id(idd, "student")
                    else:
                        self.prints.print_stud_disc_search_id(idd, "discipline")
                elif option == "name":
                    name = input("name: ")
                    name = name.lower()
                    name = name.strip()
                    if search_option == "student":
                        self.prints.print_stud_disc_search_name(name, "student")
                    else:
                        self.prints.print_stud_disc_search_name(name, "discipline")
            elif option == "statistics":
                self.prints.print_menu_statistics()
            elif previous_option == "statistics":  # statistics
                if option == "failing":
                    failing_dict = dict()
                    self.srvStud.failing_studs(self.srvGrade, self.srvDisc.repoDisc.dictionary, failing_dict)
                    # self.prints.print_avg_grades_stud()
                    self.prints.print_statistics_failing(failing_dict)
                    failing_dict.clear()
                elif option == "best":
                    best_studs = []
                    best_studs.clear()
                    self.srvStud.best_studs_function(self.srvGrade, self.srvStud.repoStud.dictionary, best_studs)
                    self.prints.print_statistics_best(best_studs)
                    print(best_studs)
                elif option == "discipline":
                    disc_list = []
                    disc_list.clear()
                    self.srvDisc.disc_grades_desc(self.srvGrade, self.srvStud.repoStud.dictionary, disc_list)
                    print(disc_list)
            elif option == "redo":
                if clear_redo == 1:
                    self.redo_list.clear()
                    self.redo_params.clear()
                    print("There were no operations made that can be redone!")
                elif len(self.redo_list) == 0 or len(self.redo_params) == 1:
                    print("There were no operations made that can be redone!")
                else:
                    try:
                        print(self.redo_list)
                        last_op_made = self.redo_list[-1]
                        self.srvUndoRedo.redoDict[last_op_made](*self.redo_params[-1])
                        if last_op_made in ["addStud", "addDisc"]:
                            if len(self.add_back_grades_redo[-1]) != 0:
                                self.srvUndoRedo.add_removed_grades(self.add_back_grades_redo[-1])
                                self.add_back_grades_undo.pop(-1)  # for cascading

                        # self.undo_list.append(self.redo_list[-1])
                        # self.undo_params.append(self.red)

                        self.undo_list.append(deepcopy(self.redo_list[-1]))
                        self.undo_params.append(deepcopy(self.redo_params[-1]))

                        self.redo_list.pop(-1)
                        self.redo_params.pop(-1)

                        print("Redo action was successful!")
                    except GradeError as ge:
                        print(ge)
                    except StudentError as se:
                        print(se)
                    except DisciplineError as de:
                        print(de)

            elif option == "undo":
                if len(self.undo_list) == 0:
                    print("There were no operations made that can be undone!")
                else:
                    last_op_made = self.undo_list[-1]
                    self.srvUndoRedo.undoDict[last_op_made](*self.undo_params[-1])  # unpacks params for the functions
                    if last_op_made in ["removeStud", "removeDisc"] and len(self.add_back_grades_undo[-1]) != 0:
                        self.srvUndoRedo.add_removed_grades(self.add_back_grades_undo[-1])
                        self.add_back_grades_undo.pop(-1)  # for cascading

                    self.redo_list.append(deepcopy(last_op_made))
                    self.redo_params.append(deepcopy(self.undo_params[-1]))

                    self.undo_list.pop(-1)
                    self.undo_params.pop(-1)
                    print("Undo action was successful!")

            elif option == "exit":
                return
            else:
                print("Invalid option!")


ui = UI()
ui.start()