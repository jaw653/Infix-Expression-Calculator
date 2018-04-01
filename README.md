# Infix-Expression-Calculator

C implementation of an infix expression calculator. Matilda.c is the file to be executed once compiled.

Used previously created dynamic structure "classes" such as stack, queue, dynamic array, and circular dynamic array to implement the calculator.

All files needed to utilize this project are found in the repository and can be used as shown below.

Command Line examples:
~$ make
~$ ./trees -g assign2Tests/trees.0 assign2Tests/trees.1 outputs/1
(the above will throw items in trees.0 found in trees.1 into a Green Tree Structure, writing the GT into outputs/1)
~$ ./trees -r assign2Tests/trees.0 assign2Tests/trees.1 outputs/1
(will do the same as the first command, but will use throw items into Red-Black Tree instead)
~$ make test
(runs program on plethora of tests and uses diff command w/ previously known correct outputs to check correctness)
~$ make clean
(cleans directory of executables for full recompilation)
