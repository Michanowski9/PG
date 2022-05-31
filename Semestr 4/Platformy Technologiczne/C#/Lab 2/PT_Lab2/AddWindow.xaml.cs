using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Forms;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.Text.RegularExpressions;

namespace PT_Lab2
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class AddWindow : Window
    {
        private string path;
        private string name;
        private bool success;
        public AddWindow(string path)
        {
            this.path = path;
            this.name = "";
            this.success = false;
            InitializeComponent();
        }

        private void OK_Click(object sender, RoutedEventArgs e)
        {
            bool isFile = (bool)radioFile.IsChecked;
            bool isDirectory = (bool)radioDirectory.IsChecked;
            if (!isFile && !isDirectory)
            {
                System.Windows.MessageBox.Show("Wrong type", "ERROR", MessageBoxButton.OK, MessageBoxImage.Information);
                return;
            }
            if (isFile && !Regex.IsMatch(nameInput.Text, "^[a-zA-Z0-9_~-]{1,8}\\.(txt|php|html)$"))
            {
                System.Windows.MessageBox.Show("Wrong input name", "ERROR", MessageBoxButton.OK, MessageBoxImage.Information);
                return;
            }

            FileAttributes attributes = FileAttributes.Normal;
            attributes |= checkRO.IsChecked == true ? FileAttributes.ReadOnly : 0;
            attributes |= checkA.IsChecked == true ? FileAttributes.Archive : 0;
            attributes |= checkH.IsChecked == true ? FileAttributes.Hidden: 0;
            attributes |= checkS.IsChecked == true ? FileAttributes.System : 0;

            this.name = nameInput.Text;
            path = path + "\\" + this.name;
            if (isDirectory)
            {
                Directory.CreateDirectory(path);
            }
            else if (isFile)
            {
                File.Create(path);
            }
            File.SetAttributes(path, attributes);
            this.success = true;
            Close();
        }
        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }
        public bool IfSuccess()
        {
            return this.success;
        }
        public string GetPath()
        {
            return this.path;
        }
    }
}
