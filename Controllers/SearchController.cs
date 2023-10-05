using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Model.Entitys;
using Model;

namespace Day5.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class SearchController : ControllerBase
    {
        [HttpGet("search")]
        public ApiResult GetLessonsByName([FromQuery] string keyword)
        {
            using var db = Common.DbContext.GetDbClient();
            var result = new ApiResult { IsSuccess = true };
            try
            {
                // 使用 SqlSugar 的 Queryable API 模糊查询数据
                var lessons = db.Queryable<lesson>().Where(l => l.LessonName.Contains(keyword)).ToList();

                result.Result = lessons;
            }
            catch (Exception ex)
            {
                result.IsSuccess = false;
                result.Msg = ex.Message;
            }
            finally
            {
                db.Dispose();
            }
            return result;
        }
    }
}
