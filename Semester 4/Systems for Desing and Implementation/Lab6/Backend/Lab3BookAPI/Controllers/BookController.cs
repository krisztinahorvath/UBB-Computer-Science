using Lab3BookAPI.Model;
using Microsoft.AspNetCore.Http.HttpResults;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.VisualBasic;
using Lab3BookAPI.Validations;

namespace Lab3BookAPI.Controllers
{
    [Route("api/books")]
    [ApiController]
    public class BookItemsController : ControllerBase
    {
        private readonly BookContext _context;
        private readonly Validate _validate;

        public BookItemsController(BookContext context, Validate validate)
        {
            _context = context;
            _validate = validate;
        }

        // GET: api/BookItems
        [HttpGet]
        public async Task<ActionResult<IEnumerable<BookDTO>>> GetBookItems()
        {
            if (_context.Books == null)
            {
                return NotFound();
            }

            return await _context.Books.Select(x => BookToDTO(x)).ToListAsync();
        }

        [HttpGet("bookAuthor")]
        public async Task<ActionResult<IEnumerable<BookAuthorDTO>>> GetBookAuthor()
        {
            if (_context.BookAuthors == null)
            {
                return NotFound();
            }

            return await _context.BookAuthors.Select(x => BookAuthorToDTO(x)).ToListAsync();
        }

        // GET: api/BookItems/5
        [HttpGet("{id}")]
        public async Task<ActionResult<BookWithAuthorDTO>> GetBookItem(int id)
        {
            if (_context.Books == null)
            {
                return NotFound();
            }

            var book = await _context.Books.Include(g => g.Genre).FirstOrDefaultAsync(x => x.Id == id);

            if (book == null)
            {
                return NotFound();
            }

            //var genre = await _context.Genres.Where(b => b.GenreId  == id);

            var author = await _context.BookAuthors.Where(b => b.BookId == id).Select(b => b.Author).ToListAsync();
           
            var bookDTO = new BookWithAuthorDTO
            {
                Books = book,
                Authors = author

            };

            return bookDTO;
        }

        [HttpGet("filter/{year}")]
        public async Task<IActionResult> FilterByYear(int year)
        {
            if (_context.Books == null)
            {
                return NotFound();
            }
            var book = await _context.Books.Where(books => books.Year > year).ToListAsync();
            return Ok(book);
        }

        [HttpGet("get/orderedAuthors")]
        public async Task<List<BookWithAverageAuthorAgeDTO>> GetBookWithAverageAuthorAge()
        {
            //if (_context.Books == null)
            //{
            //    return NotFound();
            //}

            //if (_context.Authors == null)
            //{
            //    return NotFound();
            //}

            var b = await (from bookAuthors in _context.BookAuthors
                     join books in _context.Books on bookAuthors.BookId equals books.Id
                     join authors in _context.Authors on bookAuthors.AuthorId equals authors.Id
                     group authors by books into g
                     select new BookWithAverageAuthorAgeDTO
                     {
                         Id = g.Key.Id,
                         Title = g.Key.Title,
                         Description = g.Key.Description,
                         Year = g.Key.Year,
                         Pages = g.Key.Pages,
                         Price = g.Key.Price,
                         Transcript = g.Key.Transcript,
                         AverageAuthorAge = g.Average(author => DateTime.Now.Year - author.YearOfBirth)
                     }
                     ).OrderBy(dto => dto.AverageAuthorAge).ToListAsync();

            return b;
        }

        
        
    

        // PUT: api/BookItems/5
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPut("{id}")]
        public async Task<IActionResult> PutBookItem(int id, BookDTO bookDTO)
        {
            if (id != bookDTO.Id)
            {
                return BadRequest();
            }

            var book = await _context.Books.FindAsync(id);

            if (book == null)
            {
                return NotFound();
            }

            var genre = await _context.Genres.FindAsync(bookDTO.GenreId);

            if (genre == null)
            {
                return BadRequest();
            }

            if (!_validate.IsDateValid(bookDTO.Year))
            {
                return BadRequest("The 'Year' field should be a positive integer!");
            }

            if (!_validate.IsPositive(bookDTO.GenreId)) 
            {
                return BadRequest("The 'GenreId' field should be a positive integer!");
            }

            if (!_validate.IsStringNonEmpty(bookDTO.Title))
            {
                return BadRequest("The 'Title' field should be non-empty!");
            }

            book.Title = bookDTO.Title;
            book.Description = bookDTO.Description;
            book.Year = bookDTO.Year;
            book.Pages = bookDTO.Pages;
            book.Price = bookDTO.Price;
            book.Transcript = bookDTO.Transcript;

            book.GenreId = bookDTO.GenreId;
            book.Genre = genre;

            // _context.Entry(bookDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!BookItemExists(id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return NoContent();
        }

