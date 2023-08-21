#include <stdio.h>
#include <stdlib.h>
#include "lib/list.h"
#include <ctype.h>

void showData(listHeader * InstructionList);

uint8_t hexStringConverter(char string[]);
int write(uint8_t buffer[], int opcode, int step, FILE * pointer);
uint8_t hexDigitConverter(char s);

//path to mnemonic microcode reference
char path_microcode_1[] = "./RomDatabase/rom1/micro.micunit";
char path_microcode_2[] = "./RomDatabase/rom2/micro.micunit";
char path_microcode_3[] = "./RomDatabase/rom3/micro.micunit";
char path_microcode_4[] = "./RomDatabase/rom4/micro.micunit";

//path to hexadecimal microcode reference
char path_hex_1[] = "./RomDatabase/rom1/rom_hex.micunit";
char path_hex_2[] = "./RomDatabase/rom2/rom_hex.micunit";
char path_hex_3[] = "./RomDatabase/rom3/rom_hex.micunit";
char path_hex_4[] = "./RomDatabase/rom4/rom_hex.micunit";
//path to binary file
char path_bin_1[] = "./out/rom1.bin";
char path_bin_2[] = "./out/rom2.bin";
char path_bin_3[] = "./out/rom3.bin";
char path_bin_4[] = "./out/rom4.bin";


char path_instruction_set[][64] = {
    {"./InstructionSet/x0_x1_x2/BRK"},
    {"./InstructionSet/x0_x1_x2/ORA_IND_X"},
    {"./InstructionSet/x0_x1_x2/ORA_Y_IND"},
    {"./InstructionSet/x0_x1_x2/AND_IND_X"},
    {"./InstructionSet/x0_x1_x2/AND_Y_IND"},
    {"./InstructionSet/x0_x1_x2/EOR_IND_X"},
    {"./InstructionSet/x0_x1_x2/EOR_Y_IND"},
    {"./InstructionSet/x0_x1_x2/ADC_IND_X"},
    {"./InstructionSet/x0_x1_x2/ADC_Y_IND"},
    {"./InstructionSet/x0_x1_x2/STA_IND_X"},
    {"./InstructionSet/x0_x1_x2/STA_Y_IND"},
    {"./InstructionSet/x0_x1_x2/LDA_IND_X"},
    {"./InstructionSet/x0_x1_x2/LDA_Y_IND"},
    {"./InstructionSet/x0_x1_x2/CMP_IND_X"},
    {"./InstructionSet/x0_x1_x2/CMP_Y_IND"},
    {"./InstructionSet/x0_x1_x2/SBC_IND_X"},
    {"./InstructionSet/x0_x1_x2/SBC_Y_IND"},
    {"./InstructionSet/x0_x1_x2/LDX_IMP"},
    {"./InstructionSet/x0_x1_x2/LDY_IMP"},
    {"./InstructionSet/x0_x1_x2/CPX_IMP"},
    {"./InstructionSet/x0_x1_x2/CPY_IMP"},

    {"./InstructionSet/x4_x5_x6/ADC_ZPG"},
    {"./InstructionSet/x4_x5_x6/ADC_ZPG_X"},
    {"./InstructionSet/x4_x5_x6/AND_ZPG"},
    {"./InstructionSet/x4_x5_x6/AND_ZPG_X"},
    {"./InstructionSet/x4_x5_x6/ASL_ZPG"},
    {"./InstructionSet/x4_x5_x6/ASL_ZPG_X"},
    {"./InstructionSet/x4_x5_x6/BIT_ZPG"},
    {"./InstructionSet/x4_x5_x6/CMP_ZPG"},
    {"./InstructionSet/x4_x5_x6/CMP_ZPG_X"},
    {"./InstructionSet/x4_x5_x6/CPX_ZPG"},
    {"./InstructionSet/x4_x5_x6/CPY_ZPG"},
    {"./InstructionSet/x4_x5_x6/DEC_ZPG"},
    {"./InstructionSet/x4_x5_x6/DEC_ZPG_X"},
    {"./InstructionSet/x4_x5_x6/EOR_ZPG"},
    {"./InstructionSet/x4_x5_x6/EOR_ZPG_X"},
    {"./InstructionSet/x4_x5_x6/INC_ZPG"},
    {"./InstructionSet/x4_x5_x6/INC_ZPG_X"},
    {"./InstructionSet/x4_x5_x6/LDA_ZPG"},
    {"./InstructionSet/x4_x5_x6/LDA_ZPG_X"},
    {"./InstructionSet/x4_x5_x6/LDX_ZPG"},
    {"./InstructionSet/x4_x5_x6/LDX_ZPG_Y"},
    {"./InstructionSet/x4_x5_x6/LDY_ZPG"},
    {"./InstructionSet/x4_x5_x6/LDY_ZPG_X"},
    {"./InstructionSet/x4_x5_x6/LSR_ZPG"},
    {"./InstructionSet/x4_x5_x6/LSR_ZPG_X"},
    {"./InstructionSet/x4_x5_x6/ORA_ZPG"},
    {"./InstructionSet/x4_x5_x6/ORA_ZPG_X"},
    {"./InstructionSet/x4_x5_x6/ROL_ZPG"},
    {"./InstructionSet/x4_x5_x6/ROL_ZPG_X"},
    {"./InstructionSet/x4_x5_x6/ROR_ZPG"},
    {"./InstructionSet/x4_x5_x6/ROR_ZPG_X"},
    {"./InstructionSet/x4_x5_x6/SBC_ZPG"},
    {"./InstructionSet/x4_x5_x6/SBC_ZPG_X"},
    {"./InstructionSet/x4_x5_x6/STA_ZPG"},
    {"./InstructionSet/x4_x5_x6/STA_ZPG_X"},
    {"./InstructionSet/x4_x5_x6/STX_ZPG"},
    {"./InstructionSet/x4_x5_x6/STX_ZPG_Y"},
    {"./InstructionSet/x4_x5_x6/STY_ZPG"},
    {"./InstructionSet/x4_x5_x6/STY_ZPG_X"},
};

