using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Model;
using Model.Entitys;

namespace Day5.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ScoreController : ControllerBase
    {
        [HttpPost]
        public ApiResult Create(Scores model)
        {
            var result = new ApiResult { IsSuccess = true };
            using var db = Common.DbContext.GetDbClient();//调用数据库连接
            try
            {
                // 使用 Sugar ORM 将数据插入到数据库中
                db.Insertable(model).ExecuteCommand();
               
            }
            catch (Exception ex)
            {
                result.IsSuccess = false;
                result.Msg = ex.Message;
            }
            return result;
        }
        [HttpGet]
        public ApiResult GetAllScore()
        {       
            using var db = Common.DbContext.GetDbClient();//调用数据库连接
            var result = new ApiResult { IsSuccess = true };
            try
            {
                // 使用 SqlSugar 的 Queryable API 查询最新一条数据
                var latestTi = db.Queryable<Scores>().OrderByDescending(t => t.ScoreTime).First();

                result.Result = latestTi;
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
