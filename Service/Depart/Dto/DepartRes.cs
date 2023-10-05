using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.Depart.Dto
{
   public class DepartRes
    {
      
        public string DepartId { get; set; }
        //教师id
      
        public string teacherId { get; set; }
        //班级名
        
        public string DepartName { get; set; }
    }
}
