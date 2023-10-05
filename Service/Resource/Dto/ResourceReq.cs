using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.Resource.Dto
{
    public class ResourceModel
    {
        public int Id { get; set; }
        public string LessonName { get; set; }
        public string TeacherName { get; set; }
        public string LessonType { get; set; }
        public string ResourceId { get; set; }
        public string ResourceName { get; set; }
        public string lessonTip { get; set; }
        public string DepartDis { get; set; }
    }
}
