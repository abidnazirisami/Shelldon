#!/bin/bash
gcc Input.c Parse.c Shelaunch.c Builtins.c Execution.c shell_header.h Main.c -o Sheldon
./Sheldon
