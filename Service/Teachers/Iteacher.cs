using Model.Entitys;
using Service.Teachers.Dto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.Teachers
{
    public interface Iteacher
    {
        List<teacherRes> Getteachers(teacherReq req);
        List<teacherRes> Getteacheres(teaReq req);
    }
}
