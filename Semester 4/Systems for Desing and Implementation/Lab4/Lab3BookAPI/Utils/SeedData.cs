using Lab3BookAPI.Model;
using Microsoft.EntityFrameworkCore;
using Microsoft.VisualStudio.Web.CodeGenerators.Mvc.Controller;

namespace Lab3BookAPI.Utils
{
    public class SeedData
    {
        public static void Initialize(IServiceProvider serviceProvider)
        {
            using (var context = new BookContext(serviceProvider.GetRequiredService<DbContextOptions<BookContext>>()))
            {  
                SeedGenres(context);
                SeedBooks(context);
                SeedAuthors(context);
                SeedBookAuthors(context);
            }
        }

        public static void SeedGenres(BookContext context)
        {
            if (context.Genres.Any())
                return;

            context.Genres.AddRange(
                new Genre
                {
                    Name = "Fantasy",
                    Description = "A genre that uses magic and other supernatural forms as a primary element of plot, theme, and/or setting.",
                    Subgenre = "Epic Fantasy",
                    CountryOfOrigin = "England",
                    GenreRating = 4
                },
                 new Genre
                 {
                     Name = "Mystery",
                     Description = "A genre that revolves around the investigation of a crime or series of crimes.",
                     Subgenre = "Cozy Mystery",
                     CountryOfOrigin = "USA",
                     GenreRating = 4
                 }, 
                 new Genre
                 {
                     Name = "Romance",
                     Description = "A genre that focuses on the romantic relationships between characters.",
                     Subgenre = "Historical Romance",
                     CountryOfOrigin = "England",
                     GenreRating = 3
                 }, 
                 new Genre
                 {
                     Name = "Science Fiction",
                     Description = "A genre that deals with imaginative and futuristic concepts such as advanced science and technology, space exploration, time travel, parallel universes, and extraterrestrial life.",
                     Subgenre = "Cyberpunk",
                     CountryOfOrigin = "USA",
                     GenreRating = 4
                 }, 
                 new Genre
                 {
                     Name = "Thriller",
                     Description = "A genre that uses suspense, tension, and excitement as the main elements to keep the audience engaged.",
                     Subgenre = "Psychological Thriller",
                     CountryOfOrigin = "USA",
                     GenreRating = 4
                 }, 
                 new Genre
                 {
                     Name = "Horror",
                     Description = "Horror is a genre of storytelling intended to scare, shock, and thrill its audience",
                     Subgenre = "Psychological",
                     CountryOfOrigin = "USA",
                     GenreRating = 4
                 },
                 new Genre
                 {
                     Name = "Dystopian",
                     Description = "Authors writing dystopias imagine a grim society, often in the aftermath of a disaster",
                     Subgenre = "Science Fiction",
                     CountryOfOrigin = "UK",
                     GenreRating = 4
                 },
                 new Genre
                 {
                     Name = "Action & Adventure",
                     Description = "Fast paste novels, loved by many",
                     Subgenre = "Fantasy",
                     CountryOfOrigin = "Germany",
                     GenreRating = 4
                 },
                  new Genre
                  {
                      Name = "Historical Fiction",
                      Description = "This book genre encompasses fictional stories in a historical setting, carefully balancing creativity and facts. ",
                      Subgenre = "Romance",
                      CountryOfOrigin = "France",
                      GenreRating = 5
                  },
                   new Genre
                   {
                       Name = "Contemporary Fiction",
                       Description = "This book genre is occasionally lumped in with others to indicate that the book takes place in the present day. ",
                       Subgenre = "Modern",
                       CountryOfOrigin = "USA",
                       GenreRating = 5
                   }
                );

            context.SaveChanges();
        }

