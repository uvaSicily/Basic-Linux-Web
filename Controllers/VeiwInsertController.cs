using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Model;
using Model.Entitys;
using Service.View.Dto;
using SqlSugar;

namespace Day5.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class VeiwInsertController : ControllerBase
    {
        [HttpPost]
        public ApiResult AddComment(Views views)
        {
            var apiResult = new ApiResult { IsSuccess = false };

            // 检查参数是否为空
            if (string.IsNullOrEmpty(views.ViewsText))
            {
                apiResult.Msg = "评论内容不能为空";
            }
            else
            {
                try
                {
                    using var db = Common.DbContext.GetDbClient();

                    // 设置评论时间为当前时间
                    views.ViewTime = DateTime.Now;

                    // 将评论插入到数据库中
                    db.Insertable(views).ExecuteCommand();

                    apiResult.IsSuccess = true;
                    apiResult.Result = views.ViewsId;
                }
                catch (Exception ex)
                {
                    // 出错时返回错误信息
                    apiResult.Msg = ex.Message;
                }
            }

            return apiResult;
        }



    }
}
