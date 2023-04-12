namespace Lab3BookAPI.Model
{
    public class BookWithAuthorDTO
    {
        public virtual Book Books { get; set; }
        public virtual ICollection<Author> Authors { get; set; }
    }
}
