from src.repository.repoEntity import Repo
from src.repository.validations import ValidEntity


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
