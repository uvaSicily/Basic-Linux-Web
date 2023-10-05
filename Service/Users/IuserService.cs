namespace Service
{
    public interface IuserService
    {
       // List<UserRes>GetUsers(UserReq req);
        UserRes GetUsers(UserReq req);
        //UserRes GetUs(uReq req);
      UserRes RegisterUser(RegisterReq req, ref string msg);
    }
}
