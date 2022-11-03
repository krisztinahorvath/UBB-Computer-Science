from domain.taxi import Taxi


class RepoTaxi:
    def __init__(self):
        self.dictionary = dict()

    def add_taxi(self, idd, fare, coord):
        self.dictionary[idd] = Taxi(idd, fare, coord)

    def update_fare(self, idd, sum):
        self.dictionary[idd].total_fare += sum




