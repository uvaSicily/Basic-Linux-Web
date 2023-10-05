using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model.Entitys
{
    // 定义Resources类，映射到数据库中的resources表格
    public class Resources
    {//编号
        [SugarColumn(IsPrimaryKey = true)]
        public string ResourceId { get; set; }
        //课程id
        [SugarColumn(IsNullable = true)]
        public int LessonId { get; set; }
        //资源类型
        [SugarColumn(IsNullable = true)]
        public string ResourceType { get; set; }
        //资源名
        [SugarColumn(IsNullable = true)]
        public string ResourceName { get; set; }
        //上传时间
        [SugarColumn(IsNullable = true)]
        public DateTime Uptime{ get; set; }
        //上传人
        [SugarColumn(IsNullable = true)]
        public string Upuser { get; set; }
    }


}
