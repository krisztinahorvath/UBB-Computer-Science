from src.domain.books import Book
from random import shuffle
from copy import deepcopy
import pytest


class Functions:
    def __init__(self):
        self.dictionary = dict()
        self.undo_list = list()
        self.book_list = ["123456*Alexandre Dumas*Black Tulip", "234567*F. Scott Fitzgerald*The Great Gatsby",
                          "345678*Stephen King*IT", "456789*Suzanne Collins*The hunger games",
                          "567899*Jane Austen*Pride and Prejudice", "765424*Margaret Mitchell*Gone with the wind",
                          "633525*Anne Frank*The diary of a young girl", "324444*Jane Austen*Emma",
                          "235647*Margaret Atwood*The handmaid's tale", "746344*Veronica Roth*Divergent",
                          "443244*Daphne du Maurier*Rebecca", "745565*George Orwell*1984",
                          "345766*J. K. Rowling*Harry Potter", "344879*J. R. R. Tolkien*The Hobbit",
                          "967866*George R. R. Martin*A game of thrones", "567889*Suzanne Collins*Mockingjay",
                          "345654*Dan Brown*Origin", "656343*Dan Brown*Angels and Demons",
                          "345789*Rick Riordan*The lost hero", "764544*Charles Dickens*A tale of two cities",
                          "786745*Fyodor Dostoevsky*Crime and Punishment",
                          "753546*Agatha Christie*Murder on the Orient Express"]

    def random_books(self):  # initialize the list with 10 random books
        while len(self.dictionary) < 10:
            shuffle(self.book_list)
            entity = Book.parse_string(self.book_list[0])
            if entity.isbn_name not in self.dictionary:
                self.dictionary[entity.isbn_name] = entity
        self.undo_list = [deepcopy(self.dictionary)]

    def print_books(self):
        for i in self.dictionary:
            print(self.dictionary[i].isbn_name + "  " + self.dictionary[i].author_name + "  " + self.dictionary[i].title_name)

    def add(self, string):
        """
        Adds an instance of the class Book to dictionary
        :param string: the given book(a string)
        """
        entity = Book.parse_string(string)
        if entity.isbn_name in self.dictionary:
            raise ValueError("Cannot add book with the same isbn twice")
        else:
            self.dictionary[entity.isbn_name] = entity
            self.undo_list.append(deepcopy(self.dictionary))

    def filter(self, word):
        """
        Deletes all books from dictionary that start with the given word
        :param word: the word that is used to filter the dictionary with the books
        """
        change = 0
        dict_index = []  # list with the indexes that have to be deleted
        word += " "  # to make sure that it is an actual word and not a group of letters in a word in the title
        for i in self.dictionary:
            word_find = self.dictionary[i].title_name.find(word)
            if word_find == 0:
                dict_index.append(i)
                change = 1
        if change == 1:
            for i in dict_index:
                self.dictionary.pop(i)
            self.undo_list.append(deepcopy(self.dictionary))

    def undo(self):
        """
        Reverses the last operation made on the dictionary of books
        """
        if len(self.undo_list) == 1:
            raise ValueError("There were no operations made that can be undone")
        else:
            self.undo_list.pop(-1)
            self.dictionary = deepcopy(self.undo_list[-1])

