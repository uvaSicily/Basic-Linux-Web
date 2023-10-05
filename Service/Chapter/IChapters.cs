using Service.Chapter.Dto;
using Service.Depart.Dto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.Chapter
{
    public interface IChapters
    {
        List<ChapterRes> GetChapter(ChapterReqs req);
    }
}
