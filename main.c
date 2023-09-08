#include <stdio.h>
#include <stdlib.h>
#include "lib/list.h"
#include <ctype.h>

void showData(listHeader * InstructionList);

uint16_t hexStringConverter(char string[]);
int write(uint8_t buffer[], uint16_t opcode, int step, FILE * pointer);
uint16_t hexDigitConverter(char s);

//path to mnemonic microcode reference
char path_microcode_1[] = "./RomDatabase/rom1/micro.micunit";
char path_microcode_2[] = "./RomDatabase/rom2/micro.micunit";
char path_microcode_3[] = "./RomDatabase/rom3/micro.micunit";
char path_microcode_4[] = "./RomDatabase/rom4/micro.micunit";
char path_microcode_5[] = "./RomDatabase/flag_rom/micro.f";

//path to hexadecimal microcode reference
char path_hex_1[] = "./RomDatabase/rom1/rom_hex.micunit";
char path_hex_2[] = "./RomDatabase/rom2/rom_hex.micunit";
char path_hex_3[] = "./RomDatabase/rom3/rom_hex.micunit";
char path_hex_4[] = "./RomDatabase/rom4/rom_hex.micunit";
char path_hex_5[] = "./RomDatabase/flag_rom/rom_hex.f";
//path to binary file
char path_bin_1[] = "./out/rom1.bin";
char path_bin_2[] = "./out/rom2.bin";
char path_bin_3[] = "./out/rom3.bin";
char path_bin_4[] = "./out/rom4.bin";
char path_bin_5[] = "./out/flag_rom.bin";


