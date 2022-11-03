class Book:
    def __init__(self, isbn, author, title):
        self.__isbn = isbn
        self.__author = author
        self.__title = title

    @classmethod  # alternative constructor for data introduced from the keyboard
    def parse_string(cls, string):
        """
        Parses a string into an isbn, author and title and returns an object of type Book
        :param string: the data of a book that has to be parsed
        :return: an object of type Book
        """
        try:
            isbn, author, title = string.split('*')
        except ValueError:
            raise ValueError("Invalid input")
        return cls(isbn, author, title)

    @property
    def isbn_name(self):
        return self.__isbn

    @property
    def author_name(self):
        return self.__author

    @property
    def title_name(self):
        return self.__title


def test_parse_string():
    book = Book.parse_string("123456*Alexandre Dumas*Black Tulip")
    assert book.isbn_name == "123456" and book.author_name == "Alexandre Dumas" and book.title_name == "Black Tulip"

    book = Book.parse_string("234567*F. Scott Fitzgerald*The Great Gatsby")
    assert book.isbn_name == "234567" and book.author_name == "F. Scott Fitzgerald" and book.title_name == "The Great Gatsby"

    try:
        book = Book.parse_string("13124*")
    except ValueError as ve:
        assert str(ve) == "Invalid input"

    try:
        book = Book.parse_string("13124*anna*")
    except ValueError as ve:
        assert str(ve) == "Invalid input"

    try:
        book = Book.parse_string("13124*anna*bella*")
    except ValueError as ve:
        assert str(ve) == "Invalid input"


test_parse_string()