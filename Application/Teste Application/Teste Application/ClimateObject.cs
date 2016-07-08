using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Teste_Application
{
    public class ClimateObject : DataObject
    {
        public float temperatura { get; set; }
        public float umidade { get; set; }
        public int pressao { get; set; }
        public DateTime horario { get; set; }
    }
}
