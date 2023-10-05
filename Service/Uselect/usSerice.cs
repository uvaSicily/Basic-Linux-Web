using AutoMapper;
using Common;
using Model.Entitys;

namespace Service
{
    public class usSerice:IusSerice
    {
        private readonly IMapper _mapper;

        public usSerice(IMapper mapper)
        {
            _mapper = mapper;
        }
     /*   public List<USres> GetUer(USReq req)
        {
            List<Users> res = new List<Users>();

            res = Common.DbContext.db.Queryable<Users>().WhereIF(req.username != null, x => x.username == req.username).ToList();

            return _mapper.Map<List<USres>>(res);
        }*/
          public USres GetUer(USReq req)
        {
            using var db = DbContext.GetDbClient(); // 从连接池中获取连接，并在 using 块结束时自动释放
            var user = db.Queryable<Users>().First(p => p.username == req.username );
               if (user != null)
               {
                   return _mapper.Map<USres>(user);

               }
               return new USres();

           }
    }
}
