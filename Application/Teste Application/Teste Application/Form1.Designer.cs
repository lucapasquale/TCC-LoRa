﻿namespace Teste_Application
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.grafico = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.labelNode = new System.Windows.Forms.Label();
            this.labelAtualizacao = new System.Windows.Forms.Label();
            this.labelPacote = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.graficos = new System.Windows.Forms.TabPage();
            this.data = new System.Windows.Forms.TabPage();
            this.mapa = new System.Windows.Forms.TabPage();
            this.gmap = new GMap.NET.WindowsForms.GMapControl();
            this.dataObjectBindingSource1 = new System.Windows.Forms.BindingSource(this.components);
            this.dataObjectBindingSource = new System.Windows.Forms.BindingSource(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.grafico)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.tabControl1.SuspendLayout();
            this.graficos.SuspendLayout();
            this.data.SuspendLayout();
            this.mapa.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataObjectBindingSource1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataObjectBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // grafico
            // 
            this.grafico.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            chartArea1.AxisX.IsStartedFromZero = false;
            chartArea1.AxisX.ScaleView.Size = 12D;
            chartArea1.AxisX.ScaleView.SizeType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Hours;
            chartArea1.AxisX.ScaleView.SmallScrollMinSizeType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Hours;
            chartArea1.AxisX.ScrollBar.BackColor = System.Drawing.Color.White;
            chartArea1.AxisX.ScrollBar.ButtonStyle = System.Windows.Forms.DataVisualization.Charting.ScrollBarButtonStyles.SmallScroll;
            chartArea1.AxisX.ScrollBar.IsPositionedInside = false;
            chartArea1.AxisY.Enabled = System.Windows.Forms.DataVisualization.Charting.AxisEnabled.True;
            chartArea1.AxisY.IsStartedFromZero = false;
            chartArea1.AxisY.MinorGrid.Enabled = true;
            chartArea1.AxisY.MinorGrid.LineColor = System.Drawing.Color.Silver;
            chartArea1.AxisY2.Enabled = System.Windows.Forms.DataVisualization.Charting.AxisEnabled.True;
            chartArea1.AxisY2.IsStartedFromZero = false;
            chartArea1.AxisY2.Title = "Pressão (hPa)";
            chartArea1.Name = "ChartArea1";
            this.grafico.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.grafico.Legends.Add(legend1);
            this.grafico.Location = new System.Drawing.Point(6, 3);
            this.grafico.Name = "grafico";
            series1.BorderWidth = 2;
            series1.ChartArea = "ChartArea1";
            series1.Color = System.Drawing.Color.LightGreen;
            series1.Legend = "Legend1";
            series1.Name = "Pressao";
            series2.BorderWidth = 2;
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series2.Color = System.Drawing.Color.Blue;
            series2.Legend = "Legend1";
            series2.Name = "Umidade";
            series3.BorderWidth = 2;
            series3.ChartArea = "ChartArea1";
            series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series3.Color = System.Drawing.Color.Red;
            series3.Legend = "Legend1";
            series3.Name = "Temperatura";
            this.grafico.Series.Add(series1);
            this.grafico.Series.Add(series2);
            this.grafico.Series.Add(series3);
            this.grafico.Size = new System.Drawing.Size(1136, 447);
            this.grafico.TabIndex = 0;
            this.grafico.Text = "chart1";
            // 
            // labelNode
            // 
            this.labelNode.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.labelNode.AutoSize = true;
            this.labelNode.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelNode.Location = new System.Drawing.Point(467, 5);
            this.labelNode.Name = "labelNode";
            this.labelNode.Size = new System.Drawing.Size(256, 25);
            this.labelNode.TabIndex = 3;
            this.labelNode.Text = "Node: 0004A30B001A674B";
            // 
            // labelAtualizacao
            // 
            this.labelAtualizacao.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.labelAtualizacao.AutoSize = true;
            this.labelAtualizacao.Location = new System.Drawing.Point(962, 9);
            this.labelAtualizacao.Name = "labelAtualizacao";
            this.labelAtualizacao.Size = new System.Drawing.Size(202, 13);
            this.labelAtualizacao.TabIndex = 4;
            this.labelAtualizacao.Text = "Ultima atualização: 01/02/2016 01:02:03";
            // 
            // labelPacote
            // 
            this.labelPacote.AutoSize = true;
            this.labelPacote.Location = new System.Drawing.Point(9, 5);
            this.labelPacote.Name = "labelPacote";
            this.labelPacote.Size = new System.Drawing.Size(181, 13);
            this.labelPacote.TabIndex = 5;
            this.labelPacote.Text = "Ultimo pacote: 01/02/2016 01:02:03";
            // 
            // button1
            // 
            this.button1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button1.Location = new System.Drawing.Point(881, 4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 7;
            this.button1.Text = "Atualizar";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // dataGridView1
            // 
            this.dataGridView1.AllowUserToAddRows = false;
            this.dataGridView1.AllowUserToDeleteRows = false;
            this.dataGridView1.AllowUserToOrderColumns = true;
            this.dataGridView1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dataGridView1.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(6, 6);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.ReadOnly = true;
            this.dataGridView1.Size = new System.Drawing.Size(1136, 439);
            this.dataGridView1.TabIndex = 8;
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(0, 0);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(200, 100);
            this.tabPage2.TabIndex = 0;
            this.tabPage2.Text = "tabPage2";
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.mapa);
            this.tabControl1.Controls.Add(this.graficos);
            this.tabControl1.Controls.Add(this.data);
            this.tabControl1.Location = new System.Drawing.Point(12, 33);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(1156, 482);
            this.tabControl1.SizeMode = System.Windows.Forms.TabSizeMode.Fixed;
            this.tabControl1.TabIndex = 9;
            // 
            // graficos
            // 
            this.graficos.Controls.Add(this.grafico);
            this.graficos.Location = new System.Drawing.Point(4, 22);
            this.graficos.Name = "graficos";
            this.graficos.Padding = new System.Windows.Forms.Padding(3);
            this.graficos.Size = new System.Drawing.Size(1148, 456);
            this.graficos.TabIndex = 0;
            this.graficos.Text = "Gráficos";
            this.graficos.UseVisualStyleBackColor = true;
            // 
            // data
            // 
            this.data.Controls.Add(this.dataGridView1);
            this.data.Location = new System.Drawing.Point(4, 22);
            this.data.Name = "data";
            this.data.Padding = new System.Windows.Forms.Padding(3);
            this.data.Size = new System.Drawing.Size(1148, 456);
            this.data.TabIndex = 1;
            this.data.Text = "Data";
            this.data.UseVisualStyleBackColor = true;
            // 
            // mapa
            // 
            this.mapa.Controls.Add(this.gmap);
            this.mapa.Location = new System.Drawing.Point(4, 22);
            this.mapa.Name = "mapa";
            this.mapa.Size = new System.Drawing.Size(1148, 456);
            this.mapa.TabIndex = 2;
            this.mapa.Text = "Mapa";
            this.mapa.UseVisualStyleBackColor = true;
            // 
            // gmap
            // 
            this.gmap.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.gmap.Bearing = 0F;
            this.gmap.CanDragMap = true;
            this.gmap.EmptyTileColor = System.Drawing.Color.Navy;
            this.gmap.GrayScaleMode = false;
            this.gmap.HelperLineOption = GMap.NET.WindowsForms.HelperLineOptions.DontShow;
            this.gmap.LevelsKeepInMemmory = 5;
            this.gmap.Location = new System.Drawing.Point(3, 3);
            this.gmap.MarkersEnabled = true;
            this.gmap.MaxZoom = 18;
            this.gmap.MinZoom = 2;
            this.gmap.MouseWheelZoomType = GMap.NET.MouseWheelZoomType.MousePositionAndCenter;
            this.gmap.Name = "gmap";
            this.gmap.NegativeMode = false;
            this.gmap.PolygonsEnabled = true;
            this.gmap.RetryLoadTile = 0;
            this.gmap.RoutesEnabled = true;
            this.gmap.ScaleMode = GMap.NET.WindowsForms.ScaleModes.Integer;
            this.gmap.SelectedAreaFillColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(65)))), ((int)(((byte)(105)))), ((int)(((byte)(225)))));
            this.gmap.ShowTileGridLines = false;
            this.gmap.Size = new System.Drawing.Size(1142, 450);
            this.gmap.TabIndex = 0;
            this.gmap.Zoom = 16D;
            // 
            // dataObjectBindingSource1
            // 
            this.dataObjectBindingSource1.DataSource = typeof(Teste_Application.ClimateObject);
            // 
            // dataObjectBindingSource
            // 
            this.dataObjectBindingSource.DataSource = typeof(Teste_Application.DataObject);
            // 
            // Form1
            // 
            this.ClientSize = new System.Drawing.Size(1180, 527);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.labelPacote);
            this.Controls.Add(this.labelAtualizacao);
            this.Controls.Add(this.labelNode);
            this.Name = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.grafico)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.tabControl1.ResumeLayout(false);
            this.graficos.ResumeLayout(false);
            this.data.ResumeLayout(false);
            this.mapa.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataObjectBindingSource1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataObjectBindingSource)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataVisualization.Charting.Chart grafico;
        private System.Windows.Forms.Label labelNode;
        private System.Windows.Forms.Label labelAtualizacao;
        private System.Windows.Forms.Label labelPacote;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.BindingSource dataObjectBindingSource;
        private System.Windows.Forms.BindingSource dataObjectBindingSource1;
        private System.Windows.Forms.TabPage data;
        private System.Windows.Forms.TabPage graficos;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage mapa;
        private GMap.NET.WindowsForms.GMapControl gmap;
    }
}

