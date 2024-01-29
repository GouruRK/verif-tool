# verif-tool

Little tool to check text file format like line length, and more to come.

- [verif-tool](#verif-tool)
  - [Download and run](#download-and-run)
  - [Runtime parameters](#runtime-parameters)
  - [Examples](#examples)
  - [Next step](#next-step)


## Download and run

To download the repo, juste use the `git` command as bellow:
```bash
$ git clone https://github.com/GouruRK/verif-tool.git
```

To compile this project, go on, the `verif-tool` directory and run 
the `make command`. It creates an executable `verif`, which is the entry point
of the programm.

```bash
$ cd verif-tool
$ make
$ ./verif -h
```

## Runtime parameters

This executable come with a bunch of command line parameters, listed in
the help message (`--help`)

```bash
Usage: verif [OPTION...] PATH
Print lines number of file pointed by PATH that are too long
according to the ruleset

If PATH is a directory, it will check the files in that directory

  -r, --recursive       If PATH contains directories, their content
                          will be checked too
  -v, --verbose         Print file name even if file format is correct
  -a, --all             Check all types of files. Overrides the filter parameter
  -l, --length          Specify maximum line length. Default: 80
  -f, --filter          Specify file type to check. Extensions must be separated
                          by a comma.
  -h, --help            Print this message and exit
```

## Examples

```bash
$ ./verif -r -f c,h .
```

```bash
$ ./verif -r -a .
```

```bash
$ ./verif -l 120 -r -a -v .
```

## Next step

* Next update will provide tool to check function's length
