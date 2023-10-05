using Service.Depart.Dto;
using Service.View.Dto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.View
{
   public interface Iviews
    {
        List<ViewRes> GetViews(ViewReq req);
    }
}
