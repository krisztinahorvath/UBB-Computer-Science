import json

from src.domain.discipline import Discipline
from src.repository.repoEntity import Repo
from src.repository.validations import ValidEntity
from src.services.exceptions import DisciplineError
import pickle


class RepoDiscipline(Repo):
    """
    This class inherits from class Repo() its methods and properties, and it holds the information related
    to disciplines
    """

    def __init__(self):
        dict_random = {"1": "Fundamentals of Programming", "2": "CSA", "3": "Algebra", "4": "Calculus", "5": "PE",
                       "6": "Logic",
                       "7": "Communication", "8": "Graphs", "9": "Music", "10": "Drawing", "11": "Debugging 101",
                       "12": "Dynamical Systems",
                       "13": "OOP", "14": "Geometry", "15": "Data structures and algorithms", "16": "Computer networks",
                       "17": "Databases",
                       "18": "Probability and statistics", "19": "Web programming", "20": "AI",
                       "21": "Numerical calculus", "22": "Computer vision and deep learning ",
                       "23": "Introduction in Robotics", "24": "Cloud Application Architecture",
                       "25": "Virtual reality", "26": " Affective Computing", "27": "English", "28": "French",
                       "29": "Spanish", "30": "Japanese", "31": "Mandarin", "32": "AP Calculus", "33": "Psychology",
                       "34": "Biology",
                       "35": "Socializing", "36": "Physics", "37": "Chemistry", "38": "Debate", "39": "Fashion 101",
                       "40": "Criminology"}
        super().__init__(dict_random)

    def remove_disc(self, idd, errorType, grade_repo):
        """
        Removes from the discipline repository discipline with id = idd and removes all the grades at that discipline from
        the grade repository.
        :param idd: discipline id
        :param errorType: Discipline error - used to avoid circular imports
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
                if str(grade_repo[i].discipline_id) == str(idd):
                    remove_keys.append(i)

            for i in remove_keys:
                grade_repo.pop(i)

        except errorType as ve:
            raise ve


class DisciplineTextFileRepo(RepoDiscipline):
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
                self.add_stud_disc(idd, name, Discipline, DisciplineError)

        self._save_file()
        f.close()

    def _save_file(self):
        f = open(self._file_name, "wt")
        for disc in self.dictionary:
            f.write(str(disc) + ',' + str(self.dictionary[disc].name) + '\n')

        f.close()

    def add_stud_disc(self, idd, name, entityType, errorType):
        super(DisciplineTextFileRepo, self).add_stud_disc(idd, name, entityType, errorType)

        self._save_file()

    def update_stud_disc(self, idd, name, entityType, errorType):
        super().update_stud_disc(idd, name, entityType, errorType)

        self._save_file()

    def remove_disc(self, idd, errorType, grade_repo):
        super().remove_disc(idd, errorType, grade_repo)

        self._save_file()


class DisciplineBinaryFileRepo(RepoDiscipline):
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
        super(DisciplineBinaryFileRepo, self).add_stud_disc(idd, name, entityType, errorType)

        self._save_file()

    def update_stud_disc(self, idd, name, entityType, errorType):
        super().update_stud_disc(idd, name, entityType, errorType)

        self._save_file()

    def remove_disc(self, idd, errorType, grade_repo):
        super().remove_disc(idd, errorType, grade_repo)

        self._save_file()


class DisciplineJsonFileRepo(RepoDiscipline):
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

    def add_stud_disc(self, idd, name, entityType, errorType):
        super(DisciplineJsonFileRepo, self).add_stud_disc(idd, name, entityType, errorType)

        self._save_file()

    def update_stud_disc(self, idd, name, entityType, errorType):
        super().update_stud_disc(idd, name, entityType, errorType)

        self._save_file()

    def remove_disc(self, idd, errorType, grade_repo):
        super().remove_disc(idd, errorType, grade_repo)

        self._save_file()

