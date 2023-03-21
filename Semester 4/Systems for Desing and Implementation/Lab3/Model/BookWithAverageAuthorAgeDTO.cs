namespace Lab3BookAPI.Model
{
    public class BookWithAverageAuthorAgeDTO
    {
        public int Id { get; set; }
        public string? Title { get; set; }
        public string? Description { get; set; }
        public int Year { get; set; }
        public int Pages { get; set; }
        public float Price { get; set; }
        public double? AverageAuthorAge { get; set; }
    }
}
