using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model.Entitys
{
    // 定义Chapters类，映射到数据库中的chapters表格
    public class Chapters
    {//章节id
        [SugarColumn(IsNullable = true)]
        public int ChapterId { get; set; }
        //课程id
        [SugarColumn(IsNullable = true)]
        public int CourseId { get; set; }
        //章节名
        [SugarColumn(IsNullable = true)]
        public string ChapterName { get; set; }
        //章节内容
        [SugarColumn(IsNullable = true)]
        public string ChapterContent { get; set; }
        [SugarColumn(IsNullable = true)]
        public string Video { get; set;}
    }

   

}
