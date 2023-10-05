using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Model;
using Service.Chapter.Dto;
using Service.Chapter;
using Service.Resource;
using Service.Resource.Dto;

namespace Day5.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class RecourceSelController : ControllerBase
    {
        public IRecource _services;
        public RecourceSelController(IRecource services)
        {
            _services = services;

        }
        [HttpPost]
        public ApiResult GetRecource(RescSecReq req)
        {

            ApiResult result = new ApiResult()
            {
                IsSuccess = true,
            };
            result.Result = _services.GetRecource(req);
            return result;
        }
    }
}
