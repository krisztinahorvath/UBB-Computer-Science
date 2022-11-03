"""
    Problem number 4

"""
from src.services.functionalities import Functions


class BookUI:
    def __init__(self):
        self.f = Functions()

    @staticmethod
    def print_menu():
        print("Menu:\n\t1.Add a book\n\t2.Display the list of books\n\t3.Filter the list\n\t4.Undo the last operation")

    def start(self):
        BookUI.print_menu()
        self.f.random_books()
        while True:
            option = input("\nOption: ")
            if option == "1":
                print("Please introduce a string as it follows: isbn*author*title")
                string = input("New book: ")
                try:
                    self.f.add(string)
                except ValueError as ve:
                    print(ve)
            elif option == "2":
                self.f.print_books()
            elif option == "3":
                word = input("Filter word: ")
                self.f.filter(word)
            elif option == "4":
                try:
                    self.f.undo()
                except ValueError as ve:
                    print(ve)
            elif option == "exit":
                return
            else:
                print("Invalid menu option")


run = BookUI()
run.start()
