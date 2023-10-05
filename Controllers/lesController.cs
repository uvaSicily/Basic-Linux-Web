using AutoMapper;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Model;
using Model.Entitys;
using Service;

namespace Day5.Controllers
{
    [Route("api/[controller]/[action]")]
    [ApiController]
    public class lesController : ControllerBase
    {
        public Serices _serices;
        public lesController(Serices serices)
        {
            _serices = serices;

        }

    /// <summary>
    /// 查询课程
    /// </summary>
    /// <param name="req"></param>
    /// <returns></returns>

                  [HttpPost]
        public ApiResult GetLessons(lessonReq req)
        {
            ApiResult result = new ApiResult()
            {
                IsSuccess = true,
            };
            result.Result = _serices.GetLessons(req);
            return result;
        }
    }


    


}
