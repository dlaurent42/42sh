
# Welcome to 42sh

#### Description
This project consists in creating a zsh-like in C language considered UNIX (and POSIX) standard.

#### Objectives
- Processes and signals handling
- Line edition
- Termcaps
- Creation and evaluation of an Abstract Syntax Tree (AST)
- Lexical analysis ("Lexing")
- Syntactic analysis ("Parsing")
- Semantic analysis
- UNIX environment handling
- Filesystem

#### Skills
- Group & interpersonal 
- Unix
- Rigor
- Organization 
- Imperative programming 

***
# LINE EDITION
#### Move

  ```←``` move one char to left

  ```→``` move one char to right

  ```↖``` move to beginning of line

  ```↘``` move to end of line

  ```⌥ + ←``` move one word to left

  ```⌥ + →``` move one word to right

  ```⌥ + ↑``` move one row up

  ```⌥ + ↓``` move one row down

#### Select
  ```⇧ + ←``` select left char

  ```⇧ + →``` select right char

  ```⇧ + ↖``` select chars to beginning of line

  ```⇧ + ↘``` select chars to end of line

  ```⇧ + ⌥ + ←``` select left word

  ```⇧ + ⌥ + →``` select right word

  ```⇧ + ⌥ + ↑``` select row above

  ```⇧ + ⌥ + ↓``` select row below

  ```Ctrl + K``` copy

  ```Ctrl + X``` cut

  ```Ctrl + P``` paste

#### Delete

  ```del``` delete previous char

  ```fn + del``` delete current char

  ```Ctrl + A``` delete all

  ```Ctrl + E``` delete to end of line

  ```Ctrl + H``` delete to beginning of line

  ```Ctrl + B``` delete previous word

  ```Ctrl + F``` delete next word

#### History

  ```↑``` previous command

  ```↓``` next command

  ```Ctrl + R``` search command

  ```!!``` gets last command

  ```!27``` gets command with id 27

  ```!-42``` gets 42nd most recent command

  ```!foo``` gets command by strncmp(cmd, "foo", 3)

  ```!?foo``` gets command by strstr(cmd, "foo)")

  ```bar!?foo?bar``` gets command by strstr(cmd, "foo)")

  ```^foo^bar^``` gets last command but applies s/foo/bar

***
# AUTO COMPLETION
#### Matched `Oh My Zsh`
- Colours
- Navigation with arrows, tab and shift + tab
- Vertical columns in selection screen
- Single word in buffer shows binaries and environment variables.
- Updates buffer in real-time
- Escapes characters correctly in real time. file: `super mario!` fills buffer with `super\ mario\!`
- Appends `=` to env variables and `/` to directories on **return**.
- Case insensitive.
- Clears selection window on exit of autocompletion
- Immediate auto-completion if only one match
- `cd` only shows directories
- `gcc` and `cc` only shows compatable file extension.
- Display of hidden files
- Window resize reorganises columns (better than zsh).
- Correct expansion of environment variables  
Assuming `FOO=bar`  
`$> echo $FO` then *tab* becomes `$> echo $FOO`.  
`$> echo $FOO` then *tab* becomes `$> echo bar`.
#### Others
- when buffer wraps to new line, selection window is properly positioned.
- Does not error when number of rows exceeds window size.
- Wildcard with `*` then return
***
# BUILTINS
#### Matched `Oh My Zsh`
### alias

##### Syntax

```
alias [-p] [name[=value] ...]
```

##### Options

&nbsp;&nbsp;&nbsp;&nbsp;-p&nbsp;&nbsp;&nbsp;&nbsp;Print the current values

If arguments are supplied, an alias is defined for each name whose value
is given.

If no value is given, alias will print the current value of the alias.

Without arguments or with the -p option, alias prints the list of aliases
on the standard output in a form that allows them to be reused as input.

The value cannot contain any positional parameters ($1 etc), if you need to
do that use a shell function instead.
### cd

##### Syntax

```
cd [-L|[-P [-e]] [-@] [directory]
```

##### Options

