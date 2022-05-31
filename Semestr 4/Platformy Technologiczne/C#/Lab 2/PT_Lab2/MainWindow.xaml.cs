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

namespace PT_Lab2
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }
        private void Open_Click(object sender, RoutedEventArgs e)
        {
            var dlg = new FolderBrowserDialog() { Description = "Select directory to open" };
            var result = dlg.ShowDialog();
            if (result == System.Windows.Forms.DialogResult.OK)
            {
                var dirInfo = new DirectoryInfo(dlg.SelectedPath);
                var root = CreateTreeDirectory(dirInfo);
                treeView.Items.Clear();
                treeView.Items.Add(root);
            }

        }
        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            Environment.Exit(0);
        }
        private TreeViewItem CreateTreeDirectory(DirectoryInfo dir)
        {
            var root = new TreeViewItem
            {
                Header = dir.Name,
                Tag = dir.FullName,
                ContextMenu = new System.Windows.Controls.ContextMenu(),
            };
            root.Selected += new RoutedEventHandler(StatusUpdate);

            var createClick = new MenuItem { Header = "Create" };
            var deleteClick = new MenuItem { Header = "Delete" };

            createClick.Click += new RoutedEventHandler(CreateClick);
            deleteClick.Click += new RoutedEventHandler(DeleteClick);

            root.ContextMenu.Items.Add(createClick);
            root.ContextMenu.Items.Add(deleteClick);

            foreach (var tempDir in dir.GetDirectories())
            {
                root.Items.Add(CreateTreeDirectory(tempDir));
            }
            foreach (var file in dir.GetFiles())
            {
                root.Items.Add(CreateTreeFile(file));
            }
            return root;
        }
        private TreeViewItem CreateTreeFile(FileInfo file)
        {
            var item = new TreeViewItem
            {
                Header = file.Name,
                Tag = file.FullName,
                ContextMenu = new System.Windows.Controls.ContextMenu()
            };
            item.Selected += new RoutedEventHandler(StatusUpdate);

            var openClick = new MenuItem { Header = "Open" };
            var deleteClick = new MenuItem { Header = "Delete" };

            openClick.Click += new RoutedEventHandler(OpenClick);
            deleteClick.Click += new RoutedEventHandler(DeleteClick);

            item.ContextMenu.Items.Add(openClick);
            item.ContextMenu.Items.Add(deleteClick);

            return item;
        }
        private void StatusUpdate(object sender, RoutedEventArgs e)
        {
            var item = (TreeViewItem)treeView.SelectedItem;
            var attributes = File.GetAttributes((string)item.Tag);

            status.Text = "";
            status.Text += (attributes & FileAttributes.ReadOnly) == FileAttributes.ReadOnly ? 'r' : '-';
            status.Text += (attributes & FileAttributes.Archive) == FileAttributes.Archive ? 'a' : '-';
            status.Text += (attributes & FileAttributes.System) == FileAttributes.System ? 's' : '-';
            status.Text += ((attributes & FileAttributes.Hidden) == FileAttributes.Hidden ? 'h' : '-');
        }
        private void CreateClick(object sender, RoutedEventArgs e)
        {
            var folder = (TreeViewItem)treeView.SelectedItem;
            var addWindow = new AddWindow((string)folder.Tag);
            addWindow.ShowDialog();

            if (addWindow.IfSuccess())
            {
                var path = addWindow.GetPath();
                if (Directory.Exists(path))
                {
                    DirectoryInfo dir = new DirectoryInfo(path);
                    folder.Items.Add(CreateTreeDirectory(dir));
                    return;
                }
                else if (File.Exists(path))
                {
                    FileInfo file = new FileInfo(path);
                    folder.Items.Add(CreateTreeFile(file));
                    return;
                }

            }
        }
        private void DeleteClick(object sender, RoutedEventArgs e)
        {
            var item = (TreeViewItem)treeView.SelectedItem;
            var path = (string)item.Tag;

            File.SetAttributes(path, File.GetAttributes(path) & ~FileAttributes.ReadOnly);
            
            delete(path);
  
            if ((TreeViewItem)treeView.Items[0] == item)
            {
                treeView.Items.Clear();
                return;
            }
            var parent = (TreeViewItem)item.Parent;
            parent.Items.Remove(item);
        }
        private void delete(string path)
        {
            //path is to file
            if ((File.GetAttributes(path) & FileAttributes.Directory) != FileAttributes.Directory)
            {
                File.Delete(path); 
                return;
            }

            //path is to directory
            var dir = new DirectoryInfo(path);
            foreach (var tempDir in dir.GetDirectories())
            {
                delete(tempDir.FullName);
            }
            foreach (var file in dir.GetFiles())
            {
                delete(file.FullName);
            }
            Directory.Delete(path);
           
        }
        private void OpenClick(object sender, RoutedEventArgs e)
        {
            var item = (TreeViewItem)treeView.SelectedItem;
            var content = File.ReadAllText((string)item.Tag);
            viewer.Content = new TextBlock() { Text = content };
        }
    }
}
