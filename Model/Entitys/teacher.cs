using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Metadata.Internal;
using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model.Entitys
{
    // 定义Teacher类，映射到数据库中的teacher表格
    public class teacher
    {//教师id==username
        [SugarColumn(IsPrimaryKey = true)]
        public string Id { get; set; }
        //教师名
        [SugarColumn(IsNullable = true)]
        public string Name { get; set; }
       
        //是否在职
        [SugarColumn(IsNullable = true)]
        public bool IsEmployed { get; set; }
        //任职学校
        [SugarColumn(IsNullable = true)]
        public string School { get; set; }
        //教师头像
        [SugarColumn(IsNullable = true)]
        public string teacherImage { get; set; }
        //教师简介
        [SugarColumn(IsNullable = true)]
        public string teacherText { get; set; }
        //教师id
        [SugarColumn(IsNullable = true)]
        public string UserId { get;set; }

    }
}
