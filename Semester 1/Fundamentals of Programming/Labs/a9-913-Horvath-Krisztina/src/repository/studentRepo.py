import json
import pickle

from src.domain.student import Student
from src.repository.repoEntity import Repo
from src.repository.validations import ValidEntity
from src.services.exceptions import StudentError


class RepoStudent(Repo):
    """
    This class inherits from class Repo() its methods and properties, and it holds the information related
    to students
    """

    def __init__(self):
        dict_random = {"1": "Alina", "2": "Mircea", "3": "Popescu", "4": "Ionescu", "5": "Asanache", "6": "Miranda",
                       "7": "Ionel", "8": "Lucescu", "9": "Copos", "10": "Shakira", "11": "Beyonce", "12": "Mihaescu",
                       "13": "Nastase", "14": "Halep", "15": "Raducanu", "16": "Tipatescu", "17": "Pristanda",
                       "18": "Farfuridi", "19": "Branzovenescu", "20": "Trahanache", "21": "Stark", "22": "Parker",
                       "23": "Depp", "24": "Johnson", "25": "Karen", "26": "Cyrus", "27": "Hayek", "28": "Jackson",
                       "29": "Keppa", "30": "Johansson", "31": "Hawking", "32": "King", "33": "Harper", "34": "Boss",
                       "35": "Gucci", "36": "Pucci", "37": "Jobs", "38": "Ritchie", "39": "Frey", "40": "Simpson"}
        super().__init__(dict_random)

    def remove_stud(self, idd, errorType, grade_repo):
        """
        Removes from the student repository student with id = idd and removes all the grades that the student has from
        the grade repository.
        :param idd: student id
        :param errorType: Student error - used to avoid circular imports
        :param grade_repo: grade repository
        """
        try:
            if len(self.dictionary) == 0:
                raise errorType("There are no elements that can be deleted!")

            valid = ValidEntity(idd, "", self.dictionary)
            valid.valid_id(errorType)
            valid.valid_remove_update(errorType)

            self.dictionary.pop(str(idd))

            remove_keys = []

            for i in grade_repo:
                if str(grade_repo[i].student_id) == str(idd):
                    remove_keys.append(i)

            for i in remove_keys:
                grade_repo.pop(i)

        except errorType as se:
            raise se


class StudentTextFileRepo(RepoStudent):
    def __init__(self, file_name):
        super().__init__()

        self._file_name = file_name
        self._load_file()

    def _load_file(self):
        f = open(self._file_name, "rt")
        for line in f.readlines():
            line = line.strip()
            if len(line) > 0:
                idd, name = line.split(maxsplit=1, sep=',')
                self.add_stud_disc(idd, name, Student, StudentError)

        self._save_file()
        f.close()

    def _save_file(self):
        f = open(self._file_name, "wt")
        for stud in self.dictionary:
            f.write(str(stud) + ',' + str(self.dictionary[stud].name) + '\n')

        f.close()

    def add_stud_disc(self, idd, name, entityType, errorType):
        super(StudentTextFileRepo, self).add_stud_disc(idd, name, entityType, errorType)

        self._save_file()

    def update_stud_disc(self, idd, name, entityType, errorType):
        super().update_stud_disc(idd, name, entityType, errorType)

        self._save_file()

    def remove_stud(self, idd, errorType, grade_repo):
        super().remove_stud(idd, errorType, grade_repo)

        self._save_file()


class StudentBinaryFileRepo(RepoStudent):
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

    def add_stud_disc(self, idd, name, entityType, errorType):
        super(StudentBinaryFileRepo, self).add_stud_disc(idd, name, entityType, errorType)

        self._save_file()

    def update_stud_disc(self, idd, name, entityType, errorType):
        super().update_stud_disc(idd, name, entityType, errorType)

        self._save_file()

    def remove_stud(self, idd, errorType, grade_repo):
        super().remove_stud(idd, errorType, grade_repo)

        self._save_file()


class StudentJsonFileRepo(RepoStudent):
    def __init__(self, file_name):
        super().__init__()

        self._file_name = file_name
        self._load_file()

    def _load_file(self):
        with open(self._file_name, "r") as f:
            try:
                self.dictionary = json.load(f)
            except json.decoder.JSONDecodeError:
                pass

        self._save_file()
        f.close()

    def _save_file(self):
        with open(self._file_name, "w") as f:
            json.dump(self.dictionary, f)

        f.close()

    def add_stud_disc(self, idd, name, entityType, errorType):
        super(StudentJsonFileRepo, self).add_stud_disc(idd, name, entityType, errorType)

        self._save_file()

    def update_stud_disc(self, idd, name, entityType, errorType):
        super().update_stud_disc(idd, name, entityType, errorType)

        self._save_file()

    def remove_stud(self, idd, errorType, grade_repo):
        super().remove_stud(idd, errorType, grade_repo)

        self._save_file()






