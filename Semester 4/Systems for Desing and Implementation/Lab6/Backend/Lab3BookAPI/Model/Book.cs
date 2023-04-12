namespace Lab3BookAPI.Model
{
    public class Book
    {
        public int Id { get; set; }
        public string? Title { get; set; }
        public string? Description { get; set; }
        public int Year { get; set; }
        public int Pages { get; set; }
        public float Price { get; set; }

        public string? Transcript { get; set; } 

        public int GenreId { get; set; }
        public virtual Genre Genre { get; set; } = null!;


        public virtual ICollection<BookAuthor> BookAuthors { get; set;  }
    }
}