class Entity:
    """
    class Entity holds the properties of class Student() and Discipline() which inherit from it,
    because those two classes have the same properties that's why I reunited them in one
    """
    def __init__(self, idd, name):
        """
        initialize an Entity() object
        :param idd: id
        :param name: name
        """
        self.__id = idd
        self.__name = name

    @property
    def id(self):
        return self.__id

    @property
    def name(self):
        return self.__name

    def __str__(self):
        return "id: " + str(self.id) + ", Name: " + str(self.name)
