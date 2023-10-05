using Microsoft.AspNetCore.Mvc;
using Model;
using Service.learns.Dto;
using Service;
using Service.persons.Dto;
using Service.learns;
using Service.persons;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace Day5.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class personController : ControllerBase
    {

        public Iperson _services;
        public personController(Iperson services)
        {
            _services = services;

        }


        // POST api/<personController>
        [HttpPost]
        public ApiResult GetPerson(personReq req)
        {
            ApiResult result = new ApiResult()
            {
                IsSuccess = true,
            };
            result.Result = _services.GetPerson(req);
            return result;
        }

     
    }
}
