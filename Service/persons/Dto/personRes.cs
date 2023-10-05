using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.persons.Dto
{
    public class personRes
    {
       
    
        public string Name { get; set; }
      //班级
        public string Depart { get; set; }
       
        public string School { get; set; }
       //系
        public string Dept { get; set; }
       
        public string Image { get; set; }
        public string ViewsText { get; set; }
       
        public DateTime ViewTime { get; set; }
        public int like { get; set; }
      
        public int ReplyCount { get; set; }
     

    }
}
