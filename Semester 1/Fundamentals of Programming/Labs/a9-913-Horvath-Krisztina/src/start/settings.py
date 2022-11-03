import json
import pickle

from src.domain.discipline import Discipline
from src.domain.grade import Grade
from src.domain.student import Student
from src.services.disciplineServices import DisciplineServices
from src.services.gradeServices import GradeServices
from src.services.studentServices import StudentServices

# repository = "binaryfiles"
# students = "students.pickle"
# disciplines = "disciplines.pickle"
# grades = "grades.pickle"


# repository = "inmemory"
# students = ""
# disciplines = ""
# grades = ""

# f = open("students.json", "w")
# g = open("disciplines.json", "w")
# h = open("grades.json", "w")


# stud = StudentServices("jsonfiles", "students.json")
# stud.repoStud.random_objects(Student)
#
# with open("students.json", "w") as f:
#     json.dump(stud.repoStud.dictionary, f)
#
# f.close()
#
# disc = DisciplineServices("jsonfiles", "disciplines.json")
# disc.repoDisc.random_objects(Discipline)
#
# with open("disciplines.json", "w") as h:
#     json.dump(disc.repoDisc.dictionary, h)
#
# h.close()
#
# grade = GradeServices(disc.repoDisc.dictionary, stud.repoStud.dictionary, "jsonfiles", "grades.json")
# grade.repoGrade.random_grades(Grade, disc.repoDisc.dictionary, stud.repoStud.dictionary)
#
# with open("grades.json", "w") as g:
#     json.dump(grade.repoGrade.dictionary, g)
#
# g.close()

repository = "textfiles"
students = "students.txt"
disciplines = "disciplines.txt"
grades = "grades.txt"

# repository = "jsonfiles"
# students = "students.json"
# disciplines = "disciplines.json"
# grades = "grades.json"



