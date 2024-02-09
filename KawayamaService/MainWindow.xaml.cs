using System;
using System.Windows;
using System.IO;

namespace KawayamaService
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        //配置
        //定义常量 并设置未指定时的初始值

        /// <summary>
        /// 备份原始EXE开关
        /// </summary>
        static bool BackupExe = false;

        /// <summary>
        /// 存档文件夹开关
        /// </summary>
        static bool ArchiveFolder = false;

        //NOT IMPLEMENTED
        /// <summary>
        /// 要求姓名表Hash相同开关
        /// </summary>
        static bool HashConsistence = false;

        /// <summary>
        /// 搜索的第一个盘符
        /// </summary>
        static char DiskStart = 'F';

        /// <summary>
        /// 搜索的最后一个盘符
        /// </summary>
        static char DiskEnd = 'Z';

        /// <summary>
        /// 文件夹名称
        /// </summary>
        static string TargetFolderName = "RandomSeatingChartProgram";

        /// <summary>
        /// 程序名称
        /// </summary>
        static string TargetExeName = "RandomSeatingChart.exe";

        public MainWindow()
        {
            InitializeComponent();

            WriteLog("INFO", "Launch [Version 1.0.0 / GitHub: Keqing-Yuheng/KawayamaProject]");

            //读取配置文件
            GetConfig();

            //目标要设置的flag 默认为2
            string TargetedFlag = "2";

            //检测flag
            string flag;
            if(File.Exists("D:\\Program Files\\KawayamaProject\\Kawayama-Flag.txt"))
            {
                StreamReader flagreader = new StreamReader("D:\\Program Files\\KawayamaProject\\Kawayama-Flag.txt");
                flag = flagreader.ReadLine();
                flagreader.Close();

                WriteLog("INFO", "Current Flag " + flag);

                //flag为-1(无条件不运行)则不执行后续
                if (flag == "-1")
                {
                    WriteLog("INFO", "Exit with return code 1");
                    Environment.Exit(1);
                }
            }
            else
            {
                WriteLog("FATAL", "FlagReader Failed");
                WriteLog("INFO", "Exit with return code -1");
                Environment.Exit(-1);
            }

            string TargetFolder;    //目标文件夹完整路径

            string TargetExe;   //目标程序完整路径

            while (true)
            {
                for (char Disk = DiskStart; Disk <= DiskEnd; Disk++)
                {
                    if(Directory.Exists(Disk + ":\\" + TargetFolderName))
                    {
                        TargetFolder = Disk + ":\\" + TargetFolderName;
                        TargetExe = TargetFolder + "\\" + TargetExeName;

                        WriteLog("INFO", "Target Found at " + TargetFolder);

                        FileInfo fi_exedest = new FileInfo(TargetExe);  //要替换的exe
                        FileInfo fi_exemod = new FileInfo(TargetExeName);   //在程序所在目录的修改exe
                        /* 为Hash准备的代码
                        FileInfo fi_namedest = new FileInfo(TargetFolder + "\\name.in");    //在目标文件夹的姓名表
                        FileInfo fi_namecontrast = new FileInfo("D:\\Program Files\\KawayamaProject\\name.in"); //在程序所在目录的姓名表
                        */

                        //备份原始EXE
                        if (BackupExe == true)
                        {
                            try
                            {
                                fi_exedest.CopyTo("D:\\Program Files\\KawayamaProject\\Backup\\Backup.exe", true);
                                WriteLog("INFO", "Backup at D:\\Program Files\\KawayamaProject\\Backup\\Backup.exe");
                            }
                            catch (Exception ex)
                            {
                                WriteLog("ERROR", "Backup Failed");
                            }
                        }

                        //存档文件夹
                        if(ArchiveFolder == true)
                        {
                            try
                            {
                                string subdir = DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss");
                                CopyDirectory(TargetFolder, "D:\\Program Files\\KawayamaProject\\Backup\\" + subdir, true);
                                WriteLog("INFO", "Archive at " + subdir);
                            }
                            catch(Exception ex)
                            {
                                WriteLog("ERROR", "Archive Failed");
                            }
                        }

                        //TODO: Check Hash of NameList in 2 Folders

                        //替换exe
                        try
                        {
                            fi_exemod.CopyTo(TargetExe, true);
                            WriteLog("INFO", "Overwrited " + TargetExe);
                        }
                        catch(Exception ex)
                        {
                            WriteLog("ERROR", "Overwrite Failed");
                        }

                        //设置flag
                        try
                        {
                            StreamWriter flagwriter = new StreamWriter("D:\\Program Files\\KawayamaProject\\Kawayama-Flag.txt", false);
                            flagwriter.Write(TargetedFlag);  //设置Flag
                            flagwriter.Close();
                            WriteLog("INFO", "Flag changed to " + TargetedFlag);
                        }
                        catch(Exception ex)
                        {
                            WriteLog("FATAL", "FlagWriter Failed");
                            WriteLog("INFO", "Exit with return code -1");
                            Environment.Exit(-1);
                        }

                        //程序结束
                        WriteLog("INFO", "Exit with return code 0");
                        Environment.Exit(0);
                    }
                }
            }
        }

        /// <summary>
        /// 写入Log
        /// </summary>
        void WriteLog(string level, string message)
        {
            try
            {
                StreamWriter sw = new StreamWriter("D:\\Program Files\\KawayamaProject\\Kawayama-Log.txt", true);
                sw.WriteLine("[" + DateTime.Now.ToString() + "]<Service>[" + level + "]" + message);
                sw.Close();
            }
            catch(Exception ex)
            {

            }
        }

        /// <summary>
        /// 加载配置
        /// </summary>
        void GetConfig()
        {
            string in_str;

            //检查文件是否存在
            if(!File.Exists("D:\\Program Files\\KawayamaProject\\Kawayama-Config.txt"))
            {
                WriteLog("FATAL", "Config Failed");
                WriteLog("INFO", "Exit with return code -1");
                Environment.Exit(-1);
            }

            StreamReader ConfigReader = new StreamReader("D:\\Program Files\\KawayamaProject\\Kawayama-Config.txt");

            //读取每行内容
            //1
            ConfigReader.ReadLine();
            //2
            ConfigReader.ReadLine();
            //3
            ConfigReader.ReadLine();
            //4
            ConfigReader.ReadLine();
            //5
            ConfigReader.ReadLine();
            //6
            BackupExe = ConfigReader.ReadLine() == "true" ? true : false;
            //7
            ConfigReader.ReadLine();
            //8
            ArchiveFolder = ConfigReader.ReadLine() == "true" ? true : false;
            //9
            ConfigReader.ReadLine();
            //10
            HashConsistence = ConfigReader.ReadLine() == "true" ? true : false;
            //11
            ConfigReader.ReadLine();
            //12
            in_str = ConfigReader.ReadLine();
            DiskStart = in_str[0];
            //13
            ConfigReader.ReadLine();
            //14
            in_str = ConfigReader.ReadLine();
            DiskEnd = in_str[0];
            //15
            ConfigReader.ReadLine();
            //16
            TargetFolderName = ConfigReader.ReadLine();
            //17
            ConfigReader.ReadLine();
            //18
            TargetExeName = ConfigReader.ReadLine();

            ConfigReader.Close();

            //配置记录到Log
            WriteLog("INFO", "Config: BackupEXE=" + BackupExe.ToString());
            WriteLog("INFO", "Config: ArchiveFolder=" + ArchiveFolder.ToString());
            WriteLog("INFO", "Config: HashConsistence=" + HashConsistence.ToString());
            WriteLog("INFO", "Config: DiskStart=" + DiskStart);
            WriteLog("INFO", "Config: DiskEnd=" + DiskEnd);
            WriteLog("INFO", "Config: TargetFolderName=" + TargetFolderName);
            WriteLog("INFO", "Config: TargetExeName=" + TargetExeName);
        }

        /// <summary>
        /// 复制文件夹
        /// </summary>
        public static void CopyDirectory(string sourceDir, string destinationDir, bool recursive)
        {
            //Code from MS Learn
            
            // Get information about the source directory
            var dir = new DirectoryInfo(sourceDir);

            // Check if the source directory exists
            if (!dir.Exists)
                throw new DirectoryNotFoundException($"Source directory not found: {dir.FullName}");

            // Cache directories before we start copying
            DirectoryInfo[] dirs = dir.GetDirectories();

            // Create the destination directory
            Directory.CreateDirectory(destinationDir);

            // Get the files in the source directory and copy to the destination directory
            foreach (FileInfo file in dir.GetFiles())
            {
                string targetFilePath = System.IO.Path.Combine(destinationDir, file.Name);
                file.CopyTo(targetFilePath);
            }

            // If recursive and copying subdirectories, recursively call this method
            if (recursive)
            {
                foreach (DirectoryInfo subDir in dirs)
                {
                    string newDestinationDir = System.IO.Path.Combine(destinationDir, subDir.Name);
                    CopyDirectory(subDir.FullName, newDestinationDir, true);
                }
            }

        }
    }
}
