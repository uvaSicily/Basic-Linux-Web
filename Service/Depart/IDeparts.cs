using Service.Depart.Dto;
using Service.Teachers.Dto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.Depart
{
    public interface IDeparts
    {
        List<DepartRes> GetDeparts(DpartReq req);
    }
}
