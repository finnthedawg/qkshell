#  :sparkles:qkshell :sparkles:
An implementation of a Unix shell written in C.

---

## To run the project:

```
> git clone
> make
> ./sh
```
Make sure you have GCC version 4.3+

## qkshell built in features:

* `pwd` Prints working directory.

* `cd [args]` - Change the working directory of qkshell. Updates `$PWD` variable.

* `history` - Lists the history of commands that have been executed.

```
history
1 history
2 ls
3 export
4 export PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin
5 export
6 ls -l -a
```

* `![number]` Execute the nth command from our history file.

* `export [PATH]=[/directory1:/directory2]` - Export the path variables to qkshell. e.g `export JAVA_PATH=/home/test/java/bin`.

* `export` Without specifying arguments, export will return a list of currently exported variables.

* `[External-command]` executes an external command by searching for the file within export variables.

```
ls is an external command (/usr/bin/ls)
command arguments:
-l
-a
```

* `exit`  or `quit` - Free allocated memory and exit.

* `$PWD` - Shell variable expansion. Expands `$ExportedKey` into the corresponding `$ExportedValue` e.g:

```
>> export
PATH=/usr/bin
PWD=/home/finn/Desktop/OS/qkshell
>> export PATH=$PATH:/bin/
>> export
PATH=/usr/bin:/bin/
PWD=/home/finn/Desktop/OS/qkshell
```

* `pwd | grep qksh | grep q` - pipes. Pass the output of one command to the input of the next command.

* `cat < history.c` - Input redirection. Changes the input to a command to a file.

* `pwd > output.txt` - Output redirection. Changes the output from stdout to a file.

* `cat aaaaa 2> error.txt` - File stream rediction. Redirects the stderr to a chosen file.
