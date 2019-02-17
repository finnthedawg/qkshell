#  :sparkles:qkshell :sparkles:
A unix shell written in C.

---

### qkshell features

* **pwd** - Print working directory.

* **cd** - Change current directory.

* **export** - List exported shell variables.
```
>> export
```
Set a path variable. Paths seperated by ':'
```
>> export PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin
```
* **history** - Display the command history and line numbers.

* **replay command** - Plays last command from history list.
```
>> !22
```
* **exit** - Free memory and exit.

And more to come

---
### Installation
```
make
./sh
```
To delete history and restart.
```
make clean
./sh
```
