from src.domain.student import Student
from src.repository.studentRepo import RepoStudent


class StudentServices:
    def __init__(self):
        self.repoStud = RepoStudent()
        self.repoStud.random_objects(Student)

    def add_stud_disc(self, idd, name):
        """
        Adds an object of type Student() to the repo that it belongs too
        :param idd: student id
        :param name: student name
        """
        from src.services.exceptions import StudentError
        try:
            self.repoStud.add_stud_disc(idd, name, Student, StudentError)
        except StudentError as ve:
            raise ve

    def update_stud_disc(self, idd, name):
        """
        Updates an object of type Student() in the student repo
        :param idd: student id
        :param name: student name
        :return:
        """
        from src.services.exceptions import StudentError
        try:
            self.repoStud.update_stud_disc(idd, name, Student, StudentError)
        except StudentError as ve:
            raise ve

    def remove_stud(self, idd, grade_repo):
        """
        Removes a student from the student repo and all its grades from the grade repo
        :param idd: student id
        :param grade_repo: grade repository
        :return:
        """
        from src.services.exceptions import StudentError
        try:
            self.repoStud.remove_stud(idd, StudentError, grade_repo)
        except StudentError as ve:
            raise ve

    def failing_studs(self, grade_repo, disc_repo, failing_dict): #, grade_avg_stud_dict
        for stud in self.repoStud.dictionary:
            for disc in disc_repo:
                avg_grades = grade_repo.avg_grade_stud_disc(stud, disc)
                if avg_grades < 5.00 and float(avg_grades) != 0:
                    failing_dict[stud] = self.repoStud.dictionary[stud]
                # grade_avg_stud_dict[str(avg_grades)] =

    # @staticmethod
    # def sort_descending(d):
    #     key2 = list(d.keys())
    #     for i in range(0, len(key2)-1):
    #         for j in range(i+1, len(key2)):
    #             if float(i) < float(j):
    #                 aux = d[i]
    #                 d[i] = d[j]
    #                 d[j] = aux

    def best_studs_function(self, grade_repo, disc_repo, best_studs):
        nrs = len(self.repoStud.dictionary)
        numbers = []
        ids = []
        if nrs != 0:
            for stud in self.repoStud.dictionary:
                sums = 0
                for disc in disc_repo:
                    avg_grades = grade_repo.avg_grade_stud_disc(stud, disc)
                    sums += avg_grades
                # best_studs.append([round(sums/nrs, 2), stud])
                numbers.append(round(sums/nrs, 2))
                ids.append(stud)
            best_studs = list(zip(numbers, ids))
            best_studs.sort(reverse=True)
            print(best_studs)





