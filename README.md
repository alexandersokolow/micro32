# micro32
This is a simulation of a 32-bit van-neumann-architecture microprocessor, as conceptualized in micro32.png

It has 64 registers, where register 0 is always 0, register 1 is always 1 and register 2 is always -1 (in two's complement).  
Only the first 16 will be printed during the programs execution, but you can easily modify the code to print all of them, by changing the maximal value for i in the for-loop of the printStatus-method.

The memory consists of 2^16 addresses, which can be utilized for and modified by binary instructions.  
This can be done, by filling the MBR (memory-buffer-register) and MAR (memory-address-register) and then using the appropriate command (look below) to save the data from the MBR to the MAR-address or conversely load the data from the MAR-address to the MBR.  
Later on I will also add physical i.e. non-volatile memory to it.

4 different operations for the alu and additionally a shift of the result by one to the left or right can be chosen.

Also, a counter-buffer can be loaded and conditional or nonconditional jumps utilized to set the counter i.e. jump to the address specified in the counter-buffer.

The current MBR-content can be saved by setting the AMUX, the current address of the counter itself by setting the BMUX.

To run a program, one must create a file called "bootloader" which may consist only of 32-bit-codes, meaning every line shall 
contain exactly 32 characters of either 0 or 1.  
you can also add empty lines (without any trailing space characters) or comments starting with # to your program  
The bits specified in those 32 characters have the following effects (order from left to right) ..  
2 bit: ALU (arithmetic operation)  
2 bit: SHIFT (left/right shift operation)  
3 bit: JUMP (jumping condition)  
3 bit: MEMMODE (memory mode)  
1 bit: SLOAD (load alu-result to reg\[S-SEL\])  
1 bit: CLOAD (load alu-result to counter-buffer)  
1 bit: AMUX (activate amux)  
1 bit: BMUX (activate bmux)  
6 bit: A-SEL (selector for which register shall be loaded into A-IN of alu)  
6 bit: B-SEL (selector for which register shall be loaded into B-IN of alu)  
6 bit: S-SEL (selector for which register (other than 0, 1 or 2) shall get the output from the alu)  
  
The bootloader-file in the repository contains an example-program, that initializes reg3=8, reg4=6 and then uses a multiplication
subroutine to multiply them. You can also initialize it with different numbers and it will still work! 

if the command 0 is used, the program will exit.

![micro32conceptual](micro32.png)
