from src.services.gradeServices import GradeServices


class Prints:
    def __init__(self, students, disciplines, grades):
        self.repoStud = students
        self.repoDisc = disciplines
        self.repoGrade = grades

    @staticmethod
    def print_menu():
        print("\nMenu:\n\tStudents\n\tDisciplines\n\tGrades\n\tSearch\n\t"
              "Statistics\n\tUndo\n\tRedo\n\tExit\n")

    @staticmethod
    def print_menu_stud_disc():
        print("\nServices:\n\tadd\n\tremove\n\tupdate\n\tlist\n")

    def print_stud(self):
        for i in self.repoStud.dictionary:
            print(str(self.repoStud.dictionary[i]))

    def print_disc(self):
        for i in self.repoDisc.dictionary:
            print(str(self.repoDisc.dictionary[i]))

    @staticmethod
    def print_menu_grades():
        print("\nServices:\n\tadd\n\tlist\n")

    def print_grades(self):
        print("\nFormat: discipline id + student id + grade")
        for i in self.repoGrade.dictionary:
            print(str(self.repoGrade.dictionary[i]))

    @staticmethod
    def print_menu_search():
        print("\nSearch by:\n\tstudent id/name\n\tdiscipline id/title\n")

    @staticmethod
    def print_menu_search_student_discipline():
        print("\nSearch by:\n\tid\n\tname\n")

    def print_stud_disc_search_id(self, idd, repo_name):
        if repo_name == "student":
            repo = self.repoStud.dictionary
        else:
            repo = self.repoDisc.dictionary

        if idd in repo:
            print(str(repo[idd]))
        else:
            print("The " + repo_name + " with id: " + str(idd) + " does not exist!")

    def print_stud_disc_search_name(self, stud_name, repo_name):
        if repo_name == "student":
            repo = self.repoStud.dictionary
        else:
            repo = self.repoDisc.dictionary

        found = 0

        for i in repo:
            student = repo[i]
            student_name = student.name.lower()
            if student_name.find(stud_name) != -1:
                found = 1
                print(str(student))

        if found == 0:
            print("No " + repo_name + "s were found with name: " + str(stud_name))

    @staticmethod
    def print_menu_statistics():
        print("\nStatistics:\n\tfailing\n\tbest situation\n\tdiscipline\n")

    @staticmethod
    def print_statistics_failing(failing_dict):
        for i in failing_dict:
            print(str(failing_dict[i]))

    def print_avg_grades_stud(self): # todo display statistics nicer
        repo = GradeServices(self.repoDisc.dictionary, self.repoStud.dictionary)
        for i in self.repoStud.dictionary:
            for j in self.repoDisc.dictionary:
                print(str(self.repoStud.dictionary[i]) + " at " + str(self.repoDisc.dictionary[j])
                      + " " + str(repo.avg_grade_stud_disc(i, j)))

    def print_statistics_best(self, best_studs):
        for i in range(0, len(best_studs)):
            print(str(self.repoStud.dictionary[[best_studs[i][1]]]) + " " + str(best_studs[i][0]))



