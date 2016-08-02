using Newtonsoft.Json;
using RestSharp;
using RestSharp.Authenticators;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using GMap.NET;
using GMap.NET.WindowsForms;
using GMap.NET.WindowsForms.Markers;

namespace Teste_Application
{
    public partial class Form1 : Form
    {
        public List<ClimateObject> dados = new List<ClimateObject>();
        GMapOverlay markersOverlay = new GMapOverlay("markers");

        public Form1()
        {
            InitializeComponent();
            GetData();
            ConfigureForm();

            //Configura mapa
            gmap.MapProvider = GMap.NET.MapProviders.BingMapProvider.Instance;
            GMap.NET.GMaps.Instance.Mode = GMap.NET.AccessMode.ServerOnly;
            gmap.Position = new PointLatLng(-23.6490855, -46.5742101);
            gmap.Overlays.Add(markersOverlay);
        }

        #region Private
        void GetData()
        {
            string acc = "maua_ceun";
            string pass = "Maua2016";
            string node = "0004A30B001A674B";

            var client = new RestClient();
            client.BaseUrl = new Uri("https://artimar.orbiwise.com/rest/nodes/" + node + "/payloads/ul");
            client.Authenticator = new HttpBasicAuthenticator(acc, pass);

            var request = new RestRequest();
            IRestResponse response = client.Execute(request);

            List<ClimateObject> listaJSON = new List<ClimateObject>();
            listaJSON = JsonConvert.DeserializeObject<List<ClimateObject>>(response.Content);

            foreach (ClimateObject n in listaJSON)
            {
                //Pega o horario em DateTime
                n.horario = DateTime.Parse(n.timeStamp);

                //Passa de base64 para HEX e remove os '-' entre os bytes
                byte[] data = Convert.FromBase64String(n.dataFrame);
                n.dataFrame = BitConverter.ToString(data).Replace("-", string.Empty);

                //Converte de HEX para decimal
                n.temperatura = int.Parse(n.dataFrame.Substring(0, 4), System.Globalization.NumberStyles.HexNumber) / 10f;
                n.umidade = int.Parse(n.dataFrame.Substring(4, 4), System.Globalization.NumberStyles.HexNumber) / 10f;
                n.pressao = int.Parse(n.dataFrame.Substring(8, 4), System.Globalization.NumberStyles.HexNumber);
            }
            dados = listaJSON.OrderByDescending(o => o.horario).ToList();

            //Adiciona marker no mapa
            markersOverlay.Clear();
               
            GMarkerGoogle marker = new GMarkerGoogle(new PointLatLng(-23.6490855, -46.5742101), GMarkerGoogleType.blue);
            marker.ToolTip = new GMapToolTip(marker);
            marker.ToolTipText = String.Format("Dia: {0}/{1}\nHora: {2}:{3}\nTemp: {4} ºC\nUmid: {5} %\nPres: {6} hPa",
                dados[0].horario.Day, dados[0].horario.Month, dados[0].horario.Hour, dados[0].horario.Minute, dados[0].temperatura, dados[0].umidade, dados[0].pressao);
            markersOverlay.Markers.Add(marker);
        }

        void ConfigureForm()
        {
            PlotValues();

            grafico.ChartAreas[0].AxisX.Title = "Horário";
            grafico.ChartAreas[0].AxisX.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Hours;
            grafico.ChartAreas[0].AxisX.Interval = 1;
            grafico.ChartAreas[0].AxisX.LabelStyle.Format = "HH:mm\nd/M";

            // Set custom chart area position
            grafico.ChartAreas[0].Position = new ElementPosition(16, 5, 85, 90);
            grafico.ChartAreas[0].InnerPlotPosition = new ElementPosition(0, 0, 90, 75);

            // Create extra Y axis for second and third series
            CreateYAxis(grafico, grafico.ChartAreas[0], grafico.Series["Temperatura"], 10, 8, "Temperatura (ºC)");
            CreateYAxis(grafico, grafico.ChartAreas[0], grafico.Series["Umidade"], 16, 8, "Umidade (%)");

            labelAtualizacao.Text = string.Format("Última atualização: {0}", DateTime.Now);
            labelPacote.Text = string.Format("Último pacote: {0}", dados[0].horario);

            // Configura o dataGrid
            var list = new BindingList<ClimateObject>(dados);
            dataGridView1.DataSource = list;
        }