        private static void SeedBooks(BookContext context)
        {
            if (context.Books.Any())
                return;

            var genre = context.Genres.First() ?? throw new Exception("No genres found!");
            int genreId = genre.Id;

            context.Books.AddRange(
                new Book
                {
                    Title = "It",
                    Description = "It’s a small city, a place as hauntingly familiar as your own hometown. Only in Derry the haunting is real ..",
                    Year = 1986,
                    Pages = 1116,
                    Price = 35, 
                    Genre = genre,
                    GenreId = genreId,
                },
                new Book
                {
                    Title = "Christine",
                    Description = "She loves thrills, night trips and the rock n' roll of the heroic years...",
                    Year = 1983,
                    Pages = 411,
                    Price = 40,
                    Genre = genre,
                    GenreId = genreId,
                },
                new Book
                {
                    Title = "Mr. Mercedes",
                    Description = "In the predawn hours, in a distressed American city, hundreds of unemployed men and women line up for the opening of a job fair.",
                    Year = 2014,
                    Pages = 437,
                    Price = 50,
                    Genre = genre,
                    GenreId = genreId,
                },
                new Book
                {
                    Title = "The Alchemist",
                    Description = "Combining magic, mysticism, wisdom, and wonder into an inspiring tale of self-discovery, The Alchemist has become a modern classic, selling millions of copies around the world and transforming the lives of countless readers across generations.",
                    Year = 1988,
                    Pages = 182,
                    Price = 25,
                    Genre = genre,
                    GenreId = genreId,
                },
                new Book
                {
                    Title = "Harry Potter and the Philosopher’s Stone",
                    Description = "Harry Potter thinks he is an ordinary boy - until he is rescued by an owl, taken to Hogwarts School of Witchcraft and Wizardry, learns to play Quidditch and does battle in a deadly duel.",
                    Year = 1997,
                    Pages = 223,
                    Price = 30,
                    Genre = genre,
                    GenreId = genreId,
                },
                new Book
                {
                    Title = "Harry Potter and the Chamber of Secrets",
                    Description = "Ever since Harry Potter had come home for the summer, the Dursleys had been so mean and hideous that all Harry wanted was to get back to the Hogwarts School for Witchcraft and Wizardry",
                    Year = 1998,
                    Pages = 341,
                    Price = 30,
                    Genre = genre,
                    GenreId = genreId,
                },
                new Book
                {
                    Title = "Harry Potter and the Prisoner of Azkaban",
                    Description = "Harry Potter, along with his best friends, Ron and Hermione, is about to start his third year at Hogwarts School of Witchcraft and Wizardry. Harry can't wait to get back to school after the summer holidays.",
                    Year = 1999,
                    Pages = 1116,
                    Price = 435,
                    Genre = genre,
                    GenreId = genreId,
                },
                new Book
                {
                    Title = "Harry Potter and the Goblet of Fire",
                    Description = "It is the summer holidays and soon Harry Potter will be starting his fourth year at Hogwarts School of Witchcraft and Wizardry.",
                    Year = 2000,
                    Pages = 734,
                    Price = 30,
                    Genre = genre,
                    GenreId = genreId,
                },
                new Book
                {
                    Title = "A time to kill",
                    Description = "Before 'The Firm' and 'The Pelican Brief' made him a superstar, John Grisham wrote this riveting story of retribution and justice..",
                    Year = 1989,
                    Pages = 738,
                    Price = 25,
                    Genre = genre,
                    GenreId = genreId,
                },
                new Book
                {
                    Title = "The Fault in Our Stars",
                    Description = "Despite the tumor-shrinking medical miracle that has bought her a few years, Hazel has never been anything but terminal, her final chapter inscribed upon diagnosis. ",
                    Year = 2012,
                    Pages = 313,
                    Price = 27,
                    Genre = genre,
                    GenreId = genreId,
                },
                new Book
                {
                    Title = "The Da Vinci Code",
                    Description = "Despite the tumor-shrinking medical miracle that has bought her a few years, Hazel has never been anything but terminal, her final chapter inscribed upon diagnosis. ",
                    Year = 2003,
                    Pages = 489,
                    Price = 27,
                    Genre = genre,
                    GenreId = genreId,
                }
                );


            context.SaveChanges();
        }

        public static void SeedAuthors(BookContext context)
        {
            if (context.Authors.Any())
                return;

            context.Authors.AddRange(
                new Author
                {
                    Name = "Stephen King",
                    YearOfBirth = 1947,
                    Address = "California, Los Angeles, Hollywood Boulevard 4943",
                    Email = "stephenking@gmail.com",
                    PhoneNumber = "0745273634",
                },
                new Author
                {
                    Name = "J. K. Rowling",
                    YearOfBirth = 1965,
                    Address = "UK, Liverpool, Main Road, 34",
                    Email = "jkrowling@gmail.com",
                    PhoneNumber = "0745345245",
                },
                new Author
                {
                    Name = "Paulo Coelho",
                    YearOfBirth = 1947,
                    Address = "Brazil, Sao Paulo, Vespa Road, 67 ",
                    Email = "paulocoelho@gmail.com",
                    PhoneNumber = "0745232444",
                },
                new Author
                {
                    Name = "John Grisham",
                    YearOfBirth = 1955,
                    Address = "USA, Mississippi, 3rd Street, 88 ",
                    Email = "johngrisham@gmail.com",
                    PhoneNumber = "0743224744",
                },
                new Author
                {
                    Name = "John Green",
                    YearOfBirth = 1977,
                    Address = "USA, New York, 99th Street, 5690 ",
                    Email = "johngreen@gmail.com",
                    PhoneNumber = "0755000113",
                },
                new Author
                {
                    Name = "Dan Brown",
                    YearOfBirth = 1964,
                    Address = "USA, New York, 99th Street, 5690 ",
                    Email = "danbrown@gmail.com",
                    PhoneNumber = "0755023413",
                },
                new Author
                {
                    Name = "Ken Follett",
                    YearOfBirth = 1949,
                    Address = "UK, London, That Street, 39 ",
                    Email = "kenfollett@gmail.com",
                    PhoneNumber = "0755023419",
                },
                new Author
                {
                    Name = "Markus Zusak",
                    YearOfBirth = 1975,
                    Address = "Australia, Melbourne, Left Street, 39 ",
                    Email = "marcuszusak@gmail.com",
                    PhoneNumber = "0745632789",
                },
                new Author
                {
                    Name = "Carlos Ruiz Zafon",
                    YearOfBirth = 1964,
                    Address = "Spain, Madrid, Left Street, 39 ",
                    Email = "carloszafon@gmail.com",
                    PhoneNumber = "0755023555",
                },
                new Author
                {
                    Name = "Tom Robbins",
                    YearOfBirth = 1932,
                    Address = "USA, New York, 78th Street, 39 ",
                    Email = "tomrobbins@gmail.com",
                    PhoneNumber = "0788023413",
                }
                );
            context.SaveChanges();
        }

