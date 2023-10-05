using AutoMapper;
using Model.Entitys;
using Service.Teachers.Dto;
using Service.View.Dto;
using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.View
{
    public class viewSerives:Iviews
    {
        private readonly IMapper _mapper;

        public viewSerives(IMapper mapper)
        {
            _mapper = mapper;
        }
       public List<ViewRes> GetViews(ViewReq req)
        {
            using var db = Common.DbContext.GetDbClient(); // 从连接池中获取连接，并在 using 块结束时自动释放
            var order = db.Queryable<Views>().Where(p => p.LessonId == req.LessonId).Select(s => new ViewRes
            {
               UserId = s.UserId, 
                LessonId = s.LessonId,
         
    ViewsId  = s.ViewsId,
     
        ViewsText = s.ViewsText,
        ViewTime =s.ViewTime,
       ViewDate =s.ViewDate,
       like =s.like,
        ReplyCount=s.ReplyCount,
            Name = SqlFunc.Subqueryable<person>().Where(f => f.UserId == s.UserId).Select(f => f.Name),//子查询
                Image = SqlFunc.Subqueryable<person>().Where(f => f.UserId == s.UserId).Select(f => f.Image),
            }).ToList();
            if (order.Count == 0)
            {
                order.Add(new ViewRes
                {
                    UserId = "--",
                    LessonId = req.LessonId,
                    ViewsId = null,
                    ViewsText = "暂无",
                    ViewTime = DateTime.MinValue,
                    ViewDate = DateTime.MinValue,
                    like = 0,
                    ReplyCount = 0,
                    Name = "--",
                    Image = "--"
                });
            }

            return order;
        }
    }
}
