# KawayamaProject
A project for cracking a random distributing program used in class

**GitHub: Keqing-Yuheng/KawayamaProject**

![Kawayama Project](https://raw.githubusercontent.com/Keqing-Yuheng/KawayamaProject/main/KawayamaProjectTitle.png)
Img: AL **Kawa**kaze & AL **Yama**kaze

## Background
In some classes of some schools, the seating chart of the classroom is generated randomly by a program. Usually, a teacher inserts his/her flash drive into the computer in the classroom, and run the program, which then distributes seats to students. Given the process, it is possible to "crack" such program by deploying some programs in the classroom computer.

**Attention**: Be careful when deploying the repository. We developers are NOT responsible for any result caused by the repository.

## Features
Control the output of teacher's random seating chart generator by modifying the program in teacher's flash drive automatically.

### Mode I: Direct Mode
**Simply output the seating chart completely crafted by user.** Random process is completely excluded, and everything is decided by user.

P.S.: make sure no changes are in the name list and seating list before choosing Mode I.

### Mode II: Swap Mode
**Swap several targeted names to the targeted seat after the seating chart is randomly generated.** Mode II provides a more flexible way to deal with unexpected changes in the name list and seating list, and generates different results when the program is run for several times.

P.S.: given the working process, Mode II might be slower than Mode I and original program (especially when too many targets need swapping), but obvious delay has not been observed by us.

## Process
1. A modified "random" seating chart generator, which distributes seats according to user's arrangement, should be deployed in the classroom computer. User's arrangement file should also be completed.

2. The background service will scan the disks in search the teacher's program.

3. Once the teacher's program is found, the background service will replace the original generator with the modified one, activate it and exit. 

   > (Not implemented)(Optional) Background service will check the consistency of the name list and the seating list. With consistent hash, Direct Mode will be activated; otherwise, Swap Mode will be activated.

4. When the teacher run the program, a seating chart modified according to the arrangement will be displayed.

5. (Not implemented)(Optional) The ending program will be invoked and wait for the end of the modified generator. Once the modified program ends, it will recover the original seating chart generator.

## Deployment
### 1. File Preparation
- Download the latest release ([Click Here](https://github.com/Keqing-Yuheng/KawayamaProject/releases, Releases)) and unzip the file.
- Get your teacher's Seating Chart Generator. (Need help? Config KawayamaService.exe to get it.)

### 2. Deployment in the targeted PC
Kawayama Project must be deployed in **D:\\Program Files\\KawayamaProject**

**Executable Files**
- **RandomSeatingChart.exe**
  **Modified** seating chart program. Keep its name the **same** as that of the teacher's program (instead of simply naming it RandomSeatingChart.exe), and change the value of "**Target EXE Name**" in Kawayama-Config.txt.
- **KawayamaService.exe**
  Background service. **Run this** to launch Kawayama Project.
- KawayamaEnd.exe (Not implemented)
  Recover the original program to the teacher's flash drive after running.

**Config Files**
- **Kawayama-Config.txt**
  Config of KawayamaService.
- **Kawayama-List.txt**
  Arrangement for Direct Mode, consisting of the complete seating chart.
- **Kawayama-Swap.txt**
  Arrangement for Swap Mode, consisting of the targeted seat ID together with names in that.

**Data Files**
- **Kawayama-Flag.txt**
  Decide which mode Kawayama will select. It is written by KawayamaService.ext initially. RandomSeatingChart.exe will execute according to its value.<br>
  Flag Values:<br>
  0: Random Mode.<br>
  1: Swap Mode. If failing, switch to Random Mode.<br>
  2: Direct Mode (switch to Swap Mode after one execution). If failing, switch to Swap Mode, then to Random Mode.<br>
  3: Direct Mode (always).If failing, switch to Swap Mode, then to Random Mode. P.S.: this can only be activated manually and be careful when choosing this.<br>
- **Kawayama-Log.txt**
  Log of Kawayama Project.

**Backup Files** (in **Backup** folder)
- **XXXX-XX-XX-XX-XX-XX** (Folder) (X refers to date and time)
  Archived target folder each time it is detected. This can be configured in "Archive Target Folder".
- **Backup.exe**
  Backup original EXE in the teacher's flash drive each time it is detected, and keep it latest. This is used for recovery (not implemented). This can be configured in "Backup Target EXE for Recovery".

**Directory Structure (Initial) (Ver 1.0.0)**
```
D:\Program Files\KawayamaProject
|   Kawayama-Config.txt
|   Kawayama-Flag.txt
|   Kawayama-List.txt
|   Kawayama-Swap.txt
|   KawayamaService.exe
|   RandomSeatingChart.exe
|
+---Backup
```

**Directory Structure (Complete) (Ver 1.0.0)**
```
D:\Program Files\KawayamaProject
|   Kawayama-Config.txt
|   Kawayama-Flag.txt
|   Kawayama-List.txt
|   Kawayama-Log.txt
|   Kawayama-Swap.txt
|   KawayamaService.exe
|   RandomSeatingChart.exe
|
+---Backup
|   \---XXXX-XX-XX-XX-XX-XX
|       Backup.exe
```

### 3. Config
Fill in Kawayama-Config.txt according to the types below (between "<" and">").
P.S.: "bool" means **true** or **false**. Other forms will be rejected.
```
# Kawayama Config 1.0.0

- Recover Target EXE
<bool>
- Backup Target EXE for Recovery
<bool>
- Archive Target Folder
<bool>
- Require Consistent Hash
<bool>
- The First Disk to Search
<char>
- The Last Disk to Search
<char>
- Target Folder Name
<string>
- Target EXE Name
<string>
```

### 4. Kawayama, launch!
With everything done, **launch KawayamaService.exe** manually or through taskschd.msc!

Testing the process ahead of time is recommended.

## Building
The repository is developed with **Visual Studio 2022**.

C++ source files can also be compiled by MinGW.

Other building methods are not tested.

## Performance
The effect on PC performance that Kawayama Project has varies in different situation.
1. Test 1 (Windows 7, Intel Core i5 4th Gen, 4GB Memory)
   CPU:25% (take up one core), Memory: approximately 4-10MB. No obvious performance decline is observed except increased fan speed.
2. Test 2 (Windows 10, Intel Core i5 9th Gen, 16GB Memory)
   CPU: approximately 0.1%, Memory: approximately 4-10MB.

## Happy New Year!
