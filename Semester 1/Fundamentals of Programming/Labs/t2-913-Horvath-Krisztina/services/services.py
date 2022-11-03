from repository.repo import RepoTaxi
import random


class Services:
    def __init__(self):
        self.repo = RepoTaxi()

    def random_coord(self):
        x = random.randint(0, 100)
        y = random.randint(0, 100)

        if x > y:
            aux = x
            x = y
            y = aux

        return [x, y]

    def manhattan_dist(self, start, finish):
        return abs(start[0] - finish[0]) + abs(start[1] - finish[1])

    def valid_random_coord(self, coord):
        if len(self.repo.dictionary) == 0:
            return 1
        else:
            for i in self.repo.dictionary:
                if abs(coord[0] - self.repo.dictionary[i].coord[0]) + abs(coord[1] - self.repo.dictionary[i].coord[1]) > 5:
                    return 1
                else:
                    return 0

    def generate_taxi(self, nr_taxi):
        for i in range(0, nr_taxi):
            coord = self.random_coord()
            while self.valid_random_coord(coord) == 0:
                coord = self.random_coord()
            self.repo.add_taxi(i+1, 0, coord)

    def update_fare(self, idd, start, finish):
        dist = self.manhattan_dist(start, finish)
        self.repo.update_fare(idd, dist)
