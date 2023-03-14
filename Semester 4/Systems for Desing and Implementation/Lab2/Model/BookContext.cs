using Microsoft.EntityFrameworkCore;
using Microsoft.Identity.Client;
using Lab2.Model;

namespace Lab2.Model
{
    public class BookContext: DbContext
    {
        public BookContext(DbContextOptions<BookContext> options) : base(options) { }
        public DbSet<Book>? Books { get; set;}
        public DbSet<Genre>? Genres { get; set;}    
        public DbSet<Lab2.Model.Author> Author { get; set; } = default!;
    }
}