        void PlotValues()
        {
            for (int n = 0; n < grafico.Series.Count; n++)
                grafico.Series[n].Points.Clear();

            for (int x = 0; x < dados.Count; x++)
            {
                grafico.Series["Umidade"].Points.AddXY(dados[x].horario, dados[x].umidade);
                grafico.Series["Temperatura"].Points.AddXY(dados[x].horario, dados[x].temperatura);
                grafico.Series["Pressao"].Points.AddXY(dados[x].horario, dados[x].pressao);
            }
        }
        #endregion

        #region Events
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            PlotValues();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            GetData();
            labelAtualizacao.Text = string.Format("Última atualização: {0}", DateTime.Now);
            labelPacote.Text = string.Format("Último pacote: {0}", dados[0].horario);
            PlotValues();
        }
        #endregion  

        /// <summary>
        /// Creates Y axis for the specified series.
        /// </summary>
        /// <param name="chart">Chart control.</param>
        /// <param name="area">Original chart area.</param>
        /// <param name="series">Series.</param>
        /// <param name="axisOffset">New Y axis offset in relative coordinates.</param>
        /// <param name="labelsSize">Extra space for new Y axis labels in relative coordinates.</param>
        public void CreateYAxis(Chart chart, ChartArea area, Series series, float axisOffset, float labelsSize, string title)
        {
            // Create new chart area for original series
            ChartArea areaSeries = chart.ChartAreas.Add("ChartArea_" + series.Name);
            areaSeries.BackColor = Color.Transparent;
            areaSeries.BorderColor = Color.Transparent;
            areaSeries.Position.FromRectangleF(area.Position.ToRectangleF());
            areaSeries.InnerPlotPosition.FromRectangleF(area.InnerPlotPosition.ToRectangleF());
            areaSeries.AxisX.MajorGrid.Enabled = false;
            areaSeries.AxisX.MajorTickMark.Enabled = false;
            areaSeries.AxisX.LabelStyle.Enabled = false;
            areaSeries.AxisY.MajorGrid.Enabled = false;
            areaSeries.AxisY.MajorTickMark.Enabled = false;
            areaSeries.AxisY.LabelStyle.Enabled = false;
            areaSeries.AxisY.IsStartedFromZero = area.AxisY.IsStartedFromZero;

            areaSeries.AxisX.ScaleView = area.AxisX.ScaleView;
            areaSeries.AxisX.ScrollBar.Enabled = false;

            series.ChartArea = areaSeries.Name;

            // Create new chart area for axis
            ChartArea areaAxis = chart.ChartAreas.Add("AxisY_" + series.ChartArea);
            areaAxis.BackColor = Color.Transparent;
            areaAxis.BorderColor = Color.Transparent;
            areaAxis.Position.FromRectangleF(chart.ChartAreas[series.ChartArea].Position.ToRectangleF());
            areaAxis.InnerPlotPosition.FromRectangleF(chart.ChartAreas[series.ChartArea].InnerPlotPosition.ToRectangleF());

            // Create a copy of specified series
            Series seriesCopy = chart.Series.Add(series.Name + "_Copy");
            seriesCopy.ChartType = series.ChartType;
            foreach (DataPoint point in series.Points)
            {
                seriesCopy.Points.AddXY(point.XValue, point.YValues[0]);
            }

            // Hide copied series
            seriesCopy.IsVisibleInLegend = false;
            seriesCopy.Color = Color.Transparent;
            seriesCopy.BorderColor = Color.Transparent;
            seriesCopy.ChartArea = areaAxis.Name;

            // Disable grid lines & tickmarks
            areaAxis.AxisX.LineWidth = 0;
            areaAxis.AxisX.MajorGrid.Enabled = false;
            areaAxis.AxisX.MajorTickMark.Enabled = false;
            areaAxis.AxisX.LabelStyle.Enabled = false;
            areaAxis.AxisY.MajorGrid.Enabled = false;
            areaAxis.AxisY.IsStartedFromZero = area.AxisY.IsStartedFromZero;

            // Adjust area position
            areaAxis.Position.X -= axisOffset;
            areaAxis.InnerPlotPosition.X += labelsSize;

            //Configura titulo e numero de intervalos
            areaAxis.AxisY.Title = title;
        }
    }
}
