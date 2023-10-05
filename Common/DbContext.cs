using Microsoft.EntityFrameworkCore;
using Model.Entitys;
using SqlSugar;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;


namespace Common
{
    public class DbContext
    {
        
            private static readonly ConcurrentBag<SqlSugarClient> ConnectionPool = new ConcurrentBag<SqlSugarClient>();

            // 创建 SqlSugarClient 对象时加入连接池
            static DbContext()
            {
                for (int i = 0; i < 10; i++)
                {
                    ConnectionPool.Add(CreateDbClient());
                }
            }

            private static SqlSugarClient CreateDbClient()
            {
                return new SqlSugarClient(new ConnectionConfig()
                {
                    ConnectionString = "data source=LAPTOP-HSQGJ7CB;initial catalog=linuxdo;integrated security=sspi",
                    DbType = SqlSugar.DbType.SqlServer,
                    IsAutoCloseConnection = true
                });
            }

            // 使用连接池获取 SqlSugarClient 对象
            public static SqlSugarClient GetDbClient()
            {
                if (ConnectionPool.TryTake(out var conn))
                {
                    return conn;
                }
                else
                {
                    return CreateDbClient();
                }
            }

            // 结束时将连接放回连接池中
            public static void Close(SqlSugarClient conn)
            {
                ConnectionPool.Add(conn);
            }

            public static void InitDataBase()
            {
                using var db = GetDbClient();

                db.DbMaintenance.CreateDatabase();//初始化数据库，没有数据库则建立
                                                  //创建表
                string nspace = "Model.Entitys";
                Type[] ass = Assembly.LoadFrom("../Model/bin/Debug/net6.0/Model.dll").GetTypes().Where(p => p.Namespace == nspace).ToArray();
                db.CodeFirst.SetStringDefaultLength(200).InitTables(ass);
            }
         /*   //测试
            List<Users> users = new List<Users>()
            {
                new Users()
                {
                  username = "2013",
                  password = "12345"

                }
    };
    db.Insertable(users).ExecuteCommand();*/

            //测试数据
      /*         List<lesson> lesson = new List<lesson>()
               {
                   new lesson()
                   {
                      Id=12,LessonText=" 我们处于并发处理的时代，进程，线程，协程等编程，逐渐成为基本技能，其中涉及资源的竞争和共享，死锁等问题，都是OS课程所要讲述的；OS对软硬件的资源管理是它的主要功能，通过对资源管理的学习，可以使大家能够在许多其他场合重用这一模式；当系统或者程序出现性能问题，或者当系统出现冲突时，要深入到系统看看如何进行处理，这样，对操作系统原理的掌握就显得弥足珍贵。",
                       LessonName="Linux操作系统及内核",
                       LessonImage="/image/linux操作.webp",
                       LessonTip="面向有一定 Linux 与 C 编程基础的用户，推荐用户进行实验之前先学习理论课程。",
                       LessonTeacher="李老师",

                   },
                    new lesson()
                   {
                      Id=11,LessonText="MongoDB是一个基于分布式文件存储的数据库。由C++语言编写。旨在为WEB应用提供可扩展的高性能数据存储解决方案。 MongoDB是一个介于关系数据库和非关系数据库之间的产品，是非关系数据库当中功能最丰富，最像关系数据库的。它支持的数据结构非常松散，是类似json的bson格式，因此可以存储比较复杂的数据类型。Mongo最大的特点是它支持的查询语言非常强大，其语法有点类似于面向对象的查询语言，几乎可以实现类似关系数据库单表查询的绝大部分功能，而且还支持对数据建立索引。\r\n\r\n",
                       LessonName="MongoDB基础",
                       LessonImage="/image/MongoDB.png",
                       LessonTip="本课程是 MongoDB 基础教程，介绍了 MongoDB 基本的集合操作、高级查询以及索引与聚合。",
                       LessonTeacher="谭老师",

                   }
               };
             db.Insertable(lesson).ExecuteCommand();*/
        
        
    }
}
