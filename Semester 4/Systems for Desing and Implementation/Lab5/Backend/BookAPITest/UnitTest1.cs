using Lab3BookAPI.Model;
using Lab3BookAPI.Controllers;
using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using Moq.EntityFrameworkCore;

using System.Collections.Generic;
using System.Data.Entity;
using System.Data.Entity.Infrastructure;
using System.Linq;
using System.Reflection;
using System.Reflection.Metadata;
using System.Threading.Tasks;
using static System.Reflection.Metadata.BlobBuilder;

using NUnit;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using NUnit.Framework;
using Lab3BookAPI.Validations;


namespace BookTests
{
    [TestFixture]
    public class BookControllerTests
    {
        private Mock<BookContext> _contextMock;
        private Mock<Validate> _validateMock;

        [SetUp]
        public void Setup()
        {
            // create a mock of the BookContext
            _contextMock = new Mock<BookContext>();
            _validateMock = new Mock<Validate>();
        }

        [Test]
        public async Task GetBookWithAverageAuthorAge_ReturnsExpectedResult()
        {
            // arrange
            var authors = new List<Author>
            {
                new Author
                {
                    Id = 1,
                    Name = "John",
                    YearOfBirth = 1970
                },
                new Author
                {
                    Id = 2,
                    Name = "Jane",
                    YearOfBirth = 1980
                },
                new Author
                {
                    Id = 3,
                    Name = "Anna",
                    YearOfBirth = 1983
                }
            };

            var books = new List<Book>
            {
                new Book
                {
                    Id = 1,
                    Title = "Book1",
                    Description = "Description1",
                    Year = 2020,
                    Pages = 100,
                    Price = 10,
                    GenreId = 1
                },
                new Book
                {
                    Id = 2,
                    Title = "Book2",
                    Description = "Description2",
                    Year = 2021,
                    Pages = 200,
                    Price = 20,
                    GenreId = 1
                }
            };

            var bookAuthors = new List<BookAuthor>
            {
                new BookAuthor
                {
                    BookId = 1,
                    AuthorId = 1
                },
                new BookAuthor
                {
                    BookId = 2,
                    AuthorId = 2
                },
                new BookAuthor { 
                    BookId = 2, 
                    AuthorId = 3
                }
            };

            _contextMock.Setup(c => c.Authors).ReturnsDbSet(authors);
            _contextMock.Setup(c => c.Books).ReturnsDbSet(books);
            _contextMock.Setup(c => c.BookAuthors).ReturnsDbSet(bookAuthors);

            var controller = new BookItemsController(_contextMock.Object, _validateMock.Object);

            // act
            var result = await controller.GetBookWithAverageAuthorAge();

            // assert
            NUnit.Framework.Assert.AreEqual(2, result.Count);
            NUnit.Framework.Assert.AreEqual(2, result[0].Id);
            NUnit.Framework.Assert.AreEqual(1, result[1].Id);
            NUnit.Framework.Assert.AreEqual("Book2", result[0].Title);
            NUnit.Framework.Assert.AreEqual("Book1", result[1].Title);
            NUnit.Framework.Assert.AreEqual(41.5d, result[0].AverageAuthorAge);
            NUnit.Framework.Assert.AreEqual(53.0d, result[1].AverageAuthorAge);
        }

        [Test]
        public async Task GetOrderedBooks_ReturnsExpectedResult() {
            // arrange
            var authors = new List<Author>
            {
                new Author
                {
                    Id = 1,
                    Name = "Author1",
                    YearOfBirth = 1970
                },
                new Author
                {
                    Id = 2,
                    Name = "Author2",
                    YearOfBirth = 1980
                },
                new Author
                {
                    Id = 3,
                    Name = "Author3",
                    YearOfBirth = 1983
                }
            };

            var books = new List<Book>
            {
                new Book
                {
                    Id = 1,
                    Title = "Book1",
                    Description = "Description1",
                    Year = 2020,
                    Pages = 100,
                    Price = 10,
                    GenreId = 1
                },
                new Book
                {
                    Id = 2,
                    Title = "Book2",
                    Description = "Description2",
                    Year = 2021,
                    Pages = 200,
                    Price = 20,
                    GenreId = 1
                },
                new Book
                {
                    Id = 3,
                    Title = "Book3",
                    Description = "Description2",
                    Year = 2021,
                    Pages = 255,
                    Price = 20,
                    GenreId = 1
                }
            };

            var bookAuthors = new List<BookAuthor>
            {
                new BookAuthor
                {
                    BookId = 1,
                    AuthorId = 1
                },
                new BookAuthor
                {
                    BookId = 2,
                    AuthorId = 2
                },
                new BookAuthor 
                {
                    BookId = 2,
                    AuthorId = 3
                },
                new BookAuthor 
                {
                    BookId = 3,
                    AuthorId = 3
                }
            };

            _contextMock.Setup(c => c.Authors).ReturnsDbSet(authors);
            _contextMock.Setup(c => c.Books).ReturnsDbSet(books);
            _contextMock.Setup(c => c.BookAuthors).ReturnsDbSet(bookAuthors);

            var controller = new AuthorController(_contextMock.Object, _validateMock.Object);

            // act
            var result = await controller.GetAuthorWithAverageBookLength();

            // assert
            NUnit.Framework.Assert.AreEqual(3, result.Count);
            NUnit.Framework.Assert.AreEqual(1, result[0].Id);
            NUnit.Framework.Assert.AreEqual(2, result[1].Id);
            NUnit.Framework.Assert.AreEqual(3, result[2].Id);
            NUnit.Framework.Assert.AreEqual("Author1", result[0].Name);
            NUnit.Framework.Assert.AreEqual("Author2", result[1].Name);
            NUnit.Framework.Assert.AreEqual("Author3", result[2].Name);
            NUnit.Framework.Assert.AreEqual(100.0d, result[0].AvgPages);
            NUnit.Framework.Assert.AreEqual(200.0d, result[1].AvgPages);
            NUnit.Framework.Assert.AreEqual(227.5d, result[2].AvgPages);
        }

    }
}
