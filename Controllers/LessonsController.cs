using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Model;
using Model.Entitys;
using Service;

namespace Day5.Controllers
{
    [Route("api/[controller]/[action]")]
    [ApiController]
    public class LessonsController : ControllerBase
    {
        public Serices  _serices;
        public LessonsController(Serices serices) {
            _serices = serices;
             
        }
        [HttpPost]
        public ApiResult GetLessons(lessonReq req)
        {
           ApiResult result = new ApiResult()
           {
               IsSuccess = true,
           };
            result.Result =_serices.GetLessons(req);
            return result;
        }
    }
}
