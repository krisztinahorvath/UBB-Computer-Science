# todo create big class validation and create subclasses for each of them
# todo check if the given grade is a positive number, grade>0

class ValidEntity:
    """
    This class verifies if an object of type Student or Discipline(which inherit properties from class Entity)
    is valid.
    """
    def __init__(self, ids, name, dicti):
        self.ids = ids
        self.name = name
        self.repo = dicti

    def valid_id(self, errorType):
        """
        This function validates the id of an object of type Entity() -> Student() or Discipline()
        :param errorType: StudentError or DisciplineError()
        """
        try:
            if self.ids[0].isdigit() is False and self.ids[0] not in ["+", "-"]:
                raise errorType("The id should be an integer!")
            for i in range(1, len(self.ids)):
                if self.ids[i].isdigit() is False and self.ids[i]:
                    raise errorType("The id should be an integer!")
            if int(self.ids) < 0:
                raise errorType("The id should be a positive number!")
        except errorType as ve:
            raise ve

    def valid_add(self, errorType):
        """
        This function validates if an object of type Entity() -> Student() or Discipline(), can be added to
        its corresponding repo
        :param errorType: StudentError or DisciplineError()
        """
        try:
            self.valid_id(errorType)
            if str(self.ids) in self.repo:
                raise errorType("An object with id: " + str(self.ids) + " already exists!")
        except errorType as ve:
            raise ve

    def valid_remove_update(self, errorType):
        """
        This function validates if an object of type Entity() -> Student() or Discipline(), can be removed or
        updated from/in its corresponding repo
        :param errorType: StudentError or DisciplineError()
        """
        try:
            self.valid_id(errorType)
            if str(self.ids) not in self.repo:
                raise errorType("There is no object with id: " + str(self.ids) + " in the list!")
        except errorType as ve:
            raise ve


class ValidGrade:
    """
    This class verifies if an object of type Grade() is valid
    """
    def __init__(self, discipline_id, student_id, grade, student_repo, discipline_repo):
        self.discipline_id = discipline_id
        self.student_id = student_id
        self.grade = grade
        self.student_repo = student_repo
        self.discipline_repo = discipline_repo

    def valid_id(self):
        """
        This function checks if the student id and discipline id of a grade are valid
        :return:
        """
        from src.services.exceptions import GradeError
        try:
            if self.discipline_id[0].isdigit() is False and self.discipline_id[0] not in ["+", "-"]:
                raise GradeError("The id should be an integer!")
            if self.student_id[0].isdigit() is False and self.student_id[0] not in ["+", "-"]:
                raise GradeError("The id should be an integer!")
            for i in range(0, len(self.discipline_id)):
                if self.discipline_id[i].isdigit() is False and self.discipline_id[i]:
                    raise GradeError("The id should be an integer!")
            for i in range(0, len(self.student_id)):
                if self.student_id[i].isdigit() is False and self.student_id[i]:
                    raise GradeError("The id should be an integer!")
            self.discipline_id = int(self.discipline_id)
            self.student_id = int(self.student_id)
        except GradeError as ge:
            raise ge

        # if int(self.discipline_id) < 0 or int(self.student_id) < 0:
        #     raise GradeError("The ids should be positive numbers!")
        if str(self.discipline_id) not in self.discipline_repo:
            raise GradeError("The discipline with id: " + str(self.discipline_id) + " does not exist!")

        if str(self.student_id) not in self.student_repo:
            raise GradeError("The student with id: " + str(self.student_id) + " does not exist!")

    def valid_grade(self):
        """
        This function checks if a grade is valid
        :return:
        """
        from src.services.exceptions import GradeError
        try:
            for i in range(0, len(self.grade)):
                if self.grade[i].isdigit() is False:
                    raise GradeError("The grade should be an integer!")
        except GradeError as ge:
            raise ge
        if not(0 < int(self.grade) <= 10):
            raise GradeError("The grade should be a strictly positive number, between 1 and 10!")
