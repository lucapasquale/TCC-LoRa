using RestSharp;
using RestSharp.Authenticators;
using Newtonsoft.Json;
using OxyPlot.Xamarin.Android;
using OxyPlot;
using OxyPlot.Axes;
using OxyPlot.Series;

using System;
using System.Collections.Generic;
using Android.App;
using Android.Content;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Android.OS;
using System.Linq;

namespace AndroidLoRa
{
    [Activity(Label = "AndroidLoRa", MainLauncher = true, Icon = "@drawable/icon")]
    public class MainActivity : Activity
    {
        List<RxObj> dados = new List<RxObj>();
        string acc = "maua_ceun";
        string pass = "Maua2016";

        protected override void OnCreate(Bundle bundle)
        {
            base.OnCreate(bundle);
            SetContentView(Resource.Layout.Main);

            PlotView view = FindViewById<PlotView>(Resource.Id.plot_view);
            view.Model = CreatePlotModel();
        }

        private void GetData()
        {
            string node = "0004A30B001A674B";

            var client = new RestClient();
            client.BaseUrl = new Uri("https://artimar.orbiwise.com/rest/nodes/" + node + "/payloads/ul");
            client.Authenticator = new HttpBasicAuthenticator(acc, pass);

            var request = new RestRequest();
            IRestResponse response = client.Execute(request);

            List<RxObj> listaJSON = JsonConvert.DeserializeObject<List<RxObj>>(response.Content);
            foreach (RxObj rx in listaJSON)
            {
                //Pega o horario em DateTime
                rx.horario = DateTime.Parse(rx.timeStamp);

                //Passa de base64 para HEX e remove os '-' entre os bytes
                byte[] data = Convert.FromBase64String(rx.dataFrame);
                rx.dataFrame = BitConverter.ToString(data).Replace("-", string.Empty);

                //Converte de HEX para decimal
                rx.temperatura = int.Parse(rx.dataFrame.Substring(0, 4), System.Globalization.NumberStyles.HexNumber) / 10f;
                rx.umidade = int.Parse(rx.dataFrame.Substring(4, 4), System.Globalization.NumberStyles.HexNumber) / 10f;
                rx.pressao = int.Parse(rx.dataFrame.Substring(8, 4), System.Globalization.NumberStyles.HexNumber);
            }
            dados = listaJSON.OrderByDescending(o => o.horario).ToList();
            dados.Add(new RxObj() { temperatura = 15, horario = DateTime.Now });
        }

        private PlotModel CreatePlotModel()
        {
            var plotModel = new PlotModel { Title = "OxyPlot Demo" };

            LinearAxis xAxis = new DateTimeAxis();
            xAxis.Position = AxisPosition.Bottom;
            xAxis.Title = "Time (hours)";
            xAxis.StringFormat = "HH:mm.ss";


            LinearAxis yAxis = new LinearAxis();
            yAxis.Position = AxisPosition.Left;
            yAxis.Title = "Values";

            var series1 = new LineSeries
            {
                MarkerType = MarkerType.Circle,
                MarkerSize = 4,
                MarkerStroke = OxyColors.White
            };

            series1.Points.Add(new DataPoint(DateTimeAxis.ToDouble(DateTime.Now.AddHours(0)), 0.0));
            series1.Points.Add(new DataPoint(DateTimeAxis.ToDouble(DateTime.Now.AddHours(1)), 1.4));
            series1.Points.Add(new DataPoint(DateTimeAxis.ToDouble(DateTime.Now.AddHours(2)), 2.0));
            series1.Points.Add(new DataPoint(DateTimeAxis.ToDouble(DateTime.Now.AddHours(3)), 3.3));
            series1.Points.Add(new DataPoint(DateTimeAxis.ToDouble(DateTime.Now.AddHours(4)), 4.7));
            series1.Points.Add(new DataPoint(DateTimeAxis.ToDouble(DateTime.Now.AddHours(5)), 6.0));
            series1.Points.Add(new DataPoint(DateTimeAxis.ToDouble(DateTime.Now.AddHours(6)), 8.9));

            plotModel.Series.Add(series1);

            return plotModel;
        }
    }
}