If directory is not supplied, the value of the HOME shell variable is used. Any additional arguments following directory are ignored. If the shell variable CDPATH exists, it is used as a search path: each directory name in CDPATH is searched for directory, with alternative directory names in CDPATH separated by a colon (‘:’). If directory begins with a slash, CDPATH is not used.

The -P option means to not follow symbolic links: symbolic links are resolved while cd is traversing directory and before processing an instance of ‘..’ in directory.

By default, or when the -L option is supplied, symbolic links in directory are resolved after cd processes an instance of ‘..’ in directory.

If ‘..’ appears in directory, it is processed by removing the immediately preceding pathname component, back to a slash or the beginning of directory.

If the -e option is supplied with -P and the current working directory cannot be successfully determined after a successful directory change, cd will return an unsuccessful status.

On systems that support it, the -@ option presents the extended attributes associated with a file as a directory.

If directory is ‘-’, it is converted to $OLDPWD before the directory change is attempted.

If a non-empty directory name from CDPATH is used, or if ‘-’ is the first argument, and the directory change is successful, the absolute pathname of the new working directory is written to the standard output.

The return status is zero if the directory is successfully changed, non-zero otherwise.

### echo

##### Syntax

```
echo [options]... [string]...
```

##### Options

&nbsp;&nbsp;&nbsp;&nbsp;-n&nbsp;&nbsp;&nbsp;&nbsp;Do not output the trailing newline.

### env

##### Syntax

```
env [OPTION]... [NAME=VALUE]... [COMMAND [ARGS]...]
```

##### Options

&nbsp;&nbsp;&nbsp;&nbsp;-u NAME&nbsp;&nbsp;&nbsp;&nbsp;Remove variable NAME from the environment, if it was in the
              environment.

&nbsp;&nbsp;&nbsp;&nbsp;-/-i&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Start with an empty environment, ignoring the inherited environment.

Arguments of the form `VARIABLE=VALUE' set the environment variable VARIABLE
to value VALUE.

VALUE can be empty (`VARIABLE='). Setting a variable to an empty value is
different from unsetting it.

The first remaining argument specifies the program name to invoke; it is
searched for according to the `PATH' environment variable. Any remaining
arguments are passed as arguments to that program.

If no command name is specified following the environment specifications,
the resulting environment is printed. This is like specifying a command name
of `printenv'.

### exit

##### Syntax
&nbsp;&nbsp;&nbsp;&nbsp;exit [status]

### export

##### Syntax
&nbsp;&nbsp;&nbsp;&nbsp;export [-fn] [-p] [name[=value]]

##### Options
&nbsp;&nbsp;&nbsp;&nbsp;-p&nbsp;&nbsp;&nbsp;&nbsp;Display output in a form that can be reused as input.

If no names are supplied, or if the `-p' option is given, a list of exported
names is displayed.

### history (refer to the dedicated section below)

##### Syntax

```
history
```

```
history [n]
```

```
history -c
```

```
history -d offset
```

```
history [-anrw] [filename]
```

```
history -ps arg
```

##### Options
&nbsp;&nbsp;&nbsp;&nbsp;-c&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Clear the history list. This can be combined with the other options to replace the history list completely.

&nbsp;&nbsp;&nbsp;&nbsp;-d offset&nbsp;&nbsp;&nbsp;&nbsp;Delete the history entry at position offset. offset should be specified as it appears when the history is displayed.

&nbsp;&nbsp;&nbsp;&nbsp;-a&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Append the new history lines (history lines entered since the beginning of the current Bash session) to the history file.

&nbsp;&nbsp;&nbsp;&nbsp;-n&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Append the history lines not already read from the history file to the current history list. These are lines appended to the history file since the beginning of the current Bash session.

&nbsp;&nbsp;&nbsp;&nbsp;-r&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Read the current history file and append its contents to the history list.

&nbsp;&nbsp;&nbsp;&nbsp;-w&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Write out the current history to the history file.

&nbsp;&nbsp;&nbsp;&nbsp;-p&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Perform history substitution on the args and display the result on the standard output, without storing the results in the history list.

&nbsp;&nbsp;&nbsp;&nbsp;-s&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The args are added to the end of the history list as a single entry.

With no options, display the history list with line numbers. Lines prefixed
with a `*' have been modified. An argument of n lists only the last n lines.

