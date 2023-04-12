using Lab3BookAPI.Model;
using Lab3BookAPI.Utils;
using Lab3BookAPI.Validations;
using Microsoft.EntityFrameworkCore;
using Microsoft.IdentityModel.Tokens;

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
            builder.Services.AddSingleton<Validate>();


            // add the database context to the DI container
            // and specify that the database context will use a sql server database

            var localConnectionString = "LocalBooksDatabase";
            if (localConnectionString.IsNullOrEmpty())
            {
                builder.Services.AddDbContext<BookContext>(options => options.UseSqlServer(builder.Configuration.GetConnectionString("BooksDatabase")));
            }
            else
                builder.Services.AddDbContext<BookContext>(options => options.UseSqlServer(builder.Configuration.GetConnectionString(localConnectionString)));
            // builder.Services.AddDbContext<BookContext>(options => options.UseSqlServer(builder.Configuration.GetConnectionString("BooksDatabase")));

            // add endpoints
            builder.Services.AddEndpointsApiExplorer();

            // add swagger
            builder.Services.AddSwaggerGen();

            builder.Services.ConfigureSwaggerGen(setup =>
            {
                setup.SwaggerDoc("v1", new Microsoft.OpenApi.Models.OpenApiInfo
                {
                    Title = "Book Management",
                    Version = "v1"
                });
            });

            var app = builder.Build();

            // seed database
            //using (var scope = app.Services.CreateScope())
            //{
            //    var services = scope.ServiceProvider;
            //    SeedData.Initialize(services);
            //}

            app.UseSwagger();
            app.UseSwaggerUI();

            // configure the HTTP request pipeline for swagger
            if (app.Environment.IsDevelopment())
            {
                app.UseCors(options => options.AllowAnyOrigin().AllowAnyMethod().AllowAnyHeader());
            }

            app.UseHttpsRedirection();

            app.UseAuthorization();

            app.MapControllers();

            app.Run();
        }
    }
}