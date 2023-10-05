using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Model;
using Service;
using Service.Chapter;
using Service.learns;
using Service.learns.Dto;

namespace Day5.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class learnController : ControllerBase
    {
        public Ilearn _services;
        public learnController(Ilearn services)
        {
            _services = services;

        }

        [HttpPost]
        public ApiResult Getlearn(learnReq req)
        {
            ApiResult result = new ApiResult()
            {
                IsSuccess = true,
            };
            result.Result = _services.Getlearn(req);
            return result;
        }
    }
}
