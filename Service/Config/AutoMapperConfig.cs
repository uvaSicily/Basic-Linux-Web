using AutoMapper;
using Model.Entitys;
using Service.Chapter.Dto;
using Service.Depart.Dto;
using Service.learns.Dto;
using Service.persons.Dto;
using Service.Resource;
using Service.Resource.Dto;
using Service.Teachers.Dto;
using Service.View.Dto;

namespace Service.Config
{
    public class AutoMapperConfig:Profile
    {
        /// <summary>
        /// 在构造函数中配置映射关系
        /// </summary>
        public AutoMapperConfig() {
            //从A映射到B
            CreateMap<lesson, lessonRes>();
            CreateMap<Users,UserRes>();
            CreateMap<RegisterReq, Users>();
           // CreateMap<Users, UserRes>();
            CreateMap<Users, USres>();
            CreateMap<teacher, teacherRes>();
            CreateMap<depart, teacherRes>();
            CreateMap<depart, DepartRes>();
            CreateMap<Views, ViewRes>();
            CreateMap<person,ViewRes>();
            CreateMap<Chapters,ChapterRes>();
            CreateMap<Resources, ResourceRes>();
            CreateMap<Views, personRes>();
            CreateMap<person, personRes>();
            CreateMap<learn, learnRes>();
        }
    }
}
