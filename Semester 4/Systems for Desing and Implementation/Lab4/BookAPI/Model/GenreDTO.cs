namespace Lab3BookAPI.Model
{
    public class GenreDTO
    {
        public int Id { get; set; }
        public string? Name { get; set; }
        public string? Description { get; set; }
        public string? Subgenre { get; set; }
        public string? CountryOfOrigin { get; set; }
        public int GenreRating { get; set; }
    }
}