When any of the '-w', '-r', '-a', or '-n' options are used, if filename
is given, then it is used as the history file. If not, then the value of
the HISTFILE variable is used.

### read

##### Syntax

```
read [-ers] [-p prompt] [-t timeout] [-n nchars] [-d delim] [name...]
```

##### Options

&nbsp;&nbsp;&nbsp;&nbsp;-d delim&nbsp;&nbsp;&nbsp;&nbsp;The first character of delim is used to terminate the input line, rather than newline.

&nbsp;&nbsp;&nbsp;&nbsp;-e&nbsp;&nbsp;&nbsp;&nbsp;If the standard input is coming from a terminal, readline is used to obtain the line.

&nbsp;&nbsp;&nbsp;&nbsp;-n nchars&nbsp;&nbsp;&nbsp;&nbsp;Read returns after reading nchars characters rather than waiting for a complete line of input.

&nbsp;&nbsp;&nbsp;&nbsp;-p prompt&nbsp;&nbsp;&nbsp;&nbsp;Display prompt on standard error, without a trailing newline, before attempting to read any input. The prompt is displayed only if input is coming from a terminal.

&nbsp;&nbsp;&nbsp;&nbsp;-r&nbsp;&nbsp;&nbsp;&nbsp;Backslash  does not act as an escape character. The backslash is considered to be part of the line. In particular, a backslash-newline pair can not be used as a line continuation.

&nbsp;&nbsp;&nbsp;&nbsp;-s&nbsp;&nbsp;&nbsp;&nbsp;Silent mode. If input is coming from a terminal, character are not echoed.

&nbsp;&nbsp;&nbsp;&nbsp;-t timeout&nbsp;&nbsp;&nbsp;&nbsp;Cause read to time out and return failure if a complete line of input is not read within timeout seconds. This option has no effect if read is not reading input from the terminal or a pipe.

&nbsp;&nbsp;&nbsp;&nbsp;-u fd&nbsp;&nbsp;&nbsp;&nbsp;Read input from file descriptor fd.

This is a BASH shell builtin.

One line is read from the standard input, and the first word is assigned to
the first name, the second word to the second name, and so on, with leftover
words and their intervening separators assigned to the last name.

If there are fewer words read from the standard input than names, the
remaining names are assigned empty values.

The characters in the value of the IFS variable are used to split
the line into words.

The backslash character `\' can be used to remove any special meaning for
the next character read and for line continuation.

If no names are supplied, the line read is assigned to the variable REPLY.
The return code is zero, unless end-of-file is encountered or read times out.

### setenv

##### Syntax

```
setenv name=value [...]
```

### unalias

##### Syntax

```
unalias name [...]
```

##### Options

&nbsp;&nbsp;&nbsp;&nbsp;-a&nbsp;&nbsp;&nbsp;&nbsp;Delete all aliases

### unset

##### Syntax

```
unset name [...]
```

### unsetenv

##### Syntax

```
unsetenv name [...]
```

***
# History
#### Matched `Oh My Zsh`
- Saves history in ~/.42sh_history
- `history` shows history
- `!!` shows last command
- `!27` shows command with id 27
- `!-42` shows 42nd most recent command
- `!foo` shows last command beginning with "foo"
- `^foo^bar^` works like `!!` but applies `s/foo/bar`
- `!?foo` gets last command which contains 'foo' like `strstr(foo)`
- `bar!?foo?bar` like `!?` but only compares until `?`. Inserts between replaces from `!?` to `?` with the last command containing 'foo' like `strstr(foo)` If a previous command was `foo fighters` the buffer would contain `barfoo fightersbar` in this example.

***
# OTHER FEATURES
- Configuration file ~/42shrc
- Binaries and environment variables stored in hash table for speed.
- Prompt shows location
- Prompt shows git branch
- Dollar expansion
- Tilde expansion
- Implementation of hash tables for binaries and environment variables
- Globing : "*", "?", "[]", "{}", etc.
- Back quotes "‘".
- Inhibitors """ (double quote), "’" (simple quote) and "\" (backslash).
- Job control
- Subshells "( . )"
