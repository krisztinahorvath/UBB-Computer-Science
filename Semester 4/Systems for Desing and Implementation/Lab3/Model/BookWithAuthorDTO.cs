namespace Lab3BookAPI.Model
{
    public class BookWithAuthorDTO
    {
        public Book Books { get; set; }
        public ICollection<Author> Authors { get; set; }
    }
}
