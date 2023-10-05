using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Model;
using Model.Entitys;
using Service;


namespace Day5.Controllers
{
    [Route("api/[controller]/[action]")]
    [ApiController]
    public class LoginController : ControllerBase
    {
        public IuserService _userService;
        public LoginController(IuserService iuserService) { 
        _userService = iuserService;
        }
        /// <summary>
        /// 登录
        /// </summary>
        /// <param name="req"></param>
        /// <returns></returns>
        [HttpPost]
        public ApiResult Check(UserReq req)
        {
            ApiResult apiResult = new ApiResult() { IsSuccess = false };
            if (string.IsNullOrEmpty(req.username) || string.IsNullOrEmpty(req.password))
                {
                apiResult.Msg = "参数不能为空";
            }
            else
            {

                UserRes user = _userService.GetUsers(req);
                if (string.IsNullOrEmpty(user.username))
                {
                    apiResult.Msg = "账号不存在，用户或密码错误！";
                }
                else
                {
                    apiResult.IsSuccess = true;
                    apiResult.Result =  user.username;
                    apiResult.type = user.usertype;

                }
               
            } return apiResult;
        }
        /// <summary>
        /// 注册
        /// </summary>
        /// <param name="req"></param>
        /// <returns></returns>
        /// 
        [HttpPost]
        public ApiResult Register(RegisterReq req)
        {
            ApiResult apiResult = new ApiResult() { IsSuccess=false};
            if(string.IsNullOrEmpty(req.username)||string.IsNullOrEmpty(req.password)){
                apiResult.Msg = "参数不能为空";

            }
            else
            {
                string msg = string.Empty;
                var res = _userService.RegisterUser(req,ref msg);
                if (!string.IsNullOrEmpty(msg))
                {
                    apiResult.Msg = msg;
                }
                else
                {
                    apiResult.IsSuccess=true;
                    apiResult.Result = req.username;
             
                }
            }return apiResult;

        }
    }
}
