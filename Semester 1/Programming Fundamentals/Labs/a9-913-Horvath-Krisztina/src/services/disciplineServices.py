from src.domain.discipline import Discipline
from src.repository.disciplineRepo import RepoDiscipline, DisciplineTextFileRepo, DisciplineBinaryFileRepo, \
    DisciplineJsonFileRepo


class DisciplineServices:
    """
    This class holds the methods for the disciplines
    """

    def __init__(self, repo_type, file_name):
        if repo_type == "inmemory":
            self.repoDisc = RepoDiscipline()
            self.repoDisc.random_objects(Discipline)
        elif repo_type == "textfiles":
            self.repoDisc = DisciplineTextFileRepo(file_name)
        elif repo_type == "binaryfiles":
            self.repoDisc = DisciplineBinaryFileRepo(file_name)
        else:
            self.repoDisc = DisciplineJsonFileRepo(file_name)

    def add_stud_disc(self, idd, name):
        """
        Adds an object of type Discipline() to the repo that it belongs too
        :param idd: discipline id
        :param name: discipline name
        :return:
        """
        from src.services.exceptions import DisciplineError
        try:
            self.repoDisc.add_stud_disc(idd, name, Discipline, DisciplineError)
        except DisciplineError as ve:
            raise ve

    def update_stud_disc(self, idd, name):
        """
        Updates an object of type Discipline() in the repo that it belongs too
        :param idd: discipline id
        :param name: discipline name
        """
        from src.services.exceptions import DisciplineError
        try:
            self.repoDisc.update_stud_disc(idd, name, Discipline, DisciplineError)
        except DisciplineError as ve:
            raise ve

    def remove_disc(self, idd, grade_repo):
        """
        Removes an object of type Discipline() from the discipline repo
        :param idd: discipline id
        :param grade_repo: grade repo
        """
        from src.services.exceptions import DisciplineError
        try:
            self.repoDisc.remove_disc(idd, DisciplineError, grade_repo)
        except DisciplineError as ve:
            raise ve

    def disc_grades_desc(self, grade_repo, stud_repo, disc_list):
        nr_studs = len(stud_repo)
        nr_disc = len(self.repoDisc.dictionary)
        avg_disc = 0
        number = []
        ids = []
        for disc in self.repoDisc.dictionary:
            for stud in stud_repo:
                # if grade_repo.dictionarydiscipline_id == disc and grade_repo.student_id == stud:
                avg_grade = grade_repo.avg_grade_stud_disc(stud, disc)
                avg_disc += avg_grade
            number.append(round(avg_disc / (nr_studs * nr_disc), 2))
            ids.append(disc)
        new_list = list(zip(number, ids))
        new_list.sort(reverse=True)
        # print(new_list)
        disc_list.append(new_list)
        # disc_list = copy(new_list)
