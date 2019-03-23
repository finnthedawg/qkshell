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

* `cd [args]` - Change the working directory of qkshell

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

* `![number]` Recalls the command from history and executes it.

* `export [PATH]=[/directory1:/directory2]` - Export the path variables to qkshell. e.g `export JAVA_PATH=/home/test/java/bin`.
Without specifying arguments, export will return a list of currently exported variables.

* `[External-command]` checks the external command within path variables, returns the location found:
```
ls is an external command (/usr/bin/ls)
command arguments:
-l
-a
```

* `exit` - Free allocated memory and exit.

* Todo: `special symbols`, `pipes`, `Output redirection` `Input redirection` `Shell variables`
