# Assignment 9
## Submitted by Timofei Podkorytov
for operating systems course in fall 2024
## Compiling: Makefile
The following make commands are available:
```
$ make quiz
```

## Running:
These are inputs that are accepted by the prohram
```
./quiz
```

## Files:
- Makefile
- README.md
- quiz.h
- qui.c
- fetch.c
- parse.c
- play.c

Makefile provides make commands. README gives the description of the overall homework submission.

Quiz header file gives the functions and struct from task description. It only gives declarations.

Fetch.c, parse.c, play.c give the definitions of functions. Thy follow the task requirements.

## Output
Here are some examples of output:
```
$./quiz
Answer multiple choice questions about computer science.
You score points for each correctly answered question.
If you need multiple attempts to answer a question, the
points you score for a correct answer go down.
    
Who is the original author of the realtime physics engine called PhysX?

[a] Ageia
[b] Nvidia
[c] NovodeX
[d] AMD

(8pt) > a
Answer [a] is wrong, try again.
(4pt) > b
Answer [b] is wrong, try again.
(2pt) > c
Congratulation, answer [c] is correct. Your current score is 2/8 points.

The name of technology company HP stands for what?

[a] Howard Packmann
[b] Hewlett-Oackard
[c] Hellman-Pohl
[d] Husker-Pollosk

(8pt) > a
Answer [a] is wrong, try again.
(4pt) > c
Answer [c] is wrong, try again.
(2pt) > d
Answer [d] is wrong, try again.
Number of attempts acceeded!
Thanks for playing today.
Your final score is 2/16 points


Answer multiple choice questions about computer science.
You score points for each correctly answered question.
If you need multiple attempts to answer a question, the
points you score for a correct answer go down.
    
What is the main CPU is the Sega Mega Drive / Sega Genesis?

[a] Motorola68000
[b] Yamaha YM2612
[c] Intel 8088
[d] Zilog Z80

(8pt) >
```