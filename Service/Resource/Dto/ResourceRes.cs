using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.Resource.Dto
{
    public class ResourceRes
    {
       
        public string ResourceId { get; set; }
        //课程id
        public int LessonId { get; set; }
        //资源类型
        public string ResourceType { get; set; }
        //资源名
    
        public string ResourceName { get; set; }
        //上传时间
        public DateTime Uptime { get; set; }
        //上传人
        public string Upuser { get; set; }

    }
}