char path_instruction_set[][128] = {
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
    {"./InstructionSet/x0_x1_x2/JSR"},
    {"./InstructionSet/x0_x1_x2/RTS"},
    {"./InstructionSet/x0_x1_x2/RTI"},

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

    {"./InstructionSet/x8_x9_xA/ADC_ABS_Y"},
    {"./InstructionSet/x8_x9_xA/ADC_IMP"},
    {"./InstructionSet/x8_x9_xA/AND_ABS_Y"},
    {"./InstructionSet/x8_x9_xA/AND_IMP"},
    {"./InstructionSet/x8_x9_xA/ASL_A"},
    {"./InstructionSet/x8_x9_xA/CLC"},
    {"./InstructionSet/x8_x9_xA/CLD"},
    {"./InstructionSet/x8_x9_xA/CLI"},
    {"./InstructionSet/x8_x9_xA/CLV"},
    {"./InstructionSet/x8_x9_xA/CMP_ABS_Y"},
    {"./InstructionSet/x8_x9_xA/CMP_IMP"},
    {"./InstructionSet/x8_x9_xA/DEX"},
    {"./InstructionSet/x8_x9_xA/DEY"},
    {"./InstructionSet/x8_x9_xA/EOR_ABS_Y"},
    {"./InstructionSet/x8_x9_xA/EOR_IMP"},
    {"./InstructionSet/x8_x9_xA/INX"},
    {"./InstructionSet/x8_x9_xA/INY"},
    {"./InstructionSet/x8_x9_xA/LDA_ABS_Y"},
    {"./InstructionSet/x8_x9_xA/LDA_IMP"},
    {"./InstructionSet/x8_x9_xA/LSR_A"},
    {"./InstructionSet/x8_x9_xA/NOP"},
    {"./InstructionSet/x8_x9_xA/ORA_ABS_Y"},
    {"./InstructionSet/x8_x9_xA/ORA_IMP"},
    {"./InstructionSet/x8_x9_xA/PHA"},
    {"./InstructionSet/x8_x9_xA/PHP"},
    {"./InstructionSet/x8_x9_xA/PLA"},
    {"./InstructionSet/x8_x9_xA/PLP"},
    {"./InstructionSet/x8_x9_xA/ROL_A"},
    {"./InstructionSet/x8_x9_xA/ROR_A"},
    {"./InstructionSet/x8_x9_xA/SBC_ABS_Y"},
    {"./InstructionSet/x8_x9_xA/SBC_IMP"},
    {"./InstructionSet/x8_x9_xA/SEC"},
    {"./InstructionSet/x8_x9_xA/SED"},
    {"./InstructionSet/x8_x9_xA/SEI"},
    {"./InstructionSet/x8_x9_xA/STA_ABS_Y"},
    {"./InstructionSet/x8_x9_xA/TAX"},
    {"./InstructionSet/x8_x9_xA/TAY"},
    {"./InstructionSet/x8_x9_xA/TSX"},
    {"./InstructionSet/x8_x9_xA/TXA"},
    {"./InstructionSet/x8_x9_xA/TXS"},
    {"./InstructionSet/x8_x9_xA/TYA"},

    {"./InstructionSet/xC_xD_xE/ADC_ABS"},
    {"./InstructionSet/xC_xD_xE/ADC_ABS_X"},
    {"./InstructionSet/xC_xD_xE/AND_ABS"},
    {"./InstructionSet/xC_xD_xE/AND_ABS_X"},
    {"./InstructionSet/xC_xD_xE/ASL_ABS"},
    {"./InstructionSet/xC_xD_xE/ASL_ABS_X"},
    {"./InstructionSet/xC_xD_xE/BIT_ABS"},
    {"./InstructionSet/xC_xD_xE/CMP_ABS"},
    {"./InstructionSet/xC_xD_xE/CMP_ABS_X"},
    {"./InstructionSet/xC_xD_xE/CPX_ABS"},
    {"./InstructionSet/xC_xD_xE/CPY_ABS"},
    {"./InstructionSet/xC_xD_xE/DEC_ABS"},
    {"./InstructionSet/xC_xD_xE/DEC_ABS_X"},
    {"./InstructionSet/xC_xD_xE/EOR_ABS"},
    {"./InstructionSet/xC_xD_xE/EOR_ABS_X"},
    {"./InstructionSet/xC_xD_xE/INC_ABS"},
    {"./InstructionSet/xC_xD_xE/INC_ABS_X"},
    {"./InstructionSet/xC_xD_xE/INTERRUPT"},
    {"./InstructionSet/xC_xD_xE/JMP_ABS"},
    {"./InstructionSet/xC_xD_xE/JMP_IND"},
    {"./InstructionSet/xC_xD_xE/LDA_ABS"},
    {"./InstructionSet/xC_xD_xE/LDA_ABS_X"},
    {"./InstructionSet/xC_xD_xE/LDX_ABS"},
    {"./InstructionSet/xC_xD_xE/LDX_ABS_Y"},
    {"./InstructionSet/xC_xD_xE/LDY_ABS"},
    {"./InstructionSet/xC_xD_xE/LDY_ABS_X"},
    {"./InstructionSet/xC_xD_xE/LSR_ABS"},
    {"./InstructionSet/xC_xD_xE/LSR_ABS_X"},
    {"./InstructionSet/xC_xD_xE/NMI"},
    {"./InstructionSet/xC_xD_xE/ORA_ABS"},
    {"./InstructionSet/xC_xD_xE/ORA_ABS_X"},
    {"./InstructionSet/xC_xD_xE/RESET"},
    {"./InstructionSet/xC_xD_xE/ROL_ABS"},
    {"./InstructionSet/xC_xD_xE/ROL_ABS_X"},
    {"./InstructionSet/xC_xD_xE/ROR_ABS"},
    {"./InstructionSet/xC_xD_xE/ROR_ABS_X"},
    {"./InstructionSet/xC_xD_xE/SBC_ABS"},
    {"./InstructionSet/xC_xD_xE/SBC_ABS_X"},
    {"./InstructionSet/xC_xD_xE/STA_ABS"},
    {"./InstructionSet/xC_xD_xE/STA_ABS_X"},
    {"./InstructionSet/xC_xD_xE/STARTUP"},
    {"./InstructionSet/xC_xD_xE/STX_ABS"},
    {"./InstructionSet/xC_xD_xE/STY_ABS"},

    {"./InstructionSet/conditional_branching/not_taken/BCC"},
    {"./InstructionSet/conditional_branching/not_taken/BCS"},
    {"./InstructionSet/conditional_branching/not_taken/BEQ"},
    {"./InstructionSet/conditional_branching/not_taken/BMI"},
    {"./InstructionSet/conditional_branching/not_taken/BNE"},
    {"./InstructionSet/conditional_branching/not_taken/BPL"},
    {"./InstructionSet/conditional_branching/not_taken/BVC"},
    {"./InstructionSet/conditional_branching/not_taken/BVS"},

    {"./InstructionSet/conditional_branching/taken/BCC"},
    {"./InstructionSet/conditional_branching/taken/BCS"},
    {"./InstructionSet/conditional_branching/taken/BEQ"},
    {"./InstructionSet/conditional_branching/taken/BMI"},
    {"./InstructionSet/conditional_branching/taken/BNE"},
    {"./InstructionSet/conditional_branching/taken/BPL"},
    {"./InstructionSet/conditional_branching/taken/BVC"},
    {"./InstructionSet/conditional_branching/taken/BVS"},


    {"./InstructionSet/flag_rom/BCC"},
    {"./InstructionSet/flag_rom/BCS"},
    {"./InstructionSet/flag_rom/BEQ"},
    {"./InstructionSet/flag_rom/BMI"},
    {"./InstructionSet/flag_rom/BNE"},
    {"./InstructionSet/flag_rom/BPL"},
    {"./InstructionSet/flag_rom/BVC"},
    {"./InstructionSet/flag_rom/BVS"}
};

