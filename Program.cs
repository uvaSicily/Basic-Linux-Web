using Service;
using Service.Chapter;
using Service.Config;
using Service.Depart;
using Service.learns;
using Service.persons;
using Service.Resource;
using Service.Teachers;
using Service.View;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.

builder.Services.AddControllers();
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();
//¿çÓò
builder.Services.AddCors(options =>
{
    options.AddPolicy("CorsPolicy", opt => opt.AllowAnyOrigin().AllowAnyHeader().AllowAnyMethod().WithExposedHeaders("X-Pagination"));
});

//×¢²áAutoMapper
builder.Services.AddAutoMapper(typeof(AutoMapperConfig));
//×¢²áservice·þÎñ
builder.Services.AddTransient<Serices,lessonService>();
builder.Services.AddTransient<IuserService, userService>();
builder.Services.AddTransient<IusSerice, usSerice>();
builder.Services.AddTransient<Iteacher, teachers>();
builder.Services.AddTransient<Iviews,viewSerives>();
builder.Services.AddTransient<IChapters, ChapterSer>();
builder.Services.AddTransient<IRecource, Recourcement>();
builder.Services.AddTransient<Iperson, personSer>();
builder.Services.AddTransient<Ilearn, learnSer>();
//builder.Services.AddTransient<IDeparts, Departs>();
var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseAuthorization();

app.MapControllers();
//Ê¹ÓÃ¿çÓò
app.UseCors("CorsPolicy");
app.Run();
