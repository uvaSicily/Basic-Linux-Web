using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model.Entitys
{
   public class Views
    {//用户id与Users外键关联
        [SugarColumn(IsNullable = true)]
        public string UserId { get; set; }

        //课程id与lesson外键关联
        [SugarColumn(IsNullable = true)]
        public string LessonId { get; set; }
        //评论编号
        [SugarColumn(IsNullable = true)]
        public string ViewsId { get; set;}
        //评论详情
        [SugarColumn(IsNullable = true, Length = int.MaxValue, SqlParameterDbType = "varchar(max)")]
        public string ViewsText { get; set; }
        //评论时间
        [SugarColumn(IsNullable = true, ColumnDataType = "datetime")]
        public DateTime ViewTime{ get; set;}
        //浏览日期
        [SugarColumn(IsNullable = true)]
        public DateTime ViewDate { get; set;}
        //like
        [SugarColumn(IsNullable = true)]
        public int like { get; set; }
        //回复统计
        [SugarColumn(IsNullable = true)]
        public int ReplyCount { get; set; }
    }
}
