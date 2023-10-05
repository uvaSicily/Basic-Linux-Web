using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model.Entitys
{
    public class ti
    {
       
        //题库id
        [SugarColumn(IsNullable = false,IsPrimaryKey = true)]
        public string TestId { get; set; }
        //题库名
        [SugarColumn(IsNullable = true)]
        public string TestName { get; set; }
      
        //题库难易
        [SugarColumn(IsNullable = true)]
        public string Testtype { get; set; }
        //题库
        [SugarColumn(IsNullable = true)]
        public string Tests { get; set; }
        //题库类型
        [SugarColumn(IsNullable = true)]
        public string types{ get; set; }
    }
}