const int INST_LIMIT = 60;

int main(){
    FILE * bin1;
    FILE * bin2;
    FILE * bin3;
    FILE * bin4;
    char sel;
    //define main struct 
    listHeader InstructionList = initializeHeader();
    romContainer RomData = initializeRomContainer();
    //load database
    loadDatabase(path_hex_1, path_microcode_1,&RomData, rom1);
    printf("1st rom -> database loaded\n");
    loadDatabase(path_hex_2, path_microcode_2,&RomData, rom2);
    printf("2nd rom -> database loaded\n");
    loadDatabase(path_hex_3, path_microcode_3,&RomData, rom3);
    printf("3rd rom -> database loaded\n");
    loadDatabase(path_hex_4, path_microcode_4,&RomData, rom4);
    printf("4th rom -> database loaded\n");
    printf("Start loading instruction set .. ");
    for(int i=0;i<INST_LIMIT;i++){
        char buffer_in_1[64][64];
        char buffer_in_2[64][64];
        char buffer_in_3[64][64];
        char buffer_in_4[64][64];
        node * n;
        FILE * inst; 
        if((inst = fopen(path_instruction_set[i], "r")) == NULL){
            exit(0);
        }else{
            n = (node*)malloc(sizeof(node));
            n->next = NULL;
            fscanf(inst, "%s %s %d\n", &n->name, &n->ADDRESS, &n->step);
            for(int i=0;i<n->step;i++){
                fscanf(inst, "%s %s %s %s", &buffer_in_4[i], &buffer_in_3[i], &buffer_in_2[i],&buffer_in_1[i]);
            }
            for(int i=0;i<n->step;i++){
                strcpy(n->microcode_rom1[i], buffer_in_1[i]);
                strcpy(n->microcode_rom2[i], buffer_in_2[i]);
                strcpy(n->microcode_rom3[i], buffer_in_3[i]);
                strcpy(n->microcode_rom4[i], buffer_in_4[i]);
            }
            listAddInstNode(&InstructionList,n);
        }
        fclose(inst);
    }
    printf("Done!\n");
    printf("Start traslating .. ");
    for(int i=0;i<INST_LIMIT;i++){
        char buffer_out_1[64][64];
        char buffer_out_2[64][64];
        char buffer_out_3[64][64];
        char buffer_out_4[64][64];
        for(int i=0;i<InstructionList.pointer->step;i++){
            extractFromDatabase(&RomData, InstructionList.pointer->microcode_rom1[i],buffer_out_1[i], rom1);
            extractFromDatabase(&RomData, InstructionList.pointer->microcode_rom2[i],buffer_out_2[i], rom2);
            extractFromDatabase(&RomData, InstructionList.pointer->microcode_rom3[i],buffer_out_3[i], rom3);
            extractFromDatabase(&RomData, InstructionList.pointer->microcode_rom4[i],buffer_out_4[i], rom4);

            strcpy(InstructionList.pointer->microcode_rom1[i],buffer_out_1[i]);
            strcpy(InstructionList.pointer->microcode_rom2[i],buffer_out_2[i]);
            strcpy(InstructionList.pointer->microcode_rom3[i],buffer_out_3[i]);
            strcpy(InstructionList.pointer->microcode_rom4[i],buffer_out_4[i]);
        }
        if(InstructionList.pointer->next != NULL){
            InstructionList.pointer = InstructionList.pointer->next;
        }

    }
    printf("Done!\n");
    InstructionList.pointer = InstructionList.first;
    printf("Start dumping .. ");
    bin1 = fopen(path_bin_1, "w+b");
    bin2 = fopen(path_bin_2, "w+b");
    bin3 = fopen(path_bin_3, "w+b");
    bin4 = fopen(path_bin_4, "w+b");
    if(bin1 == NULL || bin2 == NULL || bin3 == NULL || bin4 == NULL){
        printf("\nFailed while opening output binary file, aborting ..\n");
        exit(0);
    }else{
        uint8_t buffer_out_1[64];
        uint8_t buffer_out_2[64];
        uint8_t buffer_out_3[64];
        uint8_t buffer_out_4[64];
        for(int i=0;i<INST_LIMIT;i++){
            for(int i=0;i<InstructionList.pointer->step;i++){
                buffer_out_1[i] = hexStringConverter(InstructionList.pointer->microcode_rom1[i]);
                buffer_out_2[i] = hexStringConverter(InstructionList.pointer->microcode_rom2[i]);
                buffer_out_3[i] = hexStringConverter(InstructionList.pointer->microcode_rom3[i]);
                buffer_out_4[i] = hexStringConverter(InstructionList.pointer->microcode_rom4[i]);
            }
            uint8_t address = hexStringConverter(InstructionList.pointer->ADDRESS);
            write(buffer_out_1, address ,InstructionList.pointer->step,bin1);
            write(buffer_out_2, address ,InstructionList.pointer->step,bin2);
            write(buffer_out_3, address ,InstructionList.pointer->step,bin3);
            write(buffer_out_4, address ,InstructionList.pointer->step,bin4);
            if(InstructionList.pointer->next != NULL){
                InstructionList.pointer = InstructionList.pointer->next;
            }
        }
    }
    fclose(bin1);
    fclose(bin2);
    fclose(bin3);
    fclose(bin4);
    printf("Done!\n");
    InstructionList.pointer = InstructionList.first;
    printf("Show written data? (Y/N): ");
    scanf("%c", &sel);
    if(sel == 'Y' || sel == 'y'){
        showData(&InstructionList);
    }
    InstructionList.pointer = InstructionList.first;
    freeISET(&InstructionList);
    printf("Memory clear: instruction set\n");
    freeRomDatabase(&RomData);
    printf("Memory clear: Rom Container ( aka: RomDatabase )\n");
    return 0;
}


