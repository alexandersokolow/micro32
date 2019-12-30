#include <stdio.h>
#include <stdlib.h>

#define ALU ((command >> 29) & 7)
#define AMUX ((command >> 28) & 1)
#define CON ((command >> 24) & 15)
#define ASEL ((command >> 16) & 255)
#define BSEL ((command >> 8) & 255)
#define SSEL (command & 255)

#define MBR reg[252]
#define MAR reg[253]
#define JR reg[254]

typedef unsigned int bit32;

void bootLoader(bit32* memory);

void printStatus(bit32 *reg, bit32 counter, bit32 command, bit32 mbr, bit32 mar, bit32 jr);

int main(int argc, char *argv[]){

    bit32 memory[65536];
    for(int i = 0; i < 65536; i++) memory[i] = 0;
    
    bit32 reg[256];
    reg[0] = 0; //first register shall always be 0
    reg[1] = 1; //second register shall always be 1
    reg[255] = (bit32) -1; //third register shall always be -1

    bit32 counter = 0; 
    bit32 command = 0;

    bootLoader(memory);

    while(counter < 4095){
    
        int oldCounter = counter;
        command = memory[counter];
        if(command==0) break;

        bit32 aluA = AMUX ? counter : reg[ASEL];
        bit32 aluB = reg[BSEL];

        bit32 aluOUT;
        switch(ALU){
            case 0: aluOUT = aluA;
                    break;
            case 1: aluOUT = aluA>>1;
                    break;
            case 2: aluOUT = aluA<<1;
                    break;
            case 3: aluOUT = ~aluA;
                    break;
            case 4: aluOUT = aluA+aluB;
                    break;
            case 5: aluOUT = aluA+(~aluB)+1; //aluA-aluB in two's complement
                    break;
            case 6: aluOUT = aluA&aluB;
                    break;
            case 7: aluOUT = aluA|aluB;
                    break;
        }

        switch(CON){
            case 0: break;
            case 1: if(SSEL!=0 && SSEL!=1 && SSEL!=255) reg[SSEL] = aluOUT;
                    break;
            case 2: memory[MAR] = MBR;
                    break;
            case 3: MBR = memory[MAR];
                    break;
            case 4: counter = JR-1;
                    break;
            case 5: if(aluOUT==0) counter = JR-1;
                    break;
            case 6: if(aluOUT!=0) counter = JR-1;
                    break;
            case 7: if(aluOUT<0) counter = JR-1;
                    break;
            default: break;
        }

        counter++;
        
        printStatus(reg, oldCounter, command,MBR,MAR,JR);

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

void printStatus(bit32 *reg, bit32 counter, bit32 command, bit32 mbr, bit32 mar, bit32 jr){
    printf("COUNTER: %d\n\n", counter);

    printf("COMMAND: \n"); 
    printf("ALU: %d, AMUX: %d, CON: %d\n",ALU,AMUX,CON);
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

