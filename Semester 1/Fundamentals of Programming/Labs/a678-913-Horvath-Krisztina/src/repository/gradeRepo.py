from random import randrange, choice
from src.repository.validations import ValidGrade


class RepoGrade:
    def __init__(self):
        self.dictionary = dict()

    def random_grades(self, entityType, disc_dict, stud_dict):
        """
        This function generates random grades at each discipline for two random students.
        :param entityType: Grade() - we use this to avoid circular imports
        :param disc_dict: discipline repo -> dictionary
        :param stud_dict: student repo -> dictionary
        """
        id_grade = 0
        for i in disc_dict:
            grade1 = randrange(1, 11, 1)
            grade2 = randrange(1, 11, 1)

            id_grade += 1

            random_stud1 = choice(list(stud_dict))
            random_stud2 = choice(list(stud_dict))

            self.dictionary[str(id_grade)] = entityType(str(id_grade), str(disc_dict[i].id),
                                                        str(stud_dict[random_stud1].id),
                                                        str(grade1))

            id_grade += 1

            self.dictionary[str(id_grade)] = entityType(str(id_grade), str(disc_dict[i].id),
                                                        str(stud_dict[random_stud2].id),
                                                        str(grade2))

    def add_grade(self, discipline_id, student_id, grade, entityType, errorType, stud_repo, disc_repo):
        """
        This function adds a grade to the grade repo
        :param discipline_id: discipline id
        :param student_id: student id
        :param grade: grade value
        :param entityType: Grade() -> used to avoid circular imports
        :param errorType: GradeError() -> used to avoid circular imports
        :param stud_repo: student repository
        :param disc_repo: discipline repository
        """
        try:
            valid = ValidGrade(discipline_id, student_id, grade, stud_repo, disc_repo)
            valid.valid_id()
            valid.valid_grade()

            next_pos = int(list(self.dictionary.keys())[-1])  # the last key from the grade repo
            next_pos += 1

            self.dictionary[str(next_pos)] = entityType(next_pos, discipline_id, student_id, grade)

        except errorType as ve:
            raise ve

    def last_pos(self):
        return int(list(self.dictionary.keys())[-1])