const int INST_LIMIT = 163;

int main(){
    FILE * bin1;
    FILE * bin2;
    FILE * bin3;
    FILE * bin4;
    FILE * bin5;
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
    loadDatabase(path_hex_5, path_microcode_5, &RomData, rom5);
    printf("5ft rom -> database loaded\n");
    printf("Start loading instruction set .. ");
    for(int i=0;i<INST_LIMIT+8;i++){
        char buffer_in_1[64][64];
        char buffer_in_2[64][64];
        char buffer_in_3[64][64];
        char buffer_in_4[64][64];
        char buffer_in_5[64][64];
        node * n;
        FILE * inst; 
        if((inst = fopen(path_instruction_set[i], "r")) == NULL){
            exit(0);
        }else{
            n = (node*)malloc(sizeof(node));
            n->next = NULL;
            fscanf(inst, "%s %s %d", &n->name, &n->ADDRESS, &n->step);
            if(i >= INST_LIMIT){
                for(int z=0;z<n->step;z++){
                    fscanf(inst, "%s", &buffer_in_5[z]);
                }
            }else{
                for(int z=0;z<n->step;z++){
                    fscanf(inst, "%s %s %s %s", &buffer_in_4[z], &buffer_in_3[z],&buffer_in_2[z],&buffer_in_1[z]);
                }
            }
            if(i >= INST_LIMIT){
                for(int z=0;z<n->step;z++){
                    strcpy(n->microcode_rom5[z], buffer_in_5[z]);
                }
                printf("Flag/status requeset Instructions parsed: %d\n", i+1);
            }else{
                for(int z=0;z<n->step;z++){
                    strcpy(n->microcode_rom1[z], buffer_in_1[z]);
                    strcpy(n->microcode_rom2[z], buffer_in_2[z]);
                    strcpy(n->microcode_rom3[z], buffer_in_3[z]);
                    strcpy(n->microcode_rom4[z], buffer_in_4[z]);
                }
                printf("Instructions parsed: %d\n", i+1);
            }
            listAddInstNode(&InstructionList,n);
        }
        fclose(inst);
    }
    printf("Done!\n");


    printf("Start traslating .. ");
    for(int i=0;i<INST_LIMIT+8;i++){
        char buffer_out_1[64][64];
        char buffer_out_2[64][64];
        char buffer_out_3[64][64];
        char buffer_out_4[64][64];
        char buffer_out_5[64][64];
        for(int z=0;z<InstructionList.pointer->step;z++){
            if(i >= INST_LIMIT){
                extractFromDatabase(&RomData, InstructionList.pointer->microcode_rom5[z], buffer_out_5[z], rom5);
                printf("Info extracted in micro-step %d for flag return control signal %s: %s\n",i+1,InstructionList.pointer->name,buffer_out_5[z]);
                strcpy(InstructionList.pointer->microcode_rom5[z], buffer_out_5[z]);
            }else{
                if((strcmp(InstructionList.pointer->name, "BEQ")) == 0){
                    printf("Address BEQ: %s, step: %d\n", InstructionList.pointer->ADDRESS, InstructionList.pointer->step);
                }
                extractFromDatabase(&RomData, InstructionList.pointer->microcode_rom1[z],buffer_out_1[z], rom1);
                extractFromDatabase(&RomData, InstructionList.pointer->microcode_rom2[z],buffer_out_2[z], rom2);
                extractFromDatabase(&RomData, InstructionList.pointer->microcode_rom3[z],buffer_out_3[z], rom3);
                extractFromDatabase(&RomData, InstructionList.pointer->microcode_rom4[z],buffer_out_4[z], rom4);
                printf("Info extracted in micro-step %d for instruction %s : %s %s %s %s\n",i+1,InstructionList.pointer->name,buffer_out_4[z],buffer_out_3[z],buffer_out_2[z],buffer_out_1[z]);
                strcpy(InstructionList.pointer->microcode_rom1[z],buffer_out_1[z]);
                strcpy(InstructionList.pointer->microcode_rom2[z],buffer_out_2[z]);
                strcpy(InstructionList.pointer->microcode_rom3[z],buffer_out_3[z]);
                strcpy(InstructionList.pointer->microcode_rom4[z],buffer_out_4[z]);
            }
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
    bin5 = fopen(path_bin_5, "w+b");
    if(bin1 == NULL || bin2 == NULL || bin3 == NULL || bin4 == NULL || bin5 == NULL){
        printf("\nFailed while opening output binary file, aborting ..\n");
        exit(0);
    }else{
        uint8_t buffer_out_1[64];
        uint8_t buffer_out_2[64];
        uint8_t buffer_out_3[64];
        uint8_t buffer_out_4[64];
        uint8_t buffer_out_5[64];
        for(int i=0;i<INST_LIMIT+8;i++){
            if(i >= INST_LIMIT){
                for(int z=0;z<InstructionList.pointer->step;z++){
                    buffer_out_5[z] = hexStringConverter(InstructionList.pointer->microcode_rom5[z]);
                }
            }else{
                for(int z=0;z<InstructionList.pointer->step;z++){
                    buffer_out_1[z] = hexStringConverter(InstructionList.pointer->microcode_rom1[z]);
                    buffer_out_2[z] = hexStringConverter(InstructionList.pointer->microcode_rom2[z]);
                    buffer_out_3[z] = hexStringConverter(InstructionList.pointer->microcode_rom3[z]);
                    buffer_out_4[z] = hexStringConverter(InstructionList.pointer->microcode_rom4[z]);
                }
            }
            if(i >= INST_LIMIT){
                uint16_t address_f = hexStringConverter(InstructionList.pointer->ADDRESS);
                write(buffer_out_5, address_f, InstructionList.pointer->step,bin5);
            }else{
                uint16_t address = hexStringConverter(InstructionList.pointer->ADDRESS);
                write(buffer_out_1, address ,InstructionList.pointer->step,bin1);
                write(buffer_out_2, address ,InstructionList.pointer->step,bin2);
                write(buffer_out_3, address ,InstructionList.pointer->step,bin3);
                write(buffer_out_4, address ,InstructionList.pointer->step,bin4);
            }
            if(InstructionList.pointer->next != NULL){
                InstructionList.pointer = InstructionList.pointer->next;
            }
        }
    }
    fclose(bin1);
    fclose(bin2);
    fclose(bin3);
    fclose(bin4);
    fclose(bin5);
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





uint16_t hexDigitConverter(char s){
    if(isdigit(s)){
        return s - '0';
    }else{
         return toupper(s) - 'A' + 10;
    }
}

uint16_t hexStringConverter(char string[]){
    uint16_t HexString = 0;
    int len = strlen(string);
    for(int i=0;i<len;i++){
        if(!isxdigit(string[i]))
            return -1;
       int cache = hexDigitConverter(string[i]);
       HexString = (HexString << 4) | cache; 
    }
    return HexString;
}

int write(uint8_t buffer[], uint16_t opcode, int step, FILE *pointer){
    int statusOp = 0;
    uint16_t address = 0x0000;
    for(int i=0;i<step;i++){
        uint16_t wAdr = address | opcode;
        fseek(pointer ,wAdr, SEEK_SET);
        fwrite(&buffer[i],sizeof(char), 1, pointer);
        address = (address >> 8) & 0xFF;
        address++;
        if(address > 0xFF){
            address &= 0xFF;
        }
        address = (address << 8) & 0xFF00;
        address = (opcode & 0xFFFF) | address;
    }
    statusOp = 1;
    return statusOp;
}
