using Common;
using Microsoft.AspNetCore.Mvc;
using Model;
using Model.Entitys;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace Day5.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class TeaController : ControllerBase
    {
        // GET: api/<TeaController>
        [HttpGet]
        public IEnumerable<teacher> Get()
        {
            using var db = DbContext.GetDbClient(); // 从连接池中获取连接，并在 using 块结束时自动释放
            var teachers = db.Queryable<teacher>().ToList();

            return teachers;
        }

      

        // POST api/<TeaController>
        [HttpPost]
        public ApiResult UploadLesson(lesson lesson)
        {
            ApiResult result = new ApiResult();

            if (string.IsNullOrWhiteSpace(lesson.LessonName) || lesson.Id==null)
            {
                result.IsSuccess = false;
                result.Result = null;
                result.Msg = "课程名或课程编号不能为空！";
                return result;
            }

            using var db = DbContext.GetDbClient(); // 从连接池中获取连接，并在 using 块结束时自动释放
            // 首先判断该课程编号是否已经存在，如果不存在，则新增课程信息
            var entity = db.Queryable<lesson>().Where(c => c.Id == lesson.Id).First();
            if (entity == null)
            {
               db.Insertable(lesson).ExecuteCommand();
            }
            else
            {
                // 如果课程编号已经存在，则更新课程信息
                entity.LessonName = lesson.LessonName;
                entity.LessonDis = lesson.LessonDis;
                entity.LessonTip = lesson.LessonTip;
               db.Updateable(entity).ExecuteCommand();
            }

            result.IsSuccess = true;
            result.Result = lesson;
            result.Msg = string.Empty;

            return result;
        }

       

      
    }
}
