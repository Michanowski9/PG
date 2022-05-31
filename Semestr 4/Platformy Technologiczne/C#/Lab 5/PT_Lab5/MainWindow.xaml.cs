using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace PT_Lab5
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly string[] HostNames = { "www.microsoft.com", "www.apple.com",
            "www.google.com", "www.ibm.com", "cisco.netacad.net",
            "www.oracle.com", "www.nokia.com", "www.hp.com", "www.dell.com",
            "www.samsung.com", "www.toshiba.com", "www.siemens.com",
            "www.amazon.com", "www.sony.com", "www.canon.com", "www.alcatel-lucent.com",
            "www.acer.com", "www.motorola.com" };
        BackgroundWorker backgroundWorker = null;
        public MainWindow()
        {
            InitializeComponent();
        }

        private void ButtonNewtonSymbolTasks(object sender, RoutedEventArgs e)
        {
            int n;
            int k;
            
            if (!Int32.TryParse(InputK.Text, out k) || !Int32.TryParse(InputN.Text, out n))
            {
                System.Windows.MessageBox.Show("Wrong input", "Error");
                return;
            }
            
            var result = getNewtonSymbolTask(n, k);
            
            if(result == null)
            {
                System.Windows.MessageBox.Show("Something went wrong", "Error");
                return;
            }

            OutputTasks.Text = result.ToString();
        }
        private void ButtonNewtonSymbolDelegates(object sender, RoutedEventArgs e)
        {
            int n;
            int k;

            if (!Int32.TryParse(InputK.Text, out k) || !Int32.TryParse(InputN.Text, out n))
            {
                System.Windows.MessageBox.Show("Wrong input", "Error");
                return;
            }

            var result = getNewtonSymbolDelegats(n, k);

            if (result == null)
            {
                System.Windows.MessageBox.Show("Something went wrong", "Error");
                return;
            }

            OutputDelegates.Text = result.ToString();
        }
        private async void ButtonNewtonSymbolAwait(object sender, RoutedEventArgs e)
        {
            int n;
            int k;

            if (!Int32.TryParse(InputK.Text, out k) || !Int32.TryParse(InputN.Text, out n))
            {
                System.Windows.MessageBox.Show("Wrong input", "Error");
                return;
            }

            var result = await getNewtonSymbolAsync(n, k);

            if (result == null)
            {
                System.Windows.MessageBox.Show("Something went wrong", "Error");
                return;
            }

            OutputAsync.Text = result.ToString();
        }
        private void ButtonFibonacci(object sender, RoutedEventArgs e)
        {
            int i;
            if (!Int32.TryParse(InputFibonacci.Text, out i))
            {
                System.Windows.MessageBox.Show("Wrong input", "Error");
                return;
            }

            backgroundWorker = new BackgroundWorker();
            backgroundWorker.DoWork += ((object sender, DoWorkEventArgs e) => {
                    var worker = sender as BackgroundWorker;

                    if (worker == null)
                    {
                        return;
                    }

                    worker.WorkerReportsProgress = true;
                    e.Result = getFibonacci((int)e.Argument, e);
                });
            backgroundWorker.ProgressChanged += ((object sender, ProgressChangedEventArgs e) => {
                    ProgressBar.Value = e.ProgressPercentage; 
                });
            backgroundWorker.RunWorkerCompleted += ((object sender, RunWorkerCompletedEventArgs e) => {
                    if (e.Result == null)
                    {
                        return;
                    }
                    OutputFibonacci.Text = e.Result.ToString();
                });
            backgroundWorker.WorkerSupportsCancellation = true;
            ProgressBar.Value = 0;
            backgroundWorker.RunWorkerAsync(i);
        }
        private void ButtonCancelFibonacci(object sender, RoutedEventArgs e)
        {
            if(backgroundWorker == null)
            {
                return;
            }
            backgroundWorker.CancelAsync();
        }
        private void ButtonCompress(object sender, RoutedEventArgs e)
        {
            
        }
        private void ButtonDecompress(object sender, RoutedEventArgs e)
        {
            
        }
        private void ButtonResolve(object sender, RoutedEventArgs e)
        {
            var domainList = getHostNames();

            OutputDomains.Text = "";
            foreach (var domain in domainList)
            {
                OutputDomains.Text += domain.Item1 + " => " + domain.Item2 + "\n";
            }
        }


        private List<Tuple<string, string>> getHostNames()
        {
            var result = new List<Tuple<string, string>>();
            HostNames.AsParallel().ForAll((host) => {
                    lock (result)
                    {
                        result.Add(Tuple.Create(host, Dns.GetHostAddresses(host).First().ToString()));
                    }
                });
            return result;
        }


        private ulong? getFibonacci(int n, DoWorkEventArgs e)
        {
            if(n < 0)
            {
                return 0;
            }
            ulong result = 0;

            ulong temp_2 = 0;
            ulong temp_1 = 1;

            for(int i = 2, lastProgress = 0; i < n; i++)
            {
                result = temp_1 + temp_2;

                temp_2 = temp_1;
                temp_1 = result;

                Thread.Sleep(20);

                int progress = (int)((float)i / n * 100);
                if (progress > lastProgress)
                {
                    backgroundWorker.ReportProgress(progress);
                    lastProgress = progress;

                }
                if (backgroundWorker.CancellationPending)
                {
                    return null;
                }
            }
            backgroundWorker.ReportProgress(100);
        
            return result;
        }


        private double? getNewtonSymbolTask(int n, int k)
        {
            if (n <= 0 || k <= 0)
            {
                return null;
            }
            if (n < k)
            {
                return null;
            }

            var numeratorTask = Task.Factory.StartNew(
                (obj) =>
                    GetNominator(n, k),
                    100
                );
            var denominatorTask = Task.Factory.StartNew(
                (obj) =>
                    GetDenominator(n, k),
                    100
                );

            numeratorTask.Wait();
            denominatorTask.Wait();
            return numeratorTask.Result / denominatorTask.Result;
        }
        private double? getNewtonSymbolDelegats(int n, int k)
        {
            if (n <= 0 || k <= 0)
            {
                return null;
            }
            if (n < k)
            {
                return null;
            }

            var nominatorFunc = GetNominator;
            var denominatorFunc = GetDenominator;

            var nominator = nominatorFunc.BeginInvoke(n, k, null, null);
            var denominator = denominatorFunc.BeginInvoke(n, k, null, null);

            while (!nominator.IsCompleted && !denominator.IsCompleted)
            {
                // waiting for end of calculating
            }

            return nominatorFunc.EndInvoke(nominator) / denominatorFunc.EndInvoke(denominator);
        }
        private async Task<double?> getNewtonSymbolAsync(int n, int k)
        {
            if (n <= 0 || k <= 0)
            {
                return null;
            }
            if (n < k)
            {
                return null;
            }

            var nominator = Task.Run(() => GetNominator(n, k));
            var denominator = Task.Run(() => GetDenominator(n, k));

            await Task.WhenAll(nominator, denominator);

            return nominator.Result / denominator.Result;
        }


        private double GetNominator(int n, int k)
        {
            double result = 1;
            for (int i = n - k + 1; i <= n; i++)
            {
                result *= i;
            }
            return result;
        }
        private double GetDenominator(int n, int k)
        {
            double result = 1;
            for (int i = 1; i <= k; i++)
            {
                result *= i;
            }
            return result;
        }
    }
}
