using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Lab10.Models;
using Microsoft.AspNetCore.Authorization;
using System.Security.Claims;

namespace Lab10.Controllers
{
    [Route("api/documents")]
    [ApiController]
    public class DocumentsController : ControllerBase
    {
        private readonly DocumentContext _context;

        public DocumentsController(DocumentContext context)
        {
            _context = context;
        }

        // GET: api/Documents
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Document>>> GetDocuments()
        {

            if (_context.Documents == null)
            {
                return NotFound();
            }
            return await _context.Documents.ToListAsync();
        }

        [HttpGet("formats")]
        public async Task<ActionResult<IEnumerable<Document>>> GetDocumentsByFormat(string format)
        {

            var documents = await _context.Documents.Where(d => d.Format.ToLower() == format.ToLower())
                .ToListAsync();

            return Ok(documents);
        }

        [HttpGet("allformats")]
        public async Task<ActionResult<IEnumerable<string>>> GetAllDocumentFormats()
        {
            var formats = await _context.Documents
                .Select(d => d.Format)
                .Distinct()
                .ToListAsync();

            return formats;
        }

        [HttpGet("types")]
        public async Task<ActionResult<IEnumerable<Document>>> GetDocumentsByType(string type)
        {
            var documents = await _context.Documents.Where(d => d.Type.ToLower() == type.ToLower())
                .ToListAsync();

            return Ok(documents);
        }

        [HttpGet("alltypes")]
        public async Task<ActionResult<IEnumerable<string>>> GetAllDocumentTypes()
        {

            var types = await _context.Documents
                .Select(d => d.Type)
                .Distinct()
                .ToListAsync();

            return types;
        }

        // GET: api/Documents/5
        [HttpGet("{id}")]
        public async Task<ActionResult<Document>> GetDocument(int id)
        {

            if (_context.Documents == null)
          {
              return NotFound();
          }
            var document = await _context.Documents.FindAsync(id);

            if (document == null)
            {
                return NotFound();
            }

            return document;
        }

        // PUT: api/Documents/5
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPut("{id}")]
        public async Task<IActionResult> PutDocument(int id, Document document)
        {

            if (id != document.Id)
            {
                return BadRequest();
            }

            // validations
            if (document.Title.Length == 0)
            {
                return BadRequest("The 'Title' shouldn't be empty!");
            }

            if (document.NumberOfPages <= 0)
            {
                return BadRequest("Please enter a non-null positive number for the number of pages.");
            }

            if (document.Format.Length == 0)
            {
                return BadRequest("The 'Format' shouldn't be empty!");
            }

            _context.Entry(document).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!DocumentExists(id))
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

        // POST: api/Documents
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost]
        public async Task<ActionResult<Document>> PostDocument(Document document)
        {

            if (_context.Documents == null)
            {
                return Problem("Entity set 'DocumentContext.Documents'  is null.");
            }

            // validations
            if (document.Title.Length == 0)
            {
                return BadRequest("The 'Title' shouldn't be empty!");
            }

            if (document.NumberOfPages <= 0)
            {
                return BadRequest("Please enter a non-null positive number for the number of pages.");
            }

            if (document.Format.Length == 0)
            {
                return BadRequest("The 'Format' shouldn't be empty!");
            }


            _context.Documents.Add(document);
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetDocument), new { id = document.Id }, document);
        }

        // DELETE: api/Documents/5
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteDocument(int id)
        {
            if (_context.Documents == null)
            {
                return NotFound();
            }
            var document = await _context.Documents.FindAsync(id);
            if (document == null)
            {
                return NotFound();
            }

            _context.Documents.Remove(document);
            await _context.SaveChangesAsync();

            return NoContent();
        }

        private bool DocumentExists(int id)
        {
            return (_context.Documents?.Any(e => e.Id == id)).GetValueOrDefault();
        }
    }
}
