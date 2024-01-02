# KawayamaProject
A project for cracking a random distributing program used in class

**Keqing-Yuheng/KawayamaProject**

## Background
In some classes of some schools, the seating chart of the classroom is generated randomly by a program. Usually, a teacher inserts his/her flash drive into the computer in the classroom, and run the program, which then distributes seats to students. Given the process, it is possible to "crack" such program by deploying some programs in the classroom computer.

**Attention**: Be careful when deploying the repository. We developers are NOT responsible for any result caused by the repository.

## Features
Modify the teacher's random seating chart generating program immediately the teacher insert his/her flash drive, and make it generate seating charts under user's control.

### Modification Type I
**Output the seating chart completely crafted by user simply.** No random process is included. Full seating chart of the classroom should be prepared by user. Before choosing this type, make sure there will be no change in the name list and seating list. Otherwise, Type I will not run, or something embarrassing to user might happen if user force to run Type I.

### Modification Type II
**Swap a few targeted person to the targeted seat after the seating chart is randomly generated.** A list of targeted persons and targeted seats should be prepared by user. Type II provides a more flexible way to deal with unexpected changes in the name list and seating list, and generates different results when the teacher run the program for several times. But Type II may be slower than Type I and the original program, especially there are too many targets.

## Process
1. A modified "random" seating chart generator, which distributes seats according to user's arrangement, should be deployed in the classroom computer. User's arrangement file should also be completed.

2. The background service will scan the disks in search the teacher's program.

3. Once the teacher's program is found, the background service will replace the original generator with the modified one and exit. 

   > (Optional) To avoid unexpected changes in the name list and the seating list, the background service can compare the hash of those files. With consistent hash, the background service will use the program that simply output user's arrangement. Otherwise, the background service will use the program that only keep a few targeted persons in the targeted seats.

4. When the teacher run the program, the program will display a seating chart according to the arrangement.

5. (Optional) The ending program will be invoked and wait for the end of the modified generator. Once the modified program ends, it will recover the original seating chart generator.

## Deployment

## Building
The repository is developed with **Visual Studio 2022**.

C++ source files can also be compiled by MinGW.

Other building methods are not tested.

## Happy New Year!

Image: AL **Kawa**kaze & AL **Yama**kaze (Copyright: Azur Lane)

**The repository will be completed soon.**