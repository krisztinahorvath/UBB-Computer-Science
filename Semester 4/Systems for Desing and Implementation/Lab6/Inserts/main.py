import random
from faker import Faker


fake = Faker()

bookIds = set()


with open(f'bookauthors.csv', 'w') as f:
    n = 10000000
    for i in range(n):
        while True:
            bookId = random.randint(1, 1000000)
            authorId = random.randint(1, 1000000)
            if (bookId, authorId) not in bookIds:
                bookIds.add((bookId, authorId))
                break

        bookRating = round(random.uniform(1, 10), 2)
        authorRating = round(random.uniform(1, 10), 2)

        f.write(f"{bookId}, {authorId}, {bookRating},{authorRating}\n")
        print(i)

    f.close()


with open('authorsWDescription.csv', 'w') as f:
    n = 1000000
    for i in range(n):
        name = fake.name()
        yearOfBirth = random.randint(1501, 2023)
        address = fake.address()
        email = fake.email()
        phoneNumber = fake.phone_number()

        description = fake.paragraph() + " " + fake.paragraph()

        f.write(f"{i+1},{name}, {yearOfBirth}, {address}, {email}, {phoneNumber}, {description}\n")
        print(i)

    f.close()


with open('booksWDescription.csv', 'w') as f:
    n = 1000000
    for i in range(n):
        title = fake.catch_phrase().replace("'", "''")
        description = fake.sentence().replace("'", "''")
        year = random.randint(1501, 2023)
        pages = random.randint(100, 1500)
        price = round(random.uniform(1, 1000), 2)
        genreId = random.randint(1, 1000000)  # (minId, maxId)
        transcript = fake.paragraph() + " " + fake.paragraph()
        f.write(f"{i + 1},{title}, {description}, {year}, {pages}, {price}, {genreId}, {transcript}\n")

        print(i)

    f.close()


with open('genres.csv', 'w') as f:
    n = 1000000
    for i in range(n):
        name = fake.word().replace("'", "''")
        description = fake.sentence().replace("'", "''")
        subgenre = fake.random_element()
        countryOfOrigin = fake.country().replace("'", "''")
        genreRating = random.randint(1, 10)

        f.write(f"{i+1},{name}, {description}, {subgenre}, {countryOfOrigin}, {genreRating}\n")

        print(i)

    f.close()
