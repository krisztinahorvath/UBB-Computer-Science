using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Lab3BookAPI.Migrations
{
    /// <inheritdoc />
    public partial class BookTranscript : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<string>(
                name: "Transcript",
                table: "Books",
                type: "nvarchar(max)",
                nullable: true);
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "Transcript",
                table: "Books");
        }
    }
}
