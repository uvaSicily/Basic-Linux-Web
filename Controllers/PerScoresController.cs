using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Model;
using Model.Entitys;
using SqlSugar;

namespace Day5.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class PerScoresController : ControllerBase
    {
       

        [HttpGet("{userId}")]
        public ApiResult GetTotalScore(string userId)
        {
            var result = new ApiResult { IsSuccess = true };
            using var db = Common.DbContext.GetDbClient();//调用数据库连接
            try
            {
                // 使用 SqlSugar 的 Queryable API 查询成绩总分
                var totalScore = db.Queryable<Scores>().Where(s => s.UserId == userId).Sum(s => s.Score);

                result.Result = totalScore;
            }
            catch (Exception ex)
            {
                result.IsSuccess = false;
                result.Msg = ex.Message;
            }
            finally
            {
                db.Dispose(); // 释放数据库连接
            }
            return result;
        }
    }
}
