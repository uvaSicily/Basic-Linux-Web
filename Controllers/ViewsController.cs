using Common;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Model;
using Model.Entitys;
using Service.Teachers.Dto;
using Service.Teachers;
using SqlSugar;
using System;
using DbContext = Common.DbContext;
using Service.View.Dto;
using Service.View;

namespace Day5.Controllers
{
    [Route("api/[controller]/[action]")]
    [ApiController]
    public class ViewsController : ControllerBase
    {
      
        public Iviews _iviews;
        public ViewsController(Iviews iviews)
        {
            _iviews = iviews;
        }

        // GET: api/views
        [HttpPost]

        public ApiResult GetViews(ViewReq req)
        {
            var result = new ApiResult { IsSuccess = true };

            try
            {
                var data = _iviews.GetViews(req);
                result.Result = data;
            }
            catch (Exception ex)
            {
                result.IsSuccess = false;
                result.Msg = ex.Message;
            }

            return result;
        }
      /*  ApiResult result = new ApiResult()
            {
                IsSuccess = true,
            };

            result.Result = _iviews.GetViews(req);
            return result;

        }*/

        // POST: api/views
        /*    [HttpPost]
            public IActionResult Post(ViewsInputModel model)
            {
                var db = new SqlSugarClient(new ConnectionConfig()
                {
                    ConnectionString = "data source=LAPTOP-HSQGJ7CB;initial catalog=linuxdo;integrated security=sspi",
                    DbType = DbType.SqlServer,
                    IsAutoCloseConnection = true
                });
                var view = new Views
                {
                    UserId = model.UserId,
                    LessonId = model.LessonId,
                    ViewsText = model.ViewsText,
                    ViewTime = DateTime.Now,
                    ViewDate = DateTime.Now.Date,
                    like = 0,
                    ReplyCount = 0
                };

                db.Insertable(view).ExecuteReturnIdentity();

                return Ok(new { message = "评论添加成功." });
            }
        }

        public class ViewsInputModel
        {
            public string UserId { get; set; }
            public string LessonId { get; set; }
            public string ViewsText { get; set; }
        }*/
    }
}
        


