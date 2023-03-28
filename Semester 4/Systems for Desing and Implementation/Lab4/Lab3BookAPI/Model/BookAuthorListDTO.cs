namespace Lab3BookAPI.Model
{
    public class BookAuthorListDTO
    {
        public int BookId { get;set; }
        public List<int> AuthorId { get;set; }

        public float BookRating { get; set; }
        public float AuthorRating { get; set; }
    }
}
