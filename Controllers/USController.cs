using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Model;
using Service;



namespace Day5.Controllers
{
    [Route("api/[controller]/[action]")]
    [ApiController]
    public class USController : ControllerBase
    {
        public IusSerice _iusSerice;
        public USController(IusSerice iusSerice)
        {
            _iusSerice = iusSerice;
        }
        [HttpPost]
        public ApiResult GetUer(USReq req)
        {
            ApiResult result = new ApiResult()
            {
                IsSuccess = true,
            };
            result.Result = _iusSerice.GetUer(req);
            return result;
           
        }
    }
}
