# OS LAB exercises

This repo contains almost all exercises made by me for Uniparthenope university OS LAB course. 

I used some Makefiles to ease folders creation and projects creation, compilation and execution.

## How to use top level Makefile
To create a new folder at top level, just run:

```
make path=lesson_0
```

This command will create a new folder named `lesson_0` which will contain another Makefile and tpl folder to create C projects.

## How to use Makefile at folder level
To create a new project, just run:

```
make name=ex_0
```

This command will create a new C project within folder `ex_0` which will contain another Makefile and main.c and a.out files.

## How to use Makefile at project level
To execute the project, just run: 

```
make
```
This command will compile the project and will execute it.
