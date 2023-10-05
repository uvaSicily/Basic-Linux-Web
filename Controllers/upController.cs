using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Model.Entitys;
using SqlSugar;

namespace Day5.Controllers
{
    [Route("api/[controller]/[action]")]
    [ApiController]
    public class upController : ControllerBase
    {
        private readonly IWebHostEnvironment _environment;

        public upController(IWebHostEnvironment environment)
        {
            _environment = environment;
        }

        [HttpPost]
        public async Task<IActionResult> Upload(IFormFile file, string resourceId, int lessonId, string upuser = "")
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            try
            {
                if (file == null || file.Length == 0)
                {
                    return BadRequest("No file selected.");
                }

                var extension = Path.GetExtension(file.FileName);
                if (string.IsNullOrEmpty(extension))
                {
                    return BadRequest("Invalid file type.");
                }

                // 保存文件至文件夹
                var uploadsFolder = @"C:\Users\临璟\Desktop\download\bishe\files";
                Directory.CreateDirectory(uploadsFolder);

                var filePath = Path.Combine(uploadsFolder, $"{resourceId}{extension}");
                using (var stream = new FileStream(filePath, FileMode.Create))
                {
                    await file.CopyToAsync(stream);
                }

                // 保存文件至数据库
                var db = new SqlSugarClient(new ConnectionConfig()
                {
                    ConnectionString = "data source=LAPTOP-HSQGJ7CB;initial catalog=linuxdo;integrated security=sspi",
                    DbType = DbType.SqlServer,
                    IsAutoCloseConnection = true
                });

                var resource = new Resources()
                {
                    ResourceId = resourceId,
                    ResourceType = extension,
                    ResourceName = file.FileName,
                    Uptime = DateTime.Now,
                    Upuser = upuser ?? "", // Set upuser as empty string if null
                    LessonId = lessonId // Add lesson id to resource
                };

                db.Insertable(resource).ExecuteCommand();

                return Ok();
            }
            catch (Exception ex)
            {
                return StatusCode(500, $"Internal server error: {ex}");
            }
        }
    }
    }
