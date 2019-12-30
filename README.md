# micro32
This is a simulation of a 32-bit van-neumann-architecture microprocessor, as conceptualized in micro32.png

It has 16 registers, where register 0 is always 0 and register 1 is always 1.

The memory consists of 2^32 adresses, 2^12 of which can be utilized for binary instructions.

The whole memory (meaning, also the binary instructions) can be self-modified by the instructions themself.  
To modify the memory, one must load an adr from the alu into the MAR (MEMMODE 01) and in the next step load data from the alu
into the adr specified in the MAR (MEMMODE 10).  
One can also load data from the memory into the A-IN of the alu by using MEMMODE 11, which will set the A-MUX to 1 and load the
data from the adr specified in the MAR.

4 different operations for the alu and additionally a shift of the result by one to the left or right can be chosen.

A jumpadr can be also specified, to which the counter will jump, if the alu-out satisfies the specified jumping-condition.

To run a program, one must create a file called "bootloader" which may consist only of 32-bit-codes, meaning every line shall 
contain exactly 32 characters of either 0 or 1  
The bits specified in those 32 characters have the following effects (order from left to right) ..  
2 bit: ALU (arithmetic operation)  
2 bit: SHIFT (left/right shift operation)  
2 bit: MEMMODE (memory mode)  
2 bit: JUMP (jumping condition)  
4 bit: A-SEL (selector for which register shall be loaded into A-IN of alu)  
4 bit: B-SEL (selector for which register shall be loaded into B-IN of alu)  
4 bit: S-SEL (selector for which register (other than 0 or 1) shall get the output from the alu)  
12 bit: JUMPADR (the adr, to which the counter shall jump, if the jumping condition is fulfilled)  
Look into the micro32.png for more details concerning the operations  
  
The bootloader-file in the repository contains an example-program, that initializes reg2=4, reg3=3 and then uses a multiplication
subroutine to multiply them.  

If the counter reaches 2^12-1, the program will stop, meaning you can jump to this adress to stop your program.

![micro32conceptual](micro32.png)
