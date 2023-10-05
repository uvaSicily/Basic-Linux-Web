using AutoMapper;
using Common;
using Microsoft.EntityFrameworkCore;
using Model.Entitys;
using Service.Teachers.Dto;
using SqlSugar;
using SqlSugar.Extensions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Linq;

namespace Service.Teachers
{
    public class teachers : Iteacher
    {
        private readonly IMapper _mapper;
        public teachers(IMapper mapper)
        {
            _mapper = mapper;
        }
        //post
        public List<teacherRes> Getteachers(teacherReq req)
        {
            using var db =  Common.DbContext.GetDbClient(); // 从连接池中获取连接，并在 using 块结束时自动释放
            var order =db.Queryable<teacher>().Where(p => p.Id == req.username).Select(s => new teacherRes
            {
                Id = s.Id,
                Name = s.Name,
                IsEmployed = s.IsEmployed,
                School = s.School,
                teacherImage = s.teacherImage,
                teacherText =s.teacherText,
        DepartName = SqlFunc.Subqueryable<depart>().Where(f => f.teacherId == s.Id).Select(f => f.DepartName),//子查询
                DepartId = SqlFunc.Subqueryable<depart>().Where(f => f.teacherId == s.Id).Select(f => f.DepartId),
            }).OrderBy(p=>p.DepartId,OrderByType.Desc).ToList();
            return order;


            //List<teacher> res = new List<teacher>();

            // res = Common.DbContext.db.Queryable<teacher>().WhereIF(req.username != null, x => x.Id == req.username).ToList();

            // return _mapper.Map<List<teacherRes>>(res);
        }
       public List<teacherRes> Getteacheres(teaReq req)
        {
            using var db = Common.DbContext.GetDbClient(); // 从连接池中获取连接，并在 using 块结束时自动释放
            var order =db.Queryable<teacher>().Where(p => p.Id == req.lessonTeacher).Select(s => new teacherRes
            {
                Id = s.Id,
                Name = s.Name,
                teacherImage = s.teacherImage,
                teacherText = s.teacherText,
       
            }).ToList();
            return order;

        }


    }
}
