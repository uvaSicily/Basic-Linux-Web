using Common;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Model;
using Service;
using Service.Teachers;
using Service.Teachers.Dto;

namespace Day5.Controllers
{
    [Route("api/[controller]/[action]")]
    [ApiController]
    public class TeachersController : ControllerBase
    {
        public Iteacher _iteacher;
        public TeachersController(Iteacher iteacher)
        {
            _iteacher = iteacher;
        }
        [HttpPost]
        public ApiResult Getteacher(teacherReq req)
        {
            ApiResult result = new ApiResult()
            {
                IsSuccess = true,
            };
       
            result.Result = _iteacher.Getteachers(req);
            return result;

        }
        
    }
}
