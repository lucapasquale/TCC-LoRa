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

namespace Teste_Application
{
    public partial class Form1 : Form
    {
        public List<DataObject> dados = new List<DataObject>();

        public Form1()
        {
            InitializeComponent();
            GetData();
            ConfigureForm();
        }

        #region Private
        void GetData()
        {
            var client = new RestClient();
            client.BaseUrl = new Uri("https://artimar.orbiwise.com/rest/nodes/0004A30B001A674B/payloads/ul");
            client.Authenticator = new HttpBasicAuthenticator("maua_ceun", "Maua2016");

            var request = new RestRequest();
            IRestResponse response = client.Execute(request);

            List<DataObject> listaJSON = new List<DataObject>();
            listaJSON = JsonConvert.DeserializeObject<List<DataObject>>(response.Content);

            foreach (DataObject n in listaJSON)
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
        }

        void ConfigureForm()
        {
            grafico.ChartAreas[0].AxisX.Title = "Horário";
            grafico.ChartAreas[0].AxisX.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Hours;
            grafico.ChartAreas[0].AxisX.Interval = 1;
            grafico.ChartAreas[0].AxisX.LabelStyle.Format = "HH:mm\nd/M";
            grafico.Series[0].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastPoint;

            comboBox1.SelectedIndex = 0;

            labelAtualizacao.Text = string.Format("Última atualização: {0}", DateTime.Now);
            labelPacote.Text = string.Format("Último pacote: {0}", dados[0].horario);
            PlotGraph();
        }

        void PlotGraph()
        {
            grafico.Series[0].Points.Clear();

            switch (comboBox1.SelectedIndex)
            {
                case 0:
                    {
                        for (int x = 0; x < dados.Count; x++)
                            grafico.Series[0].Points.AddXY(dados[x].horario, dados[x].temperatura);

                        grafico.Series[0].Color = Color.Red;                      
                        grafico.ChartAreas[0].AxisY.Title = "Temperatura (ºC)";
                        grafico.ChartAreas[0].AxisY.MinorGrid.Interval = 1;
                        break;
                    }
                case 1:
                    {
                        for (int x = 0; x < dados.Count; x++)
                            grafico.Series[0].Points.AddXY(dados[x].horario, dados[x].umidade);

                        grafico.Series[0].Color = Color.Blue;
                        grafico.ChartAreas[0].AxisY.Title = "Umidade (%)";
                        grafico.ChartAreas[0].AxisY.MinorGrid.Interval = 2.5f;
                        break;
                    }
                case 2:
                    {
                        for (int x = 0; x < dados.Count; x++)
                            grafico.Series[0].Points.AddXY(dados[x].horario, dados[x].pressao);

                        grafico.Series[0].Color = Color.Green;
                        grafico.ChartAreas[0].AxisY.Title = "Pressão (hPa)";
                        grafico.ChartAreas[0].AxisY.MinorGrid.Interval = 1;
                        break;
                    }
            }
        }
        #endregion

        #region Events
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            PlotGraph();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            GetData();
            labelAtualizacao.Text = string.Format("Última atualização: {0}", DateTime.Now);
            labelPacote.Text = string.Format("Último pacote: {0}", dados[0].horario);
            PlotGraph();
        }
        #endregion
    }

    public class DataObject
    {
        public float temperatura { get; set; }
        public float umidade { get; set; }
        public int pressao { get; set; }
        public DateTime horario { get; set; }

        public int Id { get; set; }
        public string timeStamp { get; set; }
        public string dataFrame { get; set; }
        public int fcnt { get; set; }
        public int port { get; set; }
        public int rssi { get; set; }
        public float snr { get; set; }
        public int sr_used { get; set; }
        public bool decrypted { get; set; }
    }

    public class NodeObject
    {
        public string devEUI { get; set; }
        public int device_status { get; set; }
        public int dl_fcnt { get; set; }
        public int device_class { get; set; }
        public int registration_status { get; set; }
        public int expiry_time_uplink { get; set; }
        public int expiry_time_downlink { get; set; }
        public int max_allowed_dutycycle { get; set; }
        public int expected_avr_dutycycle { get; set; }
        public int quo_class { get; set; }
        public string last_reception { get; set; }
        public string appEUI { get; set; }
        public string coment { get; set; }
    }
}
