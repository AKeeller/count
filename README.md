# count
count is a simple program, written in C, created to count the existing files in a given folder with a given extension, even recursevely.
## Compiling
First of all, you need to compile the source code to generate a functional binary. Open the terminal and place yourself in the same folder as the source files with `cd /folder/to/source/files`.
Compile as following
```
cc count.c -o count
```
## Installing
If you desire to install *count*, you can just copy or move the binary into /bin/
```
mv count /bin/
```
## Usage
Now you can begin using *count*. The syntax is the following:
```
count [-r] [extension] [folder]
```
### Example
```
count -r txt .
```
This simple line of code will search for every file with txt extension recursevely in the current working folder. The grand total will be displayed at the end of the process.
### Notes
*count* is currently available only for Unix operating systems.
*count* has been tested only on OS X 10.9.1