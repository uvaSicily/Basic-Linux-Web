using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Model;
using Model.Entitys;
using SqlSugar;

namespace Day5.Controllers
{
    [Route("api/[controller]")]
    [ApiController]

    public class viewLesController : ControllerBase
    {
      

        
        [HttpPost]
        public ApiResult AddView(string lessonId, string userId)
        {
            using var db = Common.DbContext.GetDbClient();//调用数据库连接
            DateTime viewDate = DateTime.Now;

            var result = new ApiResult { IsSuccess = true };

            try
            {
                var view = new Views()
                {
                    LessonId = lessonId,
                    UserId = userId,
                    ViewDate = viewDate
                };
                db.Insertable(view).ExecuteCommand();

            }
            catch (Exception ex)
            {
                result.IsSuccess = false;
                result.Msg = ex.Message;
            }

            return result;
        





    }


    }
}
