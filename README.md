## Hi, wc to VE280, Programming & Elem. Data Structures.

### Introduction

Feeling this course useful, I redo all the lab assignments and project in year 2021. All these are written by C++ using flag ```-std=c++11```. 

### Reading Order

1. My suggestion would be first go to ```./Lecture Slides``` and take one week's time to understand all the concepts inside. Write some **Cheating Paper** so that you can go back to what is needed quickly. It is **Definitely NOT** a good idea to attend the lectures.
2. Then go to ```./Five Projects``` and spend 2 days on each of the programming assignments. From my experience, it might **take MORE time** on the third and fourth projects, especially for debugging and testing. 
3. Before going into the ```./Useful Recitation Class```, it is better to spend one day to review the Lecture Slides. 
4. The RC slides contains **much much much MORE** contents than VE280 itself. On reviewing the recitation class slides, I am shocked by the countless amount of knowledge owned by the TAs. Great thanks to the whole TA group for bring us some big pictures and intro to other advanced topics.
5. If you are students taking this course later than year 2019, you are lucky because you have new projects and labs to practice. Pls refer to [tc-imba](https://github.com/tc-imba/VE280) for description and starter files of the new projects. Pls refer to [LouieBHLu](https://github.com/LouieBHLu/VE280_2020_Summer/tree/master/Labs) for description and starter files of the new labs. 

### More on Projects

Description can be found in the corresponding files.

**Project One: Integers!**

​		This project will give you experience in using basic C++ constructs including I/O, arithmetic operators, branch, and loop.

​		To run, type ```./Five Projects/Project1/test.sh```

**Project Two: Recursion**

​		This project will give you experience in writing recursive functions that operate on recursively defined data structures and mathematical abstractions.

​		To run, type ```./Five Projects/Project2/test.sh``` and three test cases will be run automatically. 

**Project Three: Simple World**

​		To give you experience in using arrays, pointers, structs, enums, and different I/O streams and writing program that takes arguments.

​		To run, type  ```./Five Projects/Project3/test.sh``` and test cases in ```./Five Projects/Projct3/world-tests``` will be run automatically. 

**Project Four: Quarto**

​		To give you experience in implementing abstract data types (ADTs), using interfaces (abstract base classes), and using interface/implementation inheritance.

​		To run, type 

```bash
cd ./Five Projects/Project4
make
./p4 # add arguments as you like, e.g. ./p4 m m 10
```

**Project Five: List, Stack, and Queue**

​		This project will give you experience in applying dynamic memory management, implementing a template container class (the double‐ended, doubly‐linked list, or Dlist), and using the at-most‐once invariant and existence, ownership, and conservation rules to implement two simple applications using this structure.

​		To run, first uncomment the commands in ```./Five Projects/Project5/test.sh``` and then run it. ```valgrind --leak-check=full``` is used to check memory leak. To install valgrind on Linux, type ```sudo apt-get install valgrind```.

### More on Recitation Class

In one word, old RC classes for knowledges and new RC/labs for practice.

If you are interested in one TCS field called **Formal Verification**. You can start with [Software Foundation Volumn 1](https://softwarefoundations.cis.upenn.edu/lf-current/Preface.html). (My solution for exercises is available [here](https://github.com/StevenWongChess/software-foundations) ) A course called [CSE-505](https://sites.google.com/cs.washington.edu/cse-505-18au/home) is available online. [Standard Library](https://coq.inria.fr/library/index.html) for Coq can be found here. You can also have a better understanding of Coq through [Youku](https://v.youku.com/v_show/id_XMzIzOTkyMDI4NA==). 

Week 8 is a summary of the previous RCs.  

- [ ] Week 9 is pretty hard. Remember to review. 

- [ ] Week 10 is about a game called LTK, to be finished. 

- [ ] Week 11 to be finished

Week 12 is about skip list, I don't think we can reuse the code of assignment operator to write copy constructor without adding new member functions. If you can make it, pls do not hesitate to leave a message or pull a request.

### Honor Code

Pls respect the honor code and NEVER reuse these code.