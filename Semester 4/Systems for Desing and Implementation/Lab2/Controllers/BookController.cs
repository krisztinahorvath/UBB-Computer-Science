using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Lab2.Model;

namespace Lab2.Controllers
{
    [Route("api/books")]
    [ApiController]
    public class BookItemsController : ControllerBase
    {
        private readonly BookContext _context;

        public BookItemsController(BookContext context)
        {
            _context = context;
        }

        // GET: api/BookItems
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Book>>> GetBookItems()
        {
            if (_context.Books == null)
            {
                return NotFound();
            }
            return await _context.Books.ToListAsync();
        }

        // GET: api/BookItems/5
        [HttpGet("{id}")]
        public async Task<ActionResult<Book>> GetBookItem(int id)
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

            return bookItem;
        }

        //[HttpGet("{year}")]
        //public async Task<ActionResult<Book>> GetBooks(int year)
        //{
        //    if (_context.Books == null)
        //           return NotFound();

        //}

        [HttpGet("year")]
        public IActionResult GetBooks([FromQuery] int year)
        {
            var books = _context.Books.Where(books => books.Year > year).ToList();

            return Ok(books);
        }

        [HttpGet("filter/{year}")]
        public async Task<IActionResult> FilterByYear(int year)
        {
            if(_context.Books == null)
            {
                return NotFound();
            }
            var book = await _context.Books.Where(books => books.Year > year).ToListAsync();
            return Ok(book);
        }

        //[HttpGet("{year}")]
        //public async Task<ActionResult<Book>> FilterByYear(int year)
        //{
        //    if (_context.Books == null)
        //    {
        //        return NotFound();
        //    }
        //    var bookItem = await _context.Books.FindAsync(year);

        //    if (bookItem == null)
        //    {
        //        return NotFound();
        //    }

        //    return bookItem;
        //}

        // PUT: api/BookItems/5
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPut("{id}")]
        public async Task<IActionResult> PutBookItem(int id, Book bookItem)
        {
            if (id != bookItem.Id)
            {
                return BadRequest();
            }

            _context.Entry(bookItem).State = EntityState.Modified;

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

        // POST: api/BookItems
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost]
        public async Task<ActionResult<Book>> PostBookItem(Book bookItem)
        {
            if (_context.Books == null)
            {
                return Problem("Entity set 'BookContext.BookItems'  is null.");
            }
            _context.Books.Add(bookItem);
            await _context.SaveChangesAsync();

            // return CreatedAtAction("GetBookItem", new { id = bookItem.Id }, bookItem);

            return CreatedAtAction(nameof(GetBookItem), new { id = bookItem }, bookItem);
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
    }
}
