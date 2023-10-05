using AutoMapper;
using Microsoft.Data.SqlClient;
using Model.Entitys;
using Service.Chapter.Dto;
using Service.Teachers.Dto;
using SqlSugar;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.Chapter
{
   public class ChapterSer:IChapters
    {
        private readonly IMapper _mapper;
        public ChapterSer(IMapper mapper)
        {
            _mapper = mapper;
        }
        public List<ChapterRes> GetChapter(ChapterReqs req)
        {
            List<ChapterRes> result = new List<ChapterRes>();

            string connectionString = "data source=LAPTOP-HSQGJ7CB;initial catalog=linuxdo;integrated security=sspi;MultipleActiveResultSets=True";

            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                SqlCommand command = connection.CreateCommand();
                command.CommandText = "SELECT ChapterId, CourseId, ChapterName, ChapterContent,video FROM Chapters WHERE CourseId=@CourseId ORDER BY ChapterId ASC";//升序   DESC降序
                command.Parameters.AddWithValue("@CourseId", req.Id);

                connection.Open();

                SqlDataReader reader = command.ExecuteReader();

                while (reader.Read())
                {
                    ChapterRes chapter = new ChapterRes();
                    chapter.ChapterId = Convert.ToInt32(reader["ChapterId"]);
                    chapter.CourseId = Convert.ToInt32(reader["CourseId"]);
                    chapter.ChapterName = reader["ChapterName"].ToString();
                    chapter.ChapterContent = reader["ChapterContent"].ToString();
                     chapter.Video= reader["Video"].ToString();
                    result.Add(chapter);
                }

                reader.Close();
            }

            return result;
        }

    }
}
