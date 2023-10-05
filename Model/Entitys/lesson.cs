using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model.Entitys
{
    public class lesson
    {
        [SugarColumn(IsNullable = false, IsPrimaryKey = true)]
        public int Id { get; set; }
        //课程名
        [SugarColumn(IsNullable = true)]
        public string? LessonName { get; set; }

        //课程介绍
        [SugarColumn(IsNullable = true, Length = int.MaxValue, SqlParameterDbType = "varchar(max)")]
        public string? LessonText { get; set;}
        //课程简介
        [SugarColumn(IsNullable = true,Length =int.MaxValue,SqlParameterDbType ="varchar(max)")]
        public string? LessonTip { get; set;}
        //任课老师
        [SugarColumn(IsNullable = true)]
        public string? LessonTeacher { get; set;}
        //课程视频
        [SugarColumn(IsNullable = true)]
        public string? LessonVideo { get; set;}
        //课程配图
        [SugarColumn(IsNullable = true)]
        public string? LessonImage { get; set; }
        //课程类型
        [SugarColumn(IsNullable =true)]
        public string? LessonType { get; set; }
        //设计
        [SugarColumn(IsNullable = true, Length = int.MaxValue, SqlParameterDbType = "varchar(max)")]
        public string? LessonDis { get; set; }
        //公告
        [SugarColumn(IsNullable = true, Length = int.MaxValue, SqlParameterDbType = "varchar(max)")]
        public string? LessonWarn { get; set; }
    }
}
