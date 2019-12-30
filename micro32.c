#include <stdio.h>
#include <stdlib.h>

#define ALU1 ((command >> 31) & 1)
#define ALU2 ((command >> 30) & 1)
#define SHIFT1 ((command >> 29) & 1)
#define SHIFT2 ((command >> 28) & 1)
#define JUMP1 ((command >> 27) & 1)
#define JUMP2 ((command >> 26) & 1)
#define JUMP3 ((command >> 25) & 1)
#define MEM1 ((command >> 24) & 1)
#define MEM2 ((command >> 23) & 1)
#define MEM3 ((command >> 22) & 1)
#define SLOAD ((command >> 21) & 1)
#define CLOAD ((command >> 20) & 1)
#define AMUX ((command >> 19) & 1)
#define BMUX ((command >> 18) & 1)
#define ASEL1 ((command >> 17) & 1)
#define ASEL2 ((command >> 16) & 1)
#define ASEL3 ((command >> 15) & 1)
#define ASEL4 ((command >> 14) & 1)
#define ASEL5 ((command >> 13) & 1)
#define ASEL6 ((command >> 12) & 1)
#define BSEL1 ((command >> 11) & 1)
#define BSEL2 ((command >> 10) & 1)
#define BSEL3 ((command >> 9) & 1)
#define BSEL4 ((command >> 8) & 1)
#define BSEL5 ((command >> 7) & 1)
#define BSEL6 ((command >> 6) & 1)
#define SSEL1 ((command >> 5) & 1)
#define SSEL2 ((command >> 4) & 1)
#define SSEL3 ((command >> 3) & 1)
#define SSEL4 ((command >> 2) & 1)
#define SSEL5 ((command >> 1) & 1)
#define SSEL6 (command & 1)

#define ALU ALU2 + 2*ALU1
#define SHIFT SHIFT2 + 2*SHIFT1
#define MEM MEM3 + 2*MEM2 + 4*MEM1
#define JUMP JUMP3 + 2*JUMP2 + 4*JUMP1
#define AOUT ASEL6 + 2*ASEL5 + 4*ASEL4 + 8*ASEL3 + 16*ASEL2 + 32*ASEL1
#define BOUT BSEL6 + 2*BSEL5 + 4*BSEL4 + 8*BSEL3 + 16*BSEL2 + 32*BSEL1
#define SIN SSEL6 + 2*SSEL5 + 4*SSEL4 + 8*SSEL3 + 16*SSEL2 + 32*SSEL1

typedef unsigned int bit32;

void bootLoader(bit32* memory);

void printStatus(bit32 *reg, bit32 counter, bit32 command, bit32 mbr, bit32 mar, bit32 cbuf);

int main(int argc, char *argv[]){

    bit32 memory[65536];
    bit32 mar = 0;
    bit32 mbr = 0;
    for(int i = 0; i < 65536; i++) memory[i] = 0;
    
    bit32 reg[64];
    reg[0] = 0; //first register shall always be 0
    reg[1] = 1; //second register shall always be 1
    reg[2] = (bit32) -1; //third register shall always be -1

    bit32 counter = 0; 
    bit32 cbuf = 0;

    bit32 command = 0;

    bootLoader(memory);

    while(counter < 4095){
    
        command = memory[counter];
        if(command==0) break;

        bit32 aluA;
        bit32 aluB;
        if(AMUX) aluA = memory[mar]; 
        else aluA = reg[AOUT];
        if(BMUX) aluB = counter;
        else aluB = reg[BOUT]; 

        bit32 aluOUT;
        switch(ALU){
            case 0: aluOUT = aluA;
                    break;
            case 1: aluOUT = aluA+aluB;
                    break;
            case 2: aluOUT = aluA&aluB;
                    break;
            case 3: aluOUT = ~aluA;
                    break;
        }

        if(SHIFT == 1) aluOUT = aluOUT >> 1;
        if(SHIFT == 2) aluOUT = aluOUT << 1;

        if(SLOAD && SIN!=0 && SIN!=1 && SIN!=2) reg[SIN] = aluOUT;
        if(CLOAD) cbuf = aluOUT;
        if(MEM==1 || MEM==3) mar = aluOUT;
        if(MEM==2 || MEM==3) mbr = aluOUT; 
        if(MEM==4) memory[mar] = mbr;
        if(MEM==5) mbr = memory[mar];

        printStatus(reg, counter, command,mbr,mar,cbuf);

        switch(JUMP){
            case 0:
            case 1:
            case 2:
            case 3: counter++;
                    break;
            case 4: if(aluOUT==0) counter = cbuf;
                    else counter++;
                    break;
            case 5: if(aluOUT!=0) counter = cbuf;
                    else counter++;
                    break;
            case 6: if(aluOUT<0) counter = cbuf;
                    else counter++;
                    break;
            case 7: counter = cbuf;
                    break;
        }

    }

    exit(EXIT_SUCCESS);    
}

void bootLoader(bit32* memory){
    int i = 0;
    FILE* bootloader = fopen("bootloader","r");
    char* line = NULL;
    size_t len = 0;
    while(getline(&line, &len, bootloader)>0){
        if(line[0] != '\n' && line[0]!='#'){
            memory[i++] = (bit32) strtol(line, NULL, 2);
        }
        line = NULL;
        len = 0;
    }
}

void printStatus(bit32 *reg, bit32 counter, bit32 command, bit32 mbr, bit32 mar, bit32 cbuf){
    printf("COUNTER: %d\n\n", counter);

    printf("COMMAND: \n"); 
    printf("ALU: %d, SHIFT: %d, MEM: %d, JUMP: %d\n",ALU,SHIFT,MEM,JUMP);
    printf("SLOAD: %d, CLOAD: %d, AMUX: %d, BMUX: %d\n",SLOAD,CLOAD,AMUX,BMUX);
    printf("ASEL: %d, BSEL: %d, SSEL: %d\n", AOUT,BOUT,SIN);
    printf("\n");

    for(int i=0; i<8; i++){
        printf("REG %d: %d\n",i,reg[i]);
    }
    printf("\n");
    printf("MBR: %d\n",mbr);
    printf("MAR: %d\n",mar);
    printf("CBUF: %d\n",cbuf);
    printf("\n");
    printf("------------------------------------------------------------------------\n\n");
}

