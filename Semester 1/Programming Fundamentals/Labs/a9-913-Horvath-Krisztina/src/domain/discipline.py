from src.domain.entity import Entity


class Discipline(Entity):
    def __init__(self, idd, name):
        """
        initialize a class Discipline which inherits from the class Entity its properties
        :param idd: discipline id
        :param name: discipline name
        """
        super().__init__(idd, name)
