using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SqlSugar;

namespace Model.Entitys
{
    public class Users
    {//名称
        [SugarColumn(IsNullable =true)]
        public string name { get; set; }
        //账号
        [SugarColumn(IsNullable =false,IsPrimaryKey =true)]
        public string username { get; set; }
        //密码
        [SugarColumn(IsNullable =false)]
        public string password { get; set; }
        //身份
        [SugarColumn(IsNullable =true)]
        public string usertype { get; set; }
        
    }
}