void showData(listHeader * InstructionList){
    printf("\nData written to memory: \n\n");
    for(int i=0;i<INST_LIMIT;i++){
        printf("\nInstruction name: %s\n", InstructionList->pointer->name);
        printf("Instruction steps: %d\n", InstructionList->pointer->step);
        printf("Instruction address: %s\n", InstructionList->pointer->ADDRESS);
        for(int i=0;i<InstructionList->pointer->step;i++){
            printf("Data from step %d : %s %s %s %s\n", i+1, InstructionList->pointer->microcode_rom4[i],InstructionList->pointer->microcode_rom3[i],InstructionList->pointer->microcode_rom2[i],InstructionList->pointer->microcode_rom1[i]);
        }
        if(InstructionList->pointer->next != NULL){
            InstructionList->pointer = InstructionList->pointer->next;
        }
    }
}





uint8_t hexDigitConverter(char s){
    if(isdigit(s)){
        return s - '0';
    }else{
         return toupper(s) - 'A' + 10;
    }
}

uint8_t hexStringConverter(char string[]){
    uint8_t HexString = 0;
    int len = strlen(string);
    for(int i=0;i<len;i++){
        if(!isxdigit(string[i]))
            return -1;
       int cache = hexDigitConverter(string[i]);
       HexString = (HexString << 4) | cache; 
    }
    return HexString;
}

int write(uint8_t buffer[], int opcode, int step, FILE *pointer){
    int statusOp = 0;
    uint16_t address = 0x0000;
    for(int i=0;i<step;i++){
        uint16_t wAdr = address | opcode;
        fseek(pointer ,wAdr, SEEK_SET);
        fwrite(&buffer[i],sizeof(char), 1, pointer);
        address= (address >> 8) & 0xFF;
        address ++;
        if(address > 0xFF){
            address &= 0xFF;
        }
        address = (address << 8) | (opcode & 0xFF);
    }
    statusOp = 1;
    return statusOp;
}
