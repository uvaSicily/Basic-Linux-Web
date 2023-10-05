using AutoMapper;
using Microsoft.EntityFrameworkCore;
using Common;
using Model.Entitys;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SqlSugar;
using Microsoft.Data.SqlClient;

namespace Service
{
    public class lessonService : Serices   //实现继承抽象
    {
        private readonly IMapper _mapper;
        public lessonService(IMapper mapper)
        {
            _mapper = mapper;
        }



        public List<lessonRes> GetLessons(lessonReq req)
        {
            List<lesson> res = new List<lesson>();

            string connectionString = "data source=LAPTOP-HSQGJ7CB;initial catalog=linuxdo;integrated security=sspi;MultipleActiveResultSets=True";

            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                SqlCommand command = connection.CreateCommand();
                command.CommandText = "SELECT * FROM lesson WHERE LessonName=@LessonName";
                command.Parameters.AddWithValue("@LessonName", req.LessonName);

                connection.Open();

                SqlDataReader reader = command.ExecuteReader();

                while (reader.Read())
                {
                    lesson l = new lesson();
                    l.Id = Convert.ToInt32(reader["Id"]);
                    l.LessonName = Convert.ToString(reader["LessonName"]);
                    l.LessonImage = Convert.ToString(reader["LessonImage"]);
                    l.LessonText= Convert.ToString(reader["LessonText"]);
                    l.LessonTip = Convert.ToString(reader["LessonTip"]);
                    l.LessonWarn= Convert.ToString(reader["LessonWarn"]);
                    l.LessonTeacher= Convert.ToString(reader["LessonTeacher"]);
                    l.LessonVideo= Convert.ToString(reader["LessonVideo"]);
                    l.LessonDis= Convert.ToString(reader["LessonDis"]);
                    // 其他属性

                    res.Add(l);
                }

                reader.Close();
            }

            return _mapper.Map<List<lessonRes>>(res);
        }


    }
}
