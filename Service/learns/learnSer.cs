using AutoMapper;
using Model.Entitys;
using Service.learns.Dto;
using Service.persons.Dto;
using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.learns
{
    public class learnSer:Ilearn
    {
        private readonly IMapper _mapper;
        public learnSer(IMapper mapper)
        {
            _mapper = mapper;
        }
        public List<learnRes> Getlearn(learnReq req)
        {
            using var db = Common.DbContext.GetDbClient(); // 从连接池中获取连接，并在 using 块结束时自动释放
            var order = db.Queryable<learn>().Where(p => p.username == req.username).Select(s => new learnRes
            {

               LessonTime =s.LessonTime,
               LessonId =s.LessonId,
               Note =s.Note,
               NoteTime =s.NoteTime,
               Learing =s.Learing,
               Leared =s.Leared,
               like = s.like,
               ReplyCount =s.ReplyCount,
    }).OrderBy(p => p.NoteTime, OrderByType.Desc).ToList();
            return order;
        }
    }
}
