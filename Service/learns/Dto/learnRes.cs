using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.learns.Dto
{
    public class learnRes
    {
        public int LessonTime { get; set; }

       
        public int LessonId { get; set; }

      
        public string Note { get; set; }

       
        public DateTime NoteTime { get; set; }
        
        public string Learing { get; set; }
      
        public string Leared { get; set; }
    
        public int like { get; set; }
        public int ReplyCount { get; set;}
    }
}
