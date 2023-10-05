using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.Chapter.Dto
{
   public class ChapterRes
    {//章节id
        public int ChapterId { get; set; }
        //课程id
        public int CourseId { get; set; }
        //章节名
        public string ChapterName { get; set; }
        //章节内容
        public string ChapterContent { get; set; }
        public string Video { get; set; }
    }
}
