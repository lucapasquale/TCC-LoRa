using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OxyPlot;
using OxyPlot.Series;

namespace WpfApplication1
{
    public class MainViewModel
    {
        public PlotModel ModelTemp { get; private set; }
        public PlotModel ModelUmid { get; private set; }

        public LineSeries retaTemp = new LineSeries();
        public LineSeries retaUmid = new LineSeries();


        public MainViewModel()
        {
            this.ModelTemp = new PlotModel { Title = "Temperatura" };
            this.ModelUmid = new PlotModel { Title = "Umidade" };
        }

        public void Plot()
        {
            this.ModelUmid.Series.Add(retaTemp);
            this.ModelUmid.Series.Add(retaUmid);
        }

    }
}
