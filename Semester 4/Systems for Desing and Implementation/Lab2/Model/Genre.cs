namespace Lab2.Model
{
    public class Genre
    {
        public int Id { get; set; }
        public string? Name { get; set; }
        public string? Description { get; set; }
        public string? Subgenre { get; set; }
        public string? CountryOfOrigin { get; set; }
        public int GenreRating { get; set; }


        public ICollection<Book>? BookList { get; set; }
    }
}
