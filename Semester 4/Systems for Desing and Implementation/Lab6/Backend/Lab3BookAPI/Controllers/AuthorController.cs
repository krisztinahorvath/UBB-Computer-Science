using Lab3BookAPI.Model;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Lab3BookAPI.Validations;
using Microsoft.AspNetCore.Cors;

namespace Lab3BookAPI.Controllers
{
    [Route("api/authors")]
    [ApiController]
    public class AuthorController : ControllerBase
    {
        private readonly BookContext _context;
        private readonly Validate _validate;

        public AuthorController(BookContext context, Validate validate)
        {
            _context = context;
            _validate = validate;
        }

        // GET: api/Authors
        [HttpGet]
        public async Task<ActionResult<IEnumerable<AuthorDTO>>> GetAuthor(int? pageNumber = 1, int? pageSize = 10)
        {
            var authors = _context.Authors.AsQueryable();

            if (authors == null)
            {
                return NotFound();
            }

            var totalAuthors = await authors.CountAsync();

            if (pageNumber.HasValue && pageSize.HasValue)
            {
                authors = authors.Skip((pageNumber.Value - 1) * pageSize.Value).Take(pageSize.Value);
            }

            Response.Headers.Add("X-Total-Count", totalAuthors.ToString());

            return await authors.Select(x => AuthorToDTO(x)).ToListAsync();
        }

        [HttpGet("autocomplete")]
        public async Task<ActionResult<IEnumerable<Author>>> AutocompleteName(string query, int pageNumber=1, int pageSize=100)
        {
            var names = await _context.Authors.Where(t => t.Name.Contains(query))
                .Skip((pageNumber - 1) * pageSize)
                .Take(pageSize)
                .ToListAsync();

            return Ok(names);
        }

        // GET: api/Authors/5
        [HttpGet("{id}")]
        public async Task<ActionResult<AuthorWithBookDTO>> GetAuthor(int id)
        {
            if (_context.Authors == null)
            {
                return NotFound();
            }
            var author = await _context.Authors.FirstOrDefaultAsync(x => x.Id == id);

            if (author == null)
            {
                return NotFound();
            }

            var book = await _context.BookAuthors.Where(b => b.AuthorId == id).Select(b => b.Book).ToListAsync();

            var authorDTO = new AuthorWithBookDTO
            {
                Id = id,
                Name = author.Name,
                YearOfBirth = author.YearOfBirth,
                Address = author.Address,
                Email = author.Email,
                PhoneNumber = author.PhoneNumber,
                Books = book

            };

            if (authorDTO == null)
            {
                return NotFound();
            }

            return authorDTO;
        }

        [HttpGet("get/orderedBooks")]
        public async Task<List<AuthorAvgBookLengthDTO>> GetAuthorWithAverageBookLength()
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
                           group books by authors into g
                           select new AuthorAvgBookLengthDTO
                           {
                               Id = g.Key.Id,
                               Name = g.Key.Name,
                               YearOfBirth = g.Key.YearOfBirth,
                               Address = g.Key.Address,
                               Email = g.Key.Email,
                               PhoneNumber = g.Key.PhoneNumber,
                               AvgPages = g.Average(book => book.Pages)
                           }
                     )
                     .Take(100)
                     .OrderBy(dto => dto.AvgPages).ToListAsync();

            return b;
        }

        // PUT: api/Authors/5
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPut("{id}")]
        public async Task<IActionResult> PutAuthor(int id, AuthorDTO authorDTO)
        {
            if (id != authorDTO.Id)
            {
                return BadRequest();
            }

            var author = await _context.Authors.FindAsync(id);

            if (author == null)
            {
                return NotFound();
            }

            //var book = await _context.Books.FindAsync()
            // _context.Entry(authorDTO).State = EntityState.Modified;

            if (!_validate.IsStringNonEmpty(authorDTO.Name))
            {
                return BadRequest("Entity set 'BookContext.Author.Name'  is null.");
            }

            if (!_validate.IsValidEmail(authorDTO.Email))
            {
                return BadRequest("The field 'Email' should be of the form: 'text@text.com/.ro/etc.'");
            }

            if (!_validate.IsDateValid(authorDTO.YearOfBirth))
            {
                return BadRequest("The field 'YearOfBirth' should be a positive integer between 1500 and 2023!");
            }

            author.Name = authorDTO.Name;
            author.YearOfBirth = authorDTO.YearOfBirth;
            author.Address = authorDTO.Address;
            author.Email = authorDTO.Email;
            author.PhoneNumber = authorDTO.PhoneNumber;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!AuthorExists(id))
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

        // POST: api/Authors
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost]
        public async Task<ActionResult<AuthorDTO>> PostAuthor(AuthorDTO authorDTO)
        {
            if (_context.Authors == null)
            {
                return Problem("Entity set 'BookContext.Author'  is null.");
            }

            if (!_validate.IsStringNonEmpty(authorDTO.Name))
            {
                return BadRequest("Entity set 'BookContext.Author.Name'  is null.");
            }

            if (!_validate.IsEmailUnique(_context, authorDTO.Email))
            {
                return BadRequest("The given 'Email' already exists in the database!");
            }

            if (!_validate.IsValidEmail(authorDTO.Email))
            {
                return BadRequest("The field 'Email' should be of the form: 'text@text.com'");
            }

            if (!_validate.IsDateValid(authorDTO.YearOfBirth))
            {
                return BadRequest("The field 'YearOfBirth' should be a positive integer between 1500 and 2023!");
            }

            var author = new Author
            {
                Name = authorDTO.Name,
                YearOfBirth = authorDTO.YearOfBirth,
                Address = authorDTO.Address,
                Email = authorDTO.Email,
                PhoneNumber = authorDTO.PhoneNumber,
            };

            _context.Authors.Add(author);
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetAuthor), new { id = author.Id }, AuthorToDTO(author));
        }

        // DELETE: api/Authors/5
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteAuthor(int id)
        {
            //if (_context.Author == null)
            //{
            //    return NotFound();
            //}
            var author = await _context.Authors.FindAsync(id);
            if (author == null)
            {
                return NotFound();
            }

            _context.Authors.Remove(author);
            await _context.SaveChangesAsync();

            return NoContent();
        }

        private bool AuthorExists(int id)
        {
            return (_context.Authors?.Any(e => e.Id == id)).GetValueOrDefault();
        }

        private static AuthorDTO AuthorToDTO(Author author)
        {
            return new AuthorDTO
            {
                Id = author.Id,
                Name = author.Name,
                YearOfBirth = author.YearOfBirth,
                Address = author.Address,
                Email = author.Email,
                PhoneNumber = author.PhoneNumber
            };
        }
    }
}