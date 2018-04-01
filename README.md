# Infix-Expression-Calculator

C implementation of an infix expression calculator. Matilda.c is the file to be executed once compiled.

Used previously created dynamic structure "classes" such as stack, queue, dynamic array, and circular dynamic array to implement the calculator.

All files needed to utilize this project are found in the repository and can be used as shown below.

Command Line examples:</br>
~$ make</br>
~$ ./matilda -i -p -b file</br>
<\t>(takes the infix expression from 'file' and converts to postfix. -i prints input from 'file', -p prints postfix, -b prints binary tree used for storing equation)</br>
~$ make test</br>
<\t>(runs program on plethora of tests and uses diff command w/ previously known correct outputs to check correctness)</br>
~$ make clean</br>
<\t>(cleans directory of executables for full recompilation)
