import unittest

from src.domain.discipline import Discipline
from src.domain.entity import Entity
from src.domain.grade import Grade
from src.domain.student import Student
from src.repository.disciplineRepo import RepoDiscipline
from src.repository.gradeRepo import RepoGrade
from src.repository.studentRepo import RepoStudent
from src.repository.validations import ValidEntity, ValidGrade
from src.services.exceptions import StudentError, DisciplineError, GradeError


class TestValidEntity(unittest.TestCase):
    def setUp(self) -> None:
        self.repoStud = RepoStudent()
        self.repoStud.random_objects(Student)
        self.stud = ValidEntity("11a", "Mara", self.repoStud.dictionary)

        self.repoDisc = RepoDiscipline()
        self.repoDisc.random_objects(Discipline)

        self.disc = ValidEntity("12", "FP", self.repoDisc.dictionary)

    def tearDown(self) -> None:
        pass

    def test_valid_id(self):
        with self.assertRaises(StudentError) as re:
            self.stud.valid_id(StudentError)
        self.assertEqual(str(re.exception), "The id should be an integer!")

        with self.assertRaises(StudentError) as re:
            valid = ValidEntity("-15", "Mariuca", self.repoStud.dictionary)
            valid.valid_id(StudentError)
        self.assertEqual(str(re.exception), "The id should be a positive number!")

        with self.assertRaises(StudentError) as re:
            valid = ValidEntity("1%5", "Mariuca", self.repoStud.dictionary)
            valid.valid_id(StudentError)
        self.assertEqual(str(re.exception), "The id should be an integer!")

        with self.assertRaises(DisciplineError) as re:
            valid = ValidEntity("-29", "Match", self.repoDisc.dictionary)
            valid.valid_id(DisciplineError)
        self.assertEqual(str(re.exception), "The id should be a positive number!")

        with self.assertRaises(DisciplineError) as re:
            valid = ValidEntity("*29", "Match", self.repoDisc.dictionary)
            valid.valid_id(DisciplineError)
        self.assertEqual(str(re.exception), "The id should be an integer!")

        with self.assertRaises(DisciplineError) as re:
            valid = ValidEntity("1%5", "Mariuca", self.repoDisc.dictionary)
            valid.valid_id(DisciplineError)
        self.assertEqual(str(re.exception), "The id should be an integer!")

        self.disc = Entity("12", "FP")
        self.assertEqual(str(self.disc), "id: 12, Name: FP")

        # with self.assertRaises(GradeError) as re: # todo
        #     valid = ValidGrade("-22", "-15", "10", self.repoStud.dictionary, self.repoDisc.dictionary)
        #     valid.valid_id()
        # self.assertEqual(str(re.exception), "The ids should be positive numbers!")

    def test_valid_add(self):
        valid = ValidEntity("110", "Ana", self.repoStud.dictionary)
        valid.valid_add(StudentError)
        self.repoStud.dictionary["100"] = Student("100", "Mariuca")

        with self.assertRaises(StudentError) as se:
            valid = ValidEntity("100", "Mara", self.repoStud.dictionary)
            valid.valid_add(StudentError)
        self.assertEqual(str(se.exception), "An object with id: " + str(valid.ids) + " already exists!")

        valid = ValidEntity("111", "FP", self.repoDisc.dictionary)
        valid.valid_add(DisciplineError)
        self.repoDisc.dictionary["111"] = Discipline("111", "FP")

        with self.assertRaises(DisciplineError) as se:
            valid = ValidEntity("111", "Math", self.repoDisc.dictionary)
            valid.valid_add(DisciplineError)
        self.assertEqual(str(se.exception), "An object with id: " + str(valid.ids) + " already exists!")

    def test_valid_remove_update(self):
        self.repoStud.dictionary["100"] = Student("100", "Mariuca")
        valid = ValidEntity("100", "Mariuca", self.repoStud.dictionary)
        valid.valid_remove_update(StudentError)

        with self.assertRaises(StudentError) as se:
            valid = ValidEntity("99", "Elsa", self.repoStud.dictionary)
            valid.valid_remove_update(StudentError)
        self.assertEqual(str(se.exception), "There is no object with id: " + str(valid.ids) + " in the list!")

        self.repoDisc.dictionary["222"] = Discipline("222", "CSA")
        valid = ValidEntity("222", "CSA", self.repoDisc.dictionary)
        valid.valid_remove_update(DisciplineError)

        with self.assertRaises(DisciplineError) as se:
            valid = ValidEntity("1000", "Math", self.repoDisc.dictionary)
            valid.valid_remove_update(DisciplineError)
        self.assertEqual(str(se.exception), "There is no object with id: " + str(valid.ids) + " in the list!")


