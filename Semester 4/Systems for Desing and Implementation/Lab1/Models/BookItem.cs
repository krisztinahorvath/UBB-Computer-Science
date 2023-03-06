namespace BooksAPI.Models
{
    public class BookItem
    {
        public int Id { get; set; }
        public string? Title { get; set; }
        public string? Description { get; set; }
        public string? Author { get; set; }
        public int Pages { get; set; } 
        public float Price { get; set; }
    }
}
