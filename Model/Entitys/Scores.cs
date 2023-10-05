using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model.Entitys
{/// <summary>
/// 刷题成绩表
/// </summary>
    public class Scores
    {
        //用户id与Users外键约束
        [SugarColumn(IsNullable = true)]
        public string UserId { get; set; }
        //题库id
        [SugarColumn(IsNullable = true)]
        public string  TestId { get; set; }
       
       
        //每门成绩
        [SugarColumn(IsNullable = true)]
        public int Score { get; set; }
        //做题日期
        [SugarColumn(IsNullable = true)]
        public DateTime ScoreTime { get; set; }
    }
}
