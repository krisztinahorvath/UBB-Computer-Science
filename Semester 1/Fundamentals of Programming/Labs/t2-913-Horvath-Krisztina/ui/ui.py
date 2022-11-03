class UI:
    def __init__(self, serv):
        self.service = serv
        self.nr_taxi = 0

    def print_info(self):
        for i in self.service.repo.dictionary:
            idd = str(self.service.repo.dictionary[i].id)
            fare = str(self.service.repo.dictionary[i].total_fare)
            coord = str(self.service.repo.dictionary[i].coord)
            print(idd.ljust(10) + coord.rjust(10) + fare.rjust(10))

    def start(self):
        self.nr_taxi = int(input("Please introduce the number of taxis that you want :"))
        if self.nr_taxi == 0:
            print("You requested 0 taxis.")
            return
        else:
            self.service.generate_taxi(self.nr_taxi)
            self.print_info()

        while True:
            option = input()
            if option == "ride":
                print("starting point")
                x = int(input("x = "))
                y = int(input("y = "))
                start = [x, y]

                print("ending point")
                x = int(input("x = "))
                y = int(input("y = "))
                finish = [x, y]



