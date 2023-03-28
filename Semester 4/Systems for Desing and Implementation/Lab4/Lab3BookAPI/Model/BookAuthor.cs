namespace Lab3BookAPI.Model
{
    public class BookAuthor
    {
        //public int Id { get; set; }

        public int BookId { get; set; }
        public virtual Book Book { get; set; }

        public int AuthorId { get; set; }
        public virtual Author Author { get; set; }

        //public ICollection<Book> Books { get; set; } = new HashSet<Book>();
        //public ICollection<Author>  Authors { get; set; } = new HashSet<Author>();
        public float BookRating { get; set; }
        public float AuthorRating { get; set; }
    }
}
