from src.domain.grade import Grade
from src.repository.gradeRepo import RepoGrade, GradeTextFileRepo, GradeBinaryFileRepo


class GradeServices:
    """
    This class holds the methods for the grade services
    """
    def __init__(self, disc_dict, stud_dict, repo_type, file_name):
        if repo_type == "inmemory":
            self.repoGrade = RepoGrade()
            self.repoGrade.random_grades(Grade, disc_dict, stud_dict)
        elif repo_type == "textfiles":
            self.repoGrade = GradeTextFileRepo(file_name)
        else:
            self.repoGrade = GradeBinaryFileRepo(file_name)

    def add_grade(self, discipline_id, student_id, grade, stud_repo, disc_repo):
        """
        This function adds a grade to the grade repo
        :param discipline_id: discipline id
        :param student_id: student id
        :param grade: grade value
        :param stud_repo: student repository
        :param disc_repo: discipline repository
        """
        from src.services.exceptions import GradeError
        try:
            self.repoGrade.add_grade(discipline_id, student_id, grade, Grade, GradeError, stud_repo, disc_repo)
        except GradeError as ve:
            raise ve

    def avg_grade_stud_disc(self, id_stud, id_disc):
        nrs = 0
        sums = 0
        for i in self.repoGrade.dictionary:
            if self.repoGrade.dictionary[i].student_id == id_stud and \
                    self.repoGrade.dictionary[i].discipline_id == id_disc:
                nrs += 1
                sums += int(self.repoGrade.dictionary[i].grade)
        if sums == 0 and nrs == 0:
            return 0
        return round(sums/nrs, 2)



