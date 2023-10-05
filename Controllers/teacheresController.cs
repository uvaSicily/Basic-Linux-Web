using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Model;
using Service.Teachers.Dto;
using Service.Teachers;

namespace Day5.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class teacheresController : ControllerBase
    {
        public Iteacher _iteacher;
        public teacheresController(Iteacher iteacher)
        {
            _iteacher = iteacher;
        }
        [HttpPost]
        public ApiResult Getteacheres(teaReq req)
        {
          
            ApiResult result = new ApiResult()
            {
                IsSuccess = true,
            };

            try
            {
                result.Result = _iteacher.Getteacheres(req);
            }
            catch (Exception ex)
            {
                result.IsSuccess = false;
                result.Msg = "Error in Getteacheres: " + ex.Message;//记录异常
                
            }

            return result;

        }
    }
}
