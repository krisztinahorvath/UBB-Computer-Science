class Grade:
    def __init__(self, idg, idd, ids, grade_value):
        """
        initialize a class Grade that creates a Grade() object that holds the information about
        a grade(the discipline at which is given, the student who has this grade, its value)
        :param idg: grade id
        :param idd: discipline id
        :param ids: student it
        :param grade_value: grade value
        """
        self.__grade_id = idg
        self.__discipline_id = idd
        self.__student_id = ids
        self.__grade_value = grade_value

    @property
    def id(self):
        return self.__grade_id

    @property
    def discipline_id(self):
        return self.__discipline_id

    @property
    def student_id(self):
        return self.__student_id

    @property
    def grade(self):
        return self.__grade_value

    def __str__(self):
        return str(self.discipline_id) + " " + str(self.student_id) + " " + str(self.grade)
