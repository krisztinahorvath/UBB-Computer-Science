using Lab3BookAPI.Model;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace Lab3BookAPI.Controllers
{
    [Route("api/genres")]
    [ApiController]
    public class GenreController : ControllerBase
    {
        private readonly BookContext _context;

        public GenreController(BookContext context)
        {
            _context = context;
        }

        // GET: api/genre
        [HttpGet]
        public async Task<ActionResult<IEnumerable<GenreDTO>>> GetGenres()
        {
            if (_context.Genres == null)
            {
                return NotFound();
            }

            return await _context.Genres.Select(x => GenreToDTO(x)).ToListAsync();

        }

        // GET: api/genre/5
        [HttpGet("{id}")]
        public async Task<ActionResult<Genre>> GetGenre(int id)
        {
            if (_context.Genres == null)
            {
                return NotFound();
            }
            //var genre = await _context.Genres.FindAsync(id);

            var genre = await _context.Genres.Include(b => b.BookList).FirstOrDefaultAsync(b => b.Id == id);

            if (genre == null)
            {
                return NotFound();
            }

            return genre;
        }

        // PUT: api/genre/5
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPut("{id}")]
        public async Task<IActionResult> PutGenre(int id, GenreDTO genreDTO)
        {
            if (id != genreDTO.Id)
            {
                return BadRequest();
            }

            var genre = await _context.Genres.FindAsync(id);

            if (genre == null)
            {
                return NotFound();
            }

            genre.Name = genreDTO.Name;
            genre.Description = genreDTO.Description;
            genre.Subgenre = genreDTO.Subgenre;
            genre.CountryOfOrigin = genreDTO.CountryOfOrigin;
            genre.GenreRating = genreDTO.GenreRating;

            // _context.Entry(genreDTO).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!GenreExists(id))
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


        [HttpPost("{id}/bookList")]
        public async Task<ActionResult<Genre>> PostGenreWithListOfBooks(int id, List<BookDTO> books)
        {
            if (_context.Genres == null)
            {
                return Problem("Entity set 'BookContext.Genres'  is null.");
            }

            var genre = await _context.Genres.FindAsync(id);

            if (genre == null)
            {
                return BadRequest();
            }

            foreach (var b in books)
            {


                var newBook = new Book
                {
                    Id = b.Id,
                    Title = b.Title,
                    Description = b.Description,
                    Year = b.Year,
                    Pages = b.Pages,
                    Price = b.Price,
                    GenreId = id
                };

                
                _context.Books.Add(newBook);
                
           
                await _context.SaveChangesAsync();
            
            }

            return NoContent();
        }

        // POST: api/genre
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost]
        public async Task<ActionResult<Genre>> PostGenre(GenreDTO genreDTO)
        {
            if (_context.Genres == null)
            {
                return Problem("Entity set 'BookContext.Genre'  is null.");
            }

            var genre = new Genre
            {
                Id = genreDTO.Id,
                Name = genreDTO.Name,
                Description = genreDTO.Description,
                Subgenre = genreDTO.Subgenre,
                CountryOfOrigin = genreDTO.CountryOfOrigin,
                GenreRating = genreDTO.GenreRating,
                BookList = null!
            };

            _context.Genres.Add(genre);
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetGenre), new { id = genreDTO.Id }, GenreToDTO(genre));
        }

        // DELETE: api/genre/5
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteGenre(int id)
        {
            if (_context.Genres == null)
            {
                return NotFound();
            }
            var genre = await _context.Genres.FindAsync(id);
            if (genre == null)
            {
                return NotFound();
            }

            _context.Genres.Remove(genre);
            await _context.SaveChangesAsync();

            return NoContent();
        }

        private bool GenreExists(int id)
        {
            return (_context.Genres?.Any(e => e.Id == id)).GetValueOrDefault();
        }

        private static GenreDTO GenreToDTO(Genre genre)
        {
            return new GenreDTO
            {
                Id = genre.Id,
                Name = genre.Name,
                Description = genre.Description,
                Subgenre = genre.Subgenre,
                CountryOfOrigin = genre.CountryOfOrigin,
                GenreRating = genre.GenreRating
            };
        }
    }
}
