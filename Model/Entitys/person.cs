using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model.Entitys
{
    public class person
    {//userid
        [SugarColumn(IsPrimaryKey = true)]
        public string UserId { get; set; }
        //用户名
        [SugarColumn(IsNullable = true)]
        public string Name { get; set; }
        //班级
        [SugarColumn(IsNullable = true)]
        public string Depart { get; set; }
        //学校
        [SugarColumn(IsNullable = true)]
        public string School { get; set; }
        //院系
        [SugarColumn(IsNullable = true)]
        public string Dept{ get; set; }
        //头像
        [SugarColumn(IsNullable = true)]
        public string Image { get; set; }
    }
}
