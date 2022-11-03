from random import choice

from src.repository.validations import ValidEntity


class Repo:
    """
    This class holds the common methods and properties of classes DisciplineRepo() and StudentRepo()
    """
    def __init__(self, given_dict):
        self.dictionary = dict()
        self.dict_random = given_dict

    def random_objects(self, entityType):
        """
        Generates a dictionary of 20 random objects of type entityType
        :param entityType: an object of type Student() or Discipline()
        :return:
        """
        while len(self.dictionary) < 20:
            r = choice(list(self.dict_random))
            self.dictionary[r] = entityType(r, self.dict_random[r])
            self.dict_random.pop(r)  # we remove the newest added object so that we don't add them twice

    def add_stud_disc(self, idd, name, entityType, errorType):  # add for students and disciplines
        """
        Adds an object of type entityType to the repo that it belongs too
        :param idd: object id
        :param name: object name
        :param entityType: Student() or Discipline()
        :param errorType: StudentError or DisciplineError
        :return:
        """
        try:
            valid = ValidEntity(idd, name, self.dictionary)
            valid.valid_add(errorType)
            self.dictionary[idd] = entityType(idd, name)  # adds a student as a Student object
        except errorType as ve:
            raise ve

    def update_stud_disc(self, idd, name, entityType, errorType):  # update for students and disciplines
        """
        Updates an object of type entityType in the repo that it belongs too
        :param idd: object id
        :param name: object name
        :param entityType: Student() or Discipline()
        :param errorType: StudentError or DisciplineError
        :return:
        """
        try:
            valid = ValidEntity(idd, "", self.dictionary)
            valid.valid_id(errorType)
            valid.valid_remove_update(errorType)

            self.dictionary[idd] = entityType(idd, name)

        except errorType as ve:
            raise ve