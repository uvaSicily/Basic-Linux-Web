using Service.Chapter.Dto;
using Service.persons.Dto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.persons
{
    public interface Iperson
    {
        List<personRes> GetPerson(personReq req);
    }
}