        [HttpPost("{id}/authors")]
        public async Task<ActionResult<BookAuthorDTO>> PostBookWithAuthor(int id, BookAuthorDTO bookAuthorDTO)   
        {
            if (_context.Books == null)
            {
                return Problem("Entity set 'BookContext.BookItems'  is null.");
            }

            var author = await _context.Authors.FindAsync(bookAuthorDTO.AuthorId);

           
            if (author == null)
            {
                return BadRequest();
            }

            var book = await _context.Books.FindAsync(id);

            if(book == null)
            {
                return BadRequest();
            }


            var newBookAuthor = new BookAuthor
            {
                BookId = id,
                Book = book,

                AuthorId = bookAuthorDTO.AuthorId,
                Author = author,

                BookRating = bookAuthorDTO.BookRating,
                AuthorRating = bookAuthorDTO.AuthorRating
            };

            try
            {
                _context.BookAuthors.Add(newBookAuthor);
                await _context.SaveChangesAsync();
            }
            catch
            {
                return BadRequest();
            }

            // return CreatedAtAction("GetBookItem", new { id = bookItem.Id }, bookItem);

            return CreatedAtAction(nameof(GetBookAuthor), BookAuthorToDTO(newBookAuthor));
        }

        [HttpPost("{id}/authorsList")]
        public async Task<ActionResult<BookAuthorDTO>> PostBookWithListOfAuthor(int id, BookAuthorListDTO bookAuthorDTO)
        {
            if (_context.Books == null)
            {
                return Problem("Entity set 'BookContext.BookItems'  is null.");
            }

            var book = await _context.Books.FindAsync(id);

            if (book == null)
            {
                return BadRequest();
            }

            foreach(var authId in bookAuthorDTO.AuthorId)
            {
                var author = await _context.Authors.FindAsync(authId);


                if (author == null)
                {
                    return BadRequest();
                }

                var newBookAuthor = new BookAuthor
                {
                    BookId = id,
                    Book = book,

                    AuthorId = authId,
                    Author = author,

                    BookRating = bookAuthorDTO.BookRating,
                    AuthorRating = bookAuthorDTO.AuthorRating
                };

                try
                {
                    _context.BookAuthors.Add(newBookAuthor);
                    await _context.SaveChangesAsync();
                }
                catch
                {
                    return BadRequest();
                }

            }
             
            return NoContent();
        }

        // POST: api/BookItems
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost]
        public async Task<ActionResult<BookDTO>> PostBookItem(BookDTO bookDTO)
        {
            if (_context.Books == null)
            {
                return Problem("Entity set 'BookContext.BookItems'  is null.");
            }

            var genre = await _context.Genres.FindAsync(bookDTO.GenreId);

            if (genre == null)
            {
                return BadRequest();
            }

            if (!_validate.IsDateValid(bookDTO.Year))
            {
                return BadRequest("The 'Year' field should be a positive integer between 1500 and 2023!");
            }

            if (!_validate.IsPositive(bookDTO.GenreId))
            {
                return BadRequest("The 'GenreId' field should be a positive integer!");
            }

            if (!_validate.IsStringNonEmpty(bookDTO.Title))
            {
                return BadRequest("The 'Title' field should be non-empty!");
            }

            var book = new Book
            {
                Title = bookDTO.Title,
                Description = bookDTO.Description,
                Year = bookDTO.Year,
                Pages = bookDTO.Pages,
                Price = bookDTO.Price,
                Transcript = bookDTO.Transcript,

                GenreId = bookDTO.GenreId,
                Genre = genre
           };

            _context.Books.Add(book);
            await _context.SaveChangesAsync();

            // return CreatedAtAction("GetBookItem", new { id = bookItem.Id }, bookItem);

            return CreatedAtAction(nameof(GetBookItem), new { id = book.Id }, BookToDTO(book));
        }

        // DELETE: api/BookItems/5
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteBookItem(int id)
        {
            if (_context.Books == null)
            {
                return NotFound();
            }
            var bookItem = await _context.Books.FindAsync(id);
            if (bookItem == null)
            {
                return NotFound();
            }

            _context.Books.Remove(bookItem);
            await _context.SaveChangesAsync();

            return NoContent();
        }

        private bool BookItemExists(int id)
        {
            return (_context.Books?.Any(e => e.Id == id)).GetValueOrDefault();
        }

        private static BookDTO BookToDTO(Book book)
        {
            return new BookDTO
            {
                Id = book.Id,
                Title = book.Title,
                Description = book.Description,
                Year = book.Year,
                Pages = book.Pages,
                Price = book.Price,
                GenreId = book.GenreId,
                Transcript = book.Transcript
            };
        }

        private static BookAuthorDTO BookAuthorToDTO(BookAuthor bookAuthor) 
        {
            return new BookAuthorDTO
            {
                BookId = bookAuthor.BookId,
                AuthorId = bookAuthor.AuthorId,
                BookRating = bookAuthor.BookRating,
                AuthorRating = bookAuthor.AuthorRating,

            };
        }
    }
}
