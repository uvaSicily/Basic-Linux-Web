using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model.Entitys
{
    public class depart
    {//班级id
        [SugarColumn(IsPrimaryKey = true)]
        public string DepartId { get; set; }
        //教师id
        [SugarColumn(IsNullable = true)]
        public string teacherId { get; set; }
        //班级名
        [SugarColumn(IsNullable = true)]
        public string DepartName { get; set; }

    }
}
