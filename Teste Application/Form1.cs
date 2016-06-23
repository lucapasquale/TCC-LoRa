using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using RestSharp;
using RestSharp.Authenticators;
using Newtonsoft.Json;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public List<JsonObject> dados = new List<JsonObject>();

        public Form1()
        {
            InitializeComponent();

            GetJsonObjects();

            for (int n = 0; n < numericUpDown1.Value; n++)
            {
                chart2.Series["Temperatura"].Points.AddXY(dados[n].horario, dados[n].temperatura);
            }


        }

        void GetJsonObjects()
        {
            var client = new RestClient();
            client.BaseUrl = new Uri("https://artimar.orbiwise.com/rest/nodes/0004A30B001A674B/payloads/ul");
            client.Authenticator = new HttpBasicAuthenticator("maua_ceun", "Maua2016");

            var request = new RestRequest();
            IRestResponse response = client.Execute(request);

            List<JsonObject> listaJSON = new List<JsonObject>();
            listaJSON = JsonConvert.DeserializeObject<List<JsonObject>>(response.Content);

            foreach (JsonObject n in listaJSON)
            {
                n.horario = DateTime.Parse(n.timeStamp);

                byte[] data = Convert.FromBase64String(n.dataFrame);
                n.dataFrame = BitConverter.ToString(data).Replace("-", string.Empty);

                n.temperatura = int.Parse(n.dataFrame.Substring(0, 4), System.Globalization.NumberStyles.HexNumber) / 10f;
                n.umidade = int.Parse(n.dataFrame.Substring(4, 4), System.Globalization.NumberStyles.HexNumber) / 10f;
                n.pressao = int.Parse(n.dataFrame.Substring(8, 4), System.Globalization.NumberStyles.HexNumber);
            }

            dados = listaJSON.OrderByDescending(o => o.horario).ToList();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            chart2.Series[0].Points.Clear();
            for (int n = 0; n < numericUpDown1.Value; n++)
            {
                chart2.Series["Temperatura"].Points.AddXY(dados[n].horario, dados[n].temperatura);
            }
        }
    }

    public class JsonObject
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
}
