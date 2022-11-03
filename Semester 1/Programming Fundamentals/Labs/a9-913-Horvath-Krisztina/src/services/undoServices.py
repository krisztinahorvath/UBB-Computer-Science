from copy import deepcopy

from src.domain.grade import Grade
from src.services.exceptions import GradeError


class UndoRedoServices:
    def __init__(self, srvStud, srvDisc, srvGrades):
        self.srvStud = srvStud
        self.srvDisc = srvDisc
        self.srvGrades = srvGrades

        self.undoDict = {"addStud": self.undo_add_stud, "addDisc": self.undo_add_disc,
                         "updateStud": self.undo_update_stud, "updateDisc": self.undo_update_disc,
                         "removeStud": self.undo_remove_stud, "removeDisc": self.undo_remove_disc,
                         "addGrade": self.undo_add_grade}

        self.redoDict = {"addStud": self.redo_add_stud, "addDisc": self.redo_add_disc,
                         "updateStud": self.redo_update_stud, "updateDisc": self.redo_update_disc,
                         "removeStud": self.redo_remove_stud, "removeDisc": self.redo_remove_disc,
                         "addGrade": self.redo_add_grade}

        self.undo_list = []  # undo_list_options => addStud, removeStud etc
        self.undo_params = [[]]
        self.redo_list = [[]]
        self.redo_params = [[]]
        self.add_back_grades_undo = [[]]
        self.add_back_grades_redo = [[]]

    def push_stack(self, action_name, params):
        self.undo_list.append(action_name)
        self.undo_params.append(params)

    def pop_stack(self):
        self.undo_list.pop(-1)
        self.undo_params.pop(-1)

    def redo_clear(self):
        self.redo_list.clear()
        self.redo_params.clear()

    """
        ******************************************************UNDO******************************************
    """

    def undo(self):
        last_op_made = self.undo_list[-1]
        self.undoDict[last_op_made](*self.undo_params[-1])  # unpacks params for the functions
        if last_op_made in ["removeStud", "removeDisc"] and len(self.add_back_grades_undo[-1]) != 0:
            self.add_removed_grades(self.add_back_grades_undo[-1])
            self.add_back_grades_undo.pop(-1)  # for cascading

        self.redo_list.append(deepcopy(last_op_made))
        self.redo_params.append(deepcopy(self.undo_params[-1]))

        self.pop_stack()

    def undo_add_stud(self, idd, name):
        self.srvStud.remove_stud(idd, self.srvGrades.repoGrade.dictionary)

    def undo_add_disc(self, idd, name):
        self.srvDisc.remove_disc(idd, self.srvGrades.repoGrade.dictionary)

    def grades_that_have_to_be_added_back_stud(self, idd, grades):
        """
        This function adds back the grades for a deleted student
        :param idd:
        :param grades:
        :return:
        """
        grade_repo = self.srvGrades.repoGrade.dictionary
        for i in grade_repo:
            if str(grade_repo[i].student_id) == str(idd):
                grades[i] = grade_repo[i]
        return grades

    def grades_that_have_to_be_added_back_disc(self, idd, grades):
        """
        This function adds back the grades for a deleted student
        :param idd:
        :param grades:
        :return:
        """
        grade_repo = self.srvGrades.repoGrade.dictionary
        for i in grade_repo:
            if str(grade_repo[i].discipline_id) == str(idd):
                grades[i] = grade_repo[i]
        return grades

    def add_removed_grades(self, grades):
        for i in grades:
            self.srvGrades.repoGrade.add_grade(grades[i].discipline_id, grades[i].student_id,
                                               grades[i].grade, Grade, GradeError,
                                               self.srvStud.repoStud.dictionary, self.srvDisc.repoDisc.dictionary)

    def undo_update_stud(self, idd, name, old_name):
        self.srvStud.update_stud_disc(idd, old_name)

    def undo_update_disc(self, idd, name, old_name):
        self.srvDisc.update_stud_disc(idd, old_name)

    def undo_remove_stud(self, idd, name):
        self.srvStud.add_stud_disc(idd, name)

    def undo_remove_disc(self, idd, name):
        self.srvDisc.add_stud_disc(idd, name)

    def undo_add_grade(self, idd):
        self.srvGrades.repoGrade.dictionary.pop(str(idd))

    """
    ******************************************************REDO******************************************
    """

    def redo(self):
        last_op_made = self.redo_list[-1]
        self.redoDict[last_op_made](*self.redo_params[-1])
        if last_op_made in ["addStud", "addDisc"]:
            if len(self.add_back_grades_redo[-1]) != 0:
                self.add_removed_grades(self.add_back_grades_redo[-1])
                self.add_back_grades_undo.pop(-1)  # for cascading

        self.push_stack(deepcopy(self.redo_list[-1]), deepcopy(self.redo_params[-1]))

        self.redo_list.pop(-1)
        self.redo_params.pop(-1)

    def redo_add_stud(self, idd, name):
        self.undo_remove_stud(idd, name)

    def redo_add_disc(self, idd, name):
        self.undo_remove_disc(idd, name)

    def redo_update_stud(self, idd, name, old_name):
        self.srvStud.update_stud_disc(idd, old_name)

    def redo_update_disc(self, idd, name, old_name):
        self.srvDisc.update_stud_disc(idd, old_name)

    def redo_remove_stud(self, idd, name):
        self.undo_add_stud(idd, name)

    def redo_remove_disc(self, idd, name):
        self.undo_add_disc(idd, name)

    def redo_add_grade(self, idd):
        grade = self.srvGrades.repoGrade.dictionary[idd]
        self.srvGrades.repoGrade.add_grade(grade.discipline_id, grade.student_id,
                                           grade.grade, Grade, GradeError,
                                           self.srvStud.repoStud, self.srvDisc.repoDisc)
