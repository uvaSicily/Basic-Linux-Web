using AutoMapper;
using Model.Entitys;
using Service.Resource.Dto;
using Service.Teachers.Dto;
using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.Resource
{
    public class Recourcement:IRecource
    {
        private readonly IMapper _mapper;
        public Recourcement(IMapper mapper)
        {
            _mapper = mapper;
        }
        public  List<ResourceRes> GetRecource(RescSecReq req)
        {  using var db = Common.DbContext.GetDbClient(); // 从连接池中获取连接，并在 using 块结束时自动释放
            var order = db.Queryable<Resources>().Where(p => p.LessonId == req.LessonId).Select(s => new ResourceRes
            {
                 ResourceId =s.ResourceId,
         LessonId =s.LessonId,
        ResourceType =s.ResourceType,
        ResourceName =s.ResourceName,
        Uptime =s.Uptime,
        Upuser =s.Upuser,
    }).OrderBy(p => p.ResourceId, OrderByType.Desc).ToList();
            return order;
        }
    }
}
