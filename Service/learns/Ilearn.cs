using Service.learns.Dto;
using Service.persons.Dto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.learns
{
    public interface Ilearn
    {
        List<learnRes> Getlearn(learnReq req);
    }
}
