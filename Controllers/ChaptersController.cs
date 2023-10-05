using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Model;
using Service;
using Service.Chapter;
using Service.Chapter.Dto;

namespace Day5.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ChaptersController : ControllerBase
    {
        public IChapters _services;
        public ChaptersController(IChapters services)
        {
            _services = services;

        }
        [HttpPost]
        public ApiResult GetChapter(ChapterReqs req)
        {
           
                ApiResult result = new ApiResult()
                {
                    IsSuccess = true,
                };
                result.Result = _services.GetChapter(req);
                return result;
            }
        
    }
}
