using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model
{
   public class ApiResult
    {
        public bool IsSuccess { get; set; }//api结果是否成功
        public object Result { get; set; }//结构
        public string Msg { get; set; }//异常记录
        public string type { get; set; }

    }
}
