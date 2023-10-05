using AutoMapper;
using Common;
using Model.Entitys;

namespace Service
{
    public class userService : IuserService
    {
        private readonly IMapper _mapper;
       
        public userService(IMapper mapper)
        {
            _mapper = mapper;
        }

     /*   public UserRes GetUs(uReq req)
        {
            var user = DbContext.db.Queryable<Users>().First(p => p.username == req.username );
            if (user != null)
            {
                return _mapper.Map<UserRes>(user);

            }
            return new UserRes();

        }*/

        /*  public List<UserRes> GetUsers(UserReq req)
          {
              List<Users>res = new List<Users>();
               res = Common.DbContext.db.Queryable<Users>().Where( x => x.username == req.username&& x.password == req.password).ToList();

              return _mapper.Map<List<UserRes>>(res);
          }*/

        public UserRes GetUsers(UserReq req)
        {
            using var db = DbContext.GetDbClient(); // 从连接池中获取连接，并在 using 块结束时自动释放
            var user=db.Queryable<Users>().First(p=>p.username==req.username && p.password==req.password);
               if (user != null)
               {
                   return _mapper.Map<UserRes>(user);

               }return new UserRes();

           }
        
          public UserRes RegisterUser(RegisterReq req,ref string msg)
        {
            using var db = DbContext.GetDbClient(); // 从连接池中获取连接，并在 using 块结束时自动释放
            var user = db.Queryable<Users>().First(p => p.username == req.username );
             if (user != null ) {
                   msg = "账号已存在";
                   return _mapper.Map<UserRes>(user);
               }
             else
               {
                   try
                   {
                       Users users = _mapper.Map<Users>(req);
                    users.usertype = "普通用户";
                    users.name=users.username;
                       bool res = db.Insertable(users).ExecuteCommand() > 0;
                       if (res)
                       {
                           user = db.Queryable<Users>().First(p => p.username == req.username && p.password == req.password);
                           return _mapper.Map<UserRes>(user);
                       }
                   }
                   catch (Exception ex)
                   {
                       msg = ex.Message;
                   }
               }
               return new UserRes();
           }

    }
}
