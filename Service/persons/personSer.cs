using AutoMapper;
using Model.Entitys;
using Service.persons.Dto;
using Service.Teachers.Dto;
using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.persons
{
    public class personSer:Iperson
    {
        private readonly IMapper _mapper;
        public personSer(IMapper mapper)
        {
            _mapper = mapper;
        }
       public List<personRes> GetPerson(personReq req)
        {
            using var db = Common.DbContext.GetDbClient(); // 从连接池中获取连接，并在 using 块结束时自动释放
            var order = db.Queryable<person>().Where(p => p.UserId == req.username).Select(s => new personRes
            {
           
             Name = s.Name,
             Depart =s.Depart,
             School=s.School, 
                Dept =s.Dept,
                Image =s.Image,
                ViewsText = SqlFunc.Subqueryable<Views>().Where(f => f.UserId== s.UserId).Select(f => f.ViewsText),//子查询
                ViewTime = SqlFunc.Subqueryable<Views>().Where(f => f.UserId == s.UserId).Select(f => f.ViewTime),//子查询
 like = SqlFunc.Subqueryable<Views>().Where(f => f.UserId == s.UserId).Select(f => f.like),
                ReplyCount = SqlFunc.Subqueryable<Views>().Where(f => f.UserId == s.UserId).Select(f => f.ReplyCount),
                
            }).OrderBy(p => p.ViewTime, OrderByType.Desc).ToList();
            return order;

        }
    }
}
