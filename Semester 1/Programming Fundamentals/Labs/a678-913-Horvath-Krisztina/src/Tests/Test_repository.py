import unittest

from src.domain.discipline import Discipline
from src.domain.grade import Grade
from src.domain.student import Student
from src.repository.disciplineRepo import RepoDiscipline
from src.repository.gradeRepo import RepoGrade
from src.repository.studentRepo import RepoStudent
from src.services.exceptions import StudentError, DisciplineError, GradeError


class TestRepo(unittest.TestCase):
    def setUp(self) -> None:
        self.repoStud = RepoStudent()
        self.repoStud.random_objects(Student)
        self.repoDisc = RepoDiscipline()
        self.repoDisc.random_objects(Discipline)

    def tearDown(self) -> None:
        pass

    def test_random_objects(self):
        self.assertEqual(len(self.repoStud.dictionary), 20)
        self.assertEqual(len(self.repoStud.dict_random), 20)

        self.assertEqual(len(self.repoDisc.dictionary), 20)
        self.assertEqual(len(self.repoDisc.dict_random), 20)

    def test_add_stud_disc(self):
        self.repoStud.add_stud_disc("100", "Anna", Student, StudentError)
        self.assertEqual(len(self.repoStud.dictionary), 21)

        self.assertEqual(list(self.repoStud.dictionary.keys())[-1], "100")
        self.assertEqual(self.repoStud.dictionary["100"].name, "Anna")

        self.repoDisc.add_stud_disc("99", "CSA", Discipline, DisciplineError)
        self.assertEqual(len(self.repoDisc.dictionary), 21)

        self.assertEqual(list(self.repoDisc.dictionary.keys())[-1], "99")
        self.assertEqual(self.repoDisc.dictionary["99"].name, "CSA")

        with self.assertRaises(DisciplineError) as de:
            self.repoStud.add_stud_disc("100", "11", Discipline, DisciplineError)
        self.assertEqual(str(de.exception), "An object with id: 100 already exists!")

    def test_update_stud_disc(self):
        self.repoStud.add_stud_disc("100", "Anna", Student, StudentError)
        self.repoStud.update_stud_disc("100", "Mariuca", Student, StudentError)

        self.assertEqual(list(self.repoStud.dictionary.keys())[-1], "100")
        self.assertEqual(self.repoStud.dictionary["100"].name, "Mariuca")

        self.repoDisc.add_stud_disc("99", "CSA", Discipline, DisciplineError)
        self.repoDisc.update_stud_disc("99", "FP", Discipline, DisciplineError)
        self.assertEqual(len(self.repoDisc.dictionary), 21)

        self.assertEqual(list(self.repoDisc.dictionary.keys())[-1], "99")
        self.assertEqual(self.repoDisc.dictionary["99"].name, "FP")

        with self.assertRaises(StudentError) as se:
            self.repoStud.update_stud_disc("999", "", Student, StudentError)
        self.assertEqual(str(se.exception), "There is no object with id: 999 in the list!")


class TestStudentRepo(unittest.TestCase):
    def setUp(self) -> None:
        self.repoStud = RepoStudent()
        self.repoStud.random_objects(Student)

        self.repoDisc = RepoDiscipline()
        self.repoDisc.random_objects(Discipline)

        self.repoGrade = RepoGrade()
        self.repoGrade.random_grades(Grade, self.repoDisc.dictionary, self.repoStud.dictionary)

    def tearDown(self) -> None:
        pass

    def test_remove_stud(self):

        self.repoStud.add_stud_disc("101", "Ana", Student, StudentError)
        self.repoDisc.add_stud_disc("99", "CSA", Discipline, DisciplineError)
        self.repoGrade.add_grade("99", "101", "10", Grade, GradeError, self.repoStud.dictionary,
                                 self.repoDisc.dictionary)

        self.repoStud.remove_stud("101", StudentError, self.repoGrade.dictionary)
        self.assertEqual(len(self.repoStud.dictionary), 20)
        self.assertEqual(len(self.repoGrade.dictionary), 40)

        with self.assertRaises(StudentError) as se:
            empty_repo = RepoStudent()
            empty_repo.dictionary = ""
            empty_repo.remove_stud("10", StudentError, self.repoGrade.dictionary)
        self.assertEqual(str(se.exception), "There are no elements that can be deleted!")


class TestDisciplineRepo(unittest.TestCase):
    def setUp(self) -> None:
        self.repoStud = RepoStudent()
        self.repoStud.random_objects(Student)

        self.repoDisc = RepoDiscipline()
        self.repoDisc.random_objects(Discipline)

        self.repoGrade = RepoGrade()
        self.repoGrade.random_grades(Grade, self.repoDisc.dictionary, self.repoStud.dictionary)

    def tearDown(self) -> None:
        pass

    def test_remove_disc(self):
        self.repoStud.add_stud_disc("101", "Ana", Student, StudentError)
        self.repoDisc.add_stud_disc("99", "CSA", Discipline, DisciplineError)
        self.repoGrade.add_grade("99", "101", "10", Grade, GradeError, self.repoStud.dictionary,
                                 self.repoDisc.dictionary)

        self.repoDisc.remove_disc("99", DisciplineError, self.repoGrade.dictionary)
        self.assertEqual(len(self.repoDisc.dictionary), 20)
        self.assertEqual(len(self.repoGrade.dictionary), 40)

        with self.assertRaises(DisciplineError) as de:
            empty_repo = RepoDiscipline()
            empty_repo.remove_disc("11", DisciplineError, self.repoGrade)
        self.assertEqual(str(de.exception), "There are no elements that can be deleted!")


class TestGradeRepo(unittest.TestCase):
    def setUp(self) -> None:
        self.repoStud = RepoStudent()
        self.repoStud.random_objects(Student)

        self.repoDisc = RepoDiscipline()
        self.repoDisc.random_objects(Discipline)

        self.repoGrade = RepoGrade()
        self.repoGrade.random_grades(Grade, self.repoDisc.dictionary, self.repoStud.dictionary)

    def tearDown(self) -> None:
        pass

    def test_random_grades(self):
        self.assertEqual(len(self.repoGrade.dictionary), 40)

    def test_add_grade(self):
        with self.assertRaises(GradeError) as ge:
            self.repoDisc.add_stud_disc("100", "math", Discipline, DisciplineError)
            self.repoStud.add_stud_disc("99", "Mariuca", Student, StudentError)
            self.repoGrade.add_grade("100", "99", "-10", Grade, GradeError, self.repoStud.dictionary, self.repoDisc.dictionary)
        self.assertEqual(str(ge.exception), "The grade should be an integer!")

    def test_last_pos(self):
        self.repoStud.add_stud_disc("100", "mara", Student, StudentError)
        self.repoDisc.add_stud_disc("100", "csa", Discipline, DisciplineError)
        self.repoGrade.add_grade("100", "100", "10", Grade, GradeError, self.repoStud.dictionary, self.repoDisc.dictionary)
        self.assertEqual(str(self.repoGrade.last_pos()), "41")


if __name__ == "__main__":
    unittest.main()
