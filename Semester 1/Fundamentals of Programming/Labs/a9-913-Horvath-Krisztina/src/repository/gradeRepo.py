import json
import pickle
from random import randrange, choice

from src.domain.grade import Grade
from src.repository.validations import ValidGrade
from src.services.exceptions import GradeError


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

            if len(self.dictionary) == 0:
                next_pos = 0
            else:
                next_pos = int(list(self.dictionary.keys())[-1])  # the last key from the grade repo
            next_pos += 1

            self.dictionary[str(next_pos)] = entityType(next_pos, discipline_id, student_id, grade)

        except errorType as ve:
            raise ve

    def last_pos(self):
        return int(list(self.dictionary.keys())[-1])


class GradeTextFileRepo(RepoGrade):
    def __init__(self, file_name):
        super().__init__()

        self._file_name = file_name
        self._load_file()

    def _load_file(self):
        from src.repository.disciplineRepo import DisciplineTextFileRepo
        from src.repository.studentRepo import StudentTextFileRepo

        f = open(self._file_name, "rt")
        for line in f.readlines():
            line = line.strip()
            if len(line) > 0:
                disc, stud, grade = line.split(maxsplit=2, sep=',')
                repoStud = StudentTextFileRepo("students.txt")
                repoDisc = DisciplineTextFileRepo("disciplines.txt")
                self.add_grade(disc, stud, grade, Grade, GradeError, repoStud.dictionary, repoDisc.dictionary)

        self._save_file()
        f.close()

    def _save_file(self):
        f = open(self._file_name, "wt")
        for grade in self.dictionary:
            f.write(str(self.dictionary[grade].discipline_id) + ',' + str(self.dictionary[grade].student_id) + ',' +
                    str(self.dictionary[grade].grade) + '\n')

        f.close()

    def add_grade(self, discipline_id, student_id, grade, entityType, errorType, stud_repo, disc_repo):
        super().add_grade(discipline_id, student_id, grade, entityType, errorType, stud_repo, disc_repo)

        self._save_file()


class GradeBinaryFileRepo(RepoGrade):
    def __init__(self, file_name):
        super().__init__()

        self._file_name = file_name
        self._load_file()

    def _load_file(self):
        with open(self._file_name, "rb") as f:
            try:
                self.dictionary = pickle.load(f)
            except EOFError:
                pass

        self._save_file()
        f.close()

    def _save_file(self):
        with open(self._file_name, "wb") as f:
            pickle.dump(self.dictionary, f)

        f.close()

    def add_grade(self, discipline_id, student_id, grade, entityType, errorType, stud_repo, disc_repo):
        super().add_grade(discipline_id, student_id, grade, entityType, errorType, stud_repo, disc_repo)

        self._save_file()


class GradeJsonFileRepo(RepoGrade):
    def __init__(self, file_name):
        super().__init__()

        self._file_name = file_name
        self._load_file()

    def _load_file(self):
        with open(self._file_name, "r") as f:
            try:
                self.dictionary = json.load(f)
            except EOFError:
                pass

        self._save_file()
        f.close()

    def _save_file(self):
        with open(self._file_name, "w") as f:
            json.dump(self.dictionary, f)

        f.close()

    def add_grade(self, discipline_id, student_id, grade, entityType, errorType, stud_repo, disc_repo):
        super().add_grade(discipline_id, student_id, grade, entityType, errorType, stud_repo, disc_repo)

        self._save_file()



