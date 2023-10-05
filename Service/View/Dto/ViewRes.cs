using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.View.Dto
{
    public class ViewRes
    {
      
        public string UserId { get; set; }

        //课程id与lesson外键关联
    
        public string LessonId { get; set; }
        //评论编号
      
        public string ViewsId { get; set; }
        //评论详情
     
        public string ViewsText { get; set; }
        //评论时间

        public DateTime ViewTime { get; set; }
        //浏览日期

        public DateTime ViewDate { get; set; }
        //like
    
        public int like { get; set; }
        //回复统计
 
        public int ReplyCount { get; set; }
        public string Name { get; set; }
        public string Image { get; set; }
    }
}
