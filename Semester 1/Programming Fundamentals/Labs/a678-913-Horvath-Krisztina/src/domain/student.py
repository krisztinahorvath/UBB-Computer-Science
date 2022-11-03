from src.domain.entity import Entity


class Student(Entity):
    def __init__(self, ids, name):
        """
        initialize a class Student which inherits from the class Entity its properties
        :param ids: student id
        :param name: student name
        """
        super().__init__(ids, name)
