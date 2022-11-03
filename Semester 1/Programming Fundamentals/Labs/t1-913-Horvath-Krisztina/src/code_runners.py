"""
Implement the solution here. 
You may add other source files.
Make sure you commit & push the source code before the end of the test.

Solutions using user-defined classes will not be graded.
"""


from functions import random_secret_number, valid_number, correctness
from time import sleep


def run():
    number = random_secret_number()
    timer = 60
    while True and timer != 0:
        sleep(1)
        timer -= 1
        human = input("Please introduce your guess: ")
        if valid_number(human) is False:
            print("Game over(invalid input), computer wins, the number was:" + str(number))
            return
        elif int(human) == 8086:
            print("The secret number is: " + str(number))
            return
        elif int(human) == int(number):
            print("Congrats, you won!")
        else:
            codes, runners = correctness(human, number)
            print("computer reports " + str(codes) + " codes and " + str(runners) + " runners")
    if timer == 0:
        print("Time is up, can't play anymore")


run()