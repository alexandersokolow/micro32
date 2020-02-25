// MICRO 32: Van-Neumann-Architecture Processor Simulator
// Author: Alexander Sokolow

#include <stdio.h>
#include <stdlib.h>

#define ALUF ((command >> 30) & 3)
#define ALUN ((command >> 29) & 1)
#define JUMP ((command >> 28) & 1)
#define JFLG ((command >> 26) & 3)
#define MS ((command >> 25) & 1)
#define RDWR ((command >> 24) & 1)
#define ASEL ((command >> 16) & 255)
#define BSEL ((command >> 8) & 255)
#define SSEL (command & 255)

#define MBR reg[251]
#define MAR reg[252]
#define JR reg[253]
#define PC reg[254]

typedef unsigned int bit32;

void bootLoader(bit32* memory);

void printStatus(bit32 *reg, bit32 pc, bit32 command, bit32 mbr, bit32 mar, bit32 jr);

int main(int argc, char *argv[]){

    bit32 memory[65536];
    bit32 reg[256];

    for(int i = 0; i < 65536; i++) memory[i] = 0;
    for(int i = 0; i < 256; i++) reg[i] = 0;

    bootLoader(memory);
    reg[0] = 0;
    reg[1] = 1;
    reg[255] = (bit32) -1;

    //Processor-Loop
    while(PC < 4095){
    
        //Clock-Phase 1: Fetch Instruction, PC++;
        bit32 command = memory[PC];
        if(command==0) break;

        int oldPC = PC;
        PC++;

        //Clock-Phase 2: ALU 
        bit32 aluA = reg[ASEL];
        bit32 aluB = reg[BSEL];

        bit32 aluOUT;
        switch(ALUF){
            case 0: aluOUT = aluA;
                    break;
            case 1: aluOUT = aluA&aluB;
                    break;
            case 2: aluOUT = aluA|aluB;
                    break;
            case 3: aluOUT = aluA+aluB;
                    break;
        }

        if(ALUN){
            aluOUT = ~aluOUT;
        }

        bit32 flagC = (aluOUT >> 31) == 1 ? 1 : 0;
        bit32 flagZ = aluOUT == 0 ? 1 : 0;

        //Clock-Phase 3: Load S 
        if(SSEL!=0 && SSEL!= 1 && SSEL != 255 && SSEL != 254){
            reg[SSEL]=aluOUT;
        }
        
        //Clock-Phase 4: MEMORY & JUMP
        if(MS){
            if(RDWR){
                MBR = memory[MAR];
            }
            else{
                memory[MAR] = MBR;
            }
        }

        if(JUMP){
            if((JFLG == 0)||((JFLG == 1) && (flagZ==1))||((JFLG == 2) && (flagZ==0))||((JFLG == 3)&&(flagC==1))){
                PC = JR;
            }
        }

        //Simulator:
        printStatus(reg, oldPC, command,MBR,MAR,JR);
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

void printStatus(bit32 *reg, bit32 pc, bit32 command, bit32 mbr, bit32 mar, bit32 jr){

    printf("PC: %d\n\n", pc);

    printf("COMMAND: \n"); 
    printf("ALUF: %d, ALUN: %d, JUMP: %d, JFLG: %d, MS: %d, RDWR: %d\n",ALUF,ALUN,JUMP,JFLG,MS,RDWR);
    printf("ASEL: %d, BSEL: %d, SSEL: %d\n", ASEL,BSEL,SSEL);
    printf("\n");

    for(int i=2; i<8; i++){
        printf("REG %d: %d\n",i,reg[i]);
    }
    printf("\n");
    printf("MBR: %d\n",mbr);
    printf("MAR: %d\n",mar);
    printf("JR: %d\n",jr);
    printf("\n");

    printf("------------------------------------------------------------------------\n\n");

}

