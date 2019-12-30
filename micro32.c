#include <stdio.h>
#include <stdlib.h>

#define ALU1 ((command >> 31) & 1)
#define ALU2 ((command >> 30) & 1)
#define SHIFT1 ((command >> 29) & 1)
#define SHIFT2 ((command >> 28) & 1)
#define MEMMODE1 ((command >> 27) & 1)
#define MEMMODE2 ((command >> 26) & 1)
#define JUMP1 ((command >> 25) & 1)
#define JUMP2 ((command >> 24) & 1)
#define ASEL1 ((command >> 23) & 1)
#define ASEL2 ((command >> 22) & 1)
#define ASEL3 ((command >> 21) & 1)
#define ASEL4 ((command >> 20) & 1)
#define BSEL1 ((command >> 19) & 1)
#define BSEL2 ((command >> 18) & 1)
#define BSEL3 ((command >> 17) & 1)
#define BSEL4 ((command >> 16) & 1)
#define SSEL1 ((command >> 15) & 1)
#define SSEL2 ((command >> 14) & 1)
#define SSEL3 ((command >> 13) & 1)
#define SSEL4 ((command >> 12) & 1)

#define ALU ALU2 + 2*ALU1
#define SHIFT SHIFT2 + 2*SHIFT1
#define MEMMODE MEMMODE2 + 2*MEMMODE1
#define JUMP JUMP2 + 2*JUMP1
#define AOUT ASEL4 + 2*ASEL3 + 4*ASEL2 + 8*ASEL1
#define BOUT BSEL4 + 2*BSEL3 + 4*BSEL2 + 8*BSEL1
#define SIN SSEL4 + 2*SSEL3 + 4*SSEL2 + 8*SSEL1

#define JUMPADR (command & 4095)

typedef unsigned int bit32;

void bootLoader(bit32* memory);

void printStatus(bit32 *reg, bit32 counter, bit32 command);

int main(int argc, char *argv[]){

    bit32 memory[65536];
    bit32 mar = 0;
    for(int i = 0; i < 65536; i++) memory[i] = 0;
    
    bit32 reg[16];
    reg[0] = 0; //first register shall always be 0
    reg[1] = 1; //second register shall always be 1

    bit32 counter = 0; 
    bit32 command = 0;

    bootLoader(memory);

    while(counter < 4095){
    
        command = memory[counter];

        bit32 aluA;
        if(MEMMODE == 3) aluA = memory[mar]; 
        else aluA = reg[AOUT];
        bit32 aluB = reg[BOUT]; 

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

        if(SIN!=0 && SIN!=1) reg[SIN] = aluOUT;
        if(MEMMODE==1) mar = aluOUT;
        if(MEMMODE==2) memory[mar] = aluOUT;

        printStatus(reg, counter, command);

        switch(JUMP){
            case 0: counter++;
                    break;
            case 1: if(aluOUT==0) counter = JUMPADR;
                    else counter++;
                    break;
            case 2: if(aluOUT<0) counter = JUMPADR;
                    else counter++;
                    break;
            case 3: counter = JUMPADR;
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

void printStatus(bit32 *reg, bit32 counter, bit32 command){
    printf("------------------------------------------------------------------------\n\n");
    printf("COMMAND:\n"); 
    printf("ALU: %d, SHIFT: %d, MEMMODE: %d, JUMP: %d\n",ALU,SHIFT,MEMMODE,JUMP);
    printf("ASEL: %d, BSEL: %d, SSEL: %d, JUMPADR: %d\n", AOUT,BOUT,SIN,JUMPADR);
    printf("\n");
    printf("COUNTER: %d\n\n", counter);
    for(int i=0; i<16; i++){
        printf("REG %d: %d\n",i,reg[i]);
    }
    printf("\n");
}

