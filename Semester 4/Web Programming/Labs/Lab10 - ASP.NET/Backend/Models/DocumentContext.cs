using Microsoft.EntityFrameworkCore;
using Lab10.Models;

namespace Lab10.Models
{
    public class DocumentContext : DbContext
    {
        public DocumentContext(DbContextOptions<DocumentContext> options) : base(options) { }

        public DbSet<Document> Documents { get; set; } = null!;

        public DbSet<User> Users { get; set; } = default!;
    }

}
