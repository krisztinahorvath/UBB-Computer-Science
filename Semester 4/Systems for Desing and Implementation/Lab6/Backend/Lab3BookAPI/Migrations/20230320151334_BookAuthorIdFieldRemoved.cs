using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Lab3BookAPI.Migrations
{
    /// <inheritdoc />
    public partial class BookAuthorIdFieldRemoved : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "Id",
                table: "BookAuthors");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<int>(
                name: "Id",
                table: "BookAuthors",
                type: "int",
                nullable: false,
                defaultValue: 0);
        }
    }
}
