using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model.Entitys
{
    public class learn
    {
        // 用户名
        public string username { get; set; }

        // 课程学习时长（单位：秒）
        [SugarColumn(IsNullable = true)]
        public int LessonTime { get; set; }

        // 课程 ID
        [SugarColumn(IsNullable = true)]
        public int LessonId { get; set; }

        // 课程笔记
        [SugarColumn(IsNullable = true, Length = int.MaxValue, SqlParameterDbType = "varchar(max)")]
        public string Note { get; set; }

        // 笔记建立时间
        [SugarColumn(IsNullable = true)]
        public DateTime NoteTime { get; set; }
        //课程状态
        [SugarColumn(IsNullable = true)]
        public string Learing { get; set; }
        //课程进度
        [SugarColumn(IsNullable = true)]
        public string Leared { get;set; }
        //喜欢
        [SugarColumn(IsNullable = true)]
        public int like { get; set; }
        //评论数
        [SugarColumn(IsNullable = true)]
        public int ReplyCount  { get; set;}
    }
}
