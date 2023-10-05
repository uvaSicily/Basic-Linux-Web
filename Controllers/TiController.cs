using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Model;
using Model.Entitys;

namespace Day5.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class TiController : ControllerBase
    {
        [HttpGet]
        public ApiResult GetAllTi()
        {
            using var db = Common.DbContext.GetDbClient();//调用数据库连接
            var result = new ApiResult { IsSuccess = true };
            try
            {
                // 使用 SqlSugar 的 Queryable API 查询所有题库数据
                var allTi = db.Queryable<ti>().ToList();

                result.Result = allTi;
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
