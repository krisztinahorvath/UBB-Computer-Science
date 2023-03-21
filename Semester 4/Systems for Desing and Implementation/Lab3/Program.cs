using Lab3BookAPI.Model;
using Microsoft.EntityFrameworkCore;
using Lab3BookAPI.Controllers;
using Microsoft.EntityFrameworkCore;
using System.Text.Json.Serialization;

namespace BooksAPI
{
    public class Program
    {
        static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);

            // add services to the container
            //builder.Services.AddControllers().AddJsonOptions(options => options.JsonSerializerOptions.Converters.Add(new JsonStringEnumConverter()));
            // builder.Services.AddControllers();

            builder.Services.AddControllers().AddNewtonsoftJson(options => options.SerializerSettings.ReferenceLoopHandling = Newtonsoft.Json.ReferenceLoopHandling.Ignore);

            // add the database context to the DI container
            // and specify that the database context will use a sql server database
            builder.Services.AddDbContext<BookContext>(options => options.UseSqlServer(builder.Configuration.GetConnectionString("BooksDatabase")));

            // add endpoints
            builder.Services.AddEndpointsApiExplorer();

            // add swagger
            builder.Services.AddSwaggerGen();

            var app = builder.Build();

            //// seed database
            //using (var scope = app.Services.CreateScope())
            //{
            //    var services = scope.ServiceProvider;
            //    SeedData.Initialize(services);
            //}

            // configure the HTTP request pipeline for swagger
            if (app.Environment.IsDevelopment())
            {
                app.UseSwagger();
                app.UseSwaggerUI();
            }

            app.UseHttpsRedirection();

            app.UseAuthorization();

            app.MapControllers();

            app.Run();
        }
    }
}

//var builder = WebApplication.CreateBuilder(args);

//// Add services to the container.

//builder.Services.AddDbContext<BookContext>(options => options.UseSqlServer(builder.Configuration.GetConnectionString("BooksDatabase")));

//builder.Services.AddControllers();
//// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
//builder.Services.AddEndpointsApiExplorer();
//builder.Services.AddSwaggerGen();

//var app = builder.Build();

//// Configure the HTTP request pipeline.
//if (app.Environment.IsDevelopment())
//{
//    app.UseSwagger();
//    app.UseSwaggerUI();
//}

//app.UseHttpsRedirection();

//app.UseAuthorization();

//app.MapControllers();

//app.Run();
