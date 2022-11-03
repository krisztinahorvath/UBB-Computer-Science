class Taxi:
    def __init__(self, idd, fare, coords):
        self.__idd = idd
        self.__total_fare = fare
        self.__coord = coords

    @property
    def id(self):
        return self.__idd

    @property
    def total_fare(self):
        return self.__total_fare

    @property
    def coord(self):
        return self.__coord
