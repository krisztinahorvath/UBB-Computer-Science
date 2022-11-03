from src.repository.repoEntity import Repo
from src.repository.validations import ValidEntity


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