        public static void SeedBookAuthors(BookContext context)
        {
            if(context.BookAuthors.Any())
                return;

            var jkrowling = context.Authors.Select(a => a).Where(a => a.Name == "J. K. Rowling").ToList() ?? throw new Exception("Author not found");

            var bjkrowling1 = context.Books.Select(b => b).Where(b => b.Title == "Harry Potter and the Philosopher’s Stone").ToList() ?? throw new Exception("Book not found");
            var bjkrowling2 = context.Books.Select(b => b).Where(b => b.Title == "Harry Potter and the Chamber of Secrets").ToList() ?? throw new Exception("Book not found");
            var bjkrowling3 = context.Books.Select(b => b).Where(b => b.Title == "Harry Potter and the Prisoner of Azkaban").ToList() ?? throw new Exception("Book not found");
            var bjkrowling4 = context.Books.Select(b => b).Where(b => b.Title == "Harry Potter and the Goblet of Fire").ToList() ?? throw new Exception("Book not found");


            var stephenking = context.Authors.Select(a => a).Where(a => a.Name == "Stephen King").ToList() ?? throw new Exception("Author not found");

            var bsking1 = context.Books.Select(b => b).Where(b => b.Title == "It").ToList() ?? throw new Exception("Book not found");
            var bsking2 = context.Books.Select(b => b).Where(b => b.Title == "Christine").ToList() ?? throw new Exception("Book not found");
            var bsking3 = context.Books.Select(b => b).Where(b => b.Title == "Mr. Mercedes").ToList() ?? throw new Exception("Book not found");

            context.BookAuthors.AddRange(
                new BookAuthor
                {
                    BookId = bjkrowling1[0].Id,
                    Book = bjkrowling1[0],

                    AuthorId = jkrowling[0].Id,
                    Author = jkrowling[0],

                    BookRating = 5,
                    AuthorRating = 4
                },
                new BookAuthor
                {
                    BookId = bjkrowling2[0].Id,
                    Book = bjkrowling2[0],

                    AuthorId = jkrowling[0].Id,
                    Author = jkrowling[0],

                    BookRating = 5,
                    AuthorRating = 4
                }, 
                new BookAuthor
                {
                    BookId = bjkrowling3[0].Id,
                    Book = bjkrowling3[0],

                    AuthorId = jkrowling[0].Id,
                    Author = jkrowling[0],

                    BookRating = 5,
                    AuthorRating = 4
                },
                new BookAuthor
                {
                    BookId = bjkrowling4[0].Id,
                    Book = bjkrowling4[0],

                    AuthorId = jkrowling[0].Id,
                    Author = jkrowling[0],

                    BookRating = 5,
                    AuthorRating = 4
                }, 
                new BookAuthor
                {
                    BookId = bsking1[0].Id, 
                    Book = bsking1[0],

                    AuthorId = stephenking[0].Id,
                    Author = stephenking[0],

                    BookRating = 5,
                    AuthorRating = 4
                },
                new BookAuthor
                {
                    BookId = bsking2[0].Id,
                    Book = bsking2[0],

                    AuthorId = stephenking[0].Id,
                    Author = stephenking[0],

                    BookRating = 5,
                    AuthorRating = 4
                },
                new BookAuthor
                {
                    BookId = bsking3[0].Id,
                    Book = bsking3[0],

                    AuthorId = stephenking[0].Id,
                    Author = stephenking[0],

                    BookRating = 5,
                    AuthorRating = 4
                }

                );

            context.SaveChanges();
        }
    }
}
