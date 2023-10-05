using Service.Resource.Dto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.Resource
{
    public interface IRecource
    {
        List<ResourceRes> GetRecource(RescSecReq req);
    }
}