class TestValidGrade(unittest.TestCase):
    def setUp(self) -> None:
        self.studentRepo = RepoStudent()
        self.studentRepo.random_objects(Student)

        self.disciplineRepo = RepoDiscipline()
        self.disciplineRepo.random_objects(Discipline)

        self.gradeRepo = RepoGrade()
        self.gradeRepo.random_grades(Grade, self.disciplineRepo.dictionary, self.studentRepo.dictionary)

    def tearDown(self) -> None:
        pass

    def test_valid_id(self):
        with self.assertRaises(GradeError) as ge:
            grade = ValidGrade("11a", "1%a", "10", self.studentRepo.dictionary, self.gradeRepo.dictionary)
            grade.valid_id()
            grade.valid_grade()
        self.assertEqual(str(ge.exception), "The id should be an integer!")

        self.studentRepo.add_stud_disc("100", "Mara", Student, StudentError)
        with self.assertRaises(GradeError) as ge:
            grade = ValidGrade("-11", "100", "10", self.studentRepo.dictionary, self.gradeRepo.dictionary)
            grade.valid_id()
            grade.valid_grade()
        self.assertEqual(str(ge.exception), "The id should be an integer!")

        with self.assertRaises(GradeError) as ge:
            grade = ValidGrade("*11", "100", "10", self.studentRepo.dictionary, self.gradeRepo.dictionary)
            grade.valid_id()
            grade.valid_grade()
        self.assertEqual(str(ge.exception), "The id should be an integer!")

        self.disciplineRepo.add_stud_disc("102", "CSA", Discipline, DisciplineError)
        with self.assertRaises(GradeError) as ge:
            grade = ValidGrade("102", "/a12", "8", self.studentRepo.dictionary, self.gradeRepo.dictionary)
            grade.valid_id()
        self.assertEqual(str(ge.exception), "The id should be an integer!")

        with self.assertRaises(GradeError) as ge:
            grade = ValidGrade("99", "-2", "10", self.studentRepo.dictionary, self.disciplineRepo.dictionary)
            grade.valid_id()
            grade.valid_grade()
        self.assertEqual(str(ge.exception), "The id should be an integer!")

        with self.assertRaises(GradeError) as ge:
            grade = ValidGrade("101", "100", "6", self.studentRepo.dictionary, self.disciplineRepo.dictionary)
            grade.valid_id()
            grade.valid_grade()
        self.assertEqual(str(ge.exception), "The discipline with id: " + str(grade.discipline_id) + " does not exist!")

        self.disciplineRepo.add_stud_disc("100", "CSA", Discipline, DisciplineError)
        with self.assertRaises(GradeError) as ge:
            grade = ValidGrade("100", "222", "6", self.studentRepo.dictionary, self.disciplineRepo.dictionary)
            grade.valid_id()
            grade.valid_grade()
        self.assertEqual(str(ge.exception), "The student with id: " + str(grade.student_id) + " does not exist!")

        self.disciplineRepo.add_stud_disc("99", "CSA", Discipline, DisciplineError)
        with self.assertRaises(GradeError) as ge:
            grade = ValidGrade("99", "222", "6", self.studentRepo.dictionary, self.disciplineRepo.dictionary)
            grade.valid_id()
            grade.valid_grade()
        self.assertEqual(str(ge.exception), "The student with id: " + str(grade.student_id) + " does not exist!")

        with self.assertRaises(GradeError) as ge:
            grade = ValidGrade("99", "-100", "9", self.studentRepo.dictionary, self.disciplineRepo.dictionary)
            grade.valid_id()
        # self.assertEqual(str(ge.exception), "The ids should be positive numbers!")
        self.assertEqual(str(ge.exception), "The id should be an integer!")

        with self.assertRaises(GradeError) as ge:
            grade = ValidGrade("99", "888", "9", self.studentRepo.dictionary, self.disciplineRepo.dictionary)
            grade.valid_id()
        self.assertEqual(str(ge.exception), "The student with id: " + str(grade.student_id) + " does not exist!")

        with self.assertRaises(GradeError) as ge: # todo fvghjqkwedfvtygujh
            grade = ValidGrade("99.3", "888", "9", self.studentRepo.dictionary, self.disciplineRepo.dictionary)
            grade.valid_id()
        self.assertEqual(str(ge.exception), "The id should be an integer!")

        grade = Grade("12", "100", "99", "9")
        self.assertEqual(grade.id, "12")
        self.assertEqual(str(grade), "100 99 9")

    def test_valid_grade(self):
        self.studentRepo.add_stud_disc("100", "Mara", Student, StudentError)
        self.disciplineRepo.add_stud_disc("99", "FP", Discipline, DisciplineError)
        grade = ValidGrade("99", "100", "9", self.studentRepo.dictionary, self.disciplineRepo.dictionary)
        grade.valid_id()
        grade.valid_grade()

        with self.assertRaises(GradeError) as ge:
            grade = ValidGrade("99", "100", "11", self.studentRepo.dictionary, self.disciplineRepo.dictionary)
            grade.valid_grade()
        self.assertEqual(str(ge.exception), "The grade should be a strictly positive number, between 1 and 10!")

        with self.assertRaises(GradeError) as ge:
            grade = ValidGrade("99", "100", "9%0", self.studentRepo.dictionary, self.disciplineRepo.dictionary)
            grade.valid_grade()
        self.assertEqual(str(ge.exception), "The grade should be an integer!")

        with self.assertRaises(GradeError) as ge:
            grade = ValidGrade("99", "100", "9.0", self.studentRepo.dictionary, self.disciplineRepo.dictionary)
            grade.valid_grade()
        self.assertEqual(str(ge.exception), "The grade should be an integer!")


if __name__ == "__main__":
    unittest.main()