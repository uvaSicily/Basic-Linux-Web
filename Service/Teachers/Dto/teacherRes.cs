using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.Teachers.Dto
{
    public class teacherRes
    {
        
        public string Id { get; set; }
        //教师名
        
        public string Name { get; set; }

        //是否在职
       
        public bool IsEmployed { get; set; }
        //任职学校
       
        public string School { get; set; }
        //教师头像
     
        public string teacherImage { get; set; }
        public string teacherText { get; set; }
        public string DepartId { get; set; }
        public string DepartName { get; set; }
    }
}
