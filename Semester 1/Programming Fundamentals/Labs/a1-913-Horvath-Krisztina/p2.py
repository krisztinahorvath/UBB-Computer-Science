# Solve the problem from the second set here

# 6.Determine a calendar date (as year, month, day)
# starting from two integer numbers representing the year and the day number inside that year
# (e.g. day number 32 is February 1st). Take into account leap years.
# Do not use Python's inbuilt date/time functions.

def dayCalculator(day, lenDay):
    """
    This function calculates
    :param day: the given day number
    :param lenDay: the list containing the length of each month
    :return: day of the month, month eg.: 22, 1 -> 22, february
    """
    sumMonth = int(lenDay[0])
    # sumMonth = the sum of all the days of the year, added one by one in the for loop, to find the month where the
    # given day number is
    if day < sumMonth:  # displays separately for days in january, because the found formula doesn't include this case
        return day, 0
    for i in range(1, 12):
        sumMonth += int(lenDay[i])  # we add the number of days of the month with de i index
        if day <= sumMonth:
            return lenDay[i] - sumMonth + day, i  # we calculate and return the exact day number of the month
            #  formula explained: - from the length of the current month we subtract the sum of all the months until
            #  that point(including the current month) and then we add the given day number


def read():     # reads the values for year and day
    year = int(input("Please write a year = "))
    day = int(input("Please write the number of a day = "))
    if day > 366 or day <= 0 or year <= 0 :
        return 0, 0
    return year, day


def init():  # initializes the list with the needed date to solve the problem
    lenDay = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]  # the length of every month(the number of days in them)
    monthName = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October",
                 "November", "December"]  # the names of the months
    return lenDay, monthName


def verifyIfLeapYear(year, lenDay):  # we find out if the year is a leap year and modify the
    # number of days in february if needed
        if year % 100 == 0 and year % 400 == 0 or year % 4 == 0:
            lenDay[1] += 1

def solve():
    year, day = read()
    if year == 0:
        print("Invalid input, please introduce natural numbers!")
    else:
        lenDay, monthName = init()
        verifyIfLeapYear(year, lenDay)
        d, m = dayCalculator(day, lenDay)  # d = day of the month, m = month number
        print("\nThe given calendar date is: " + str(monthName[m]) + " " + str(d) + ". " + str(year))


solve()