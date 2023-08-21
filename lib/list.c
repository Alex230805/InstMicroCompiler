#define LIST_C
#include "list.h"

listHeader initializeHeader(){
    listHeader head;
    head.n = 0;
    head.pointer = NULL;
    head.first = NULL;
    return head;
}

romContainer initializeRomContainer(){

    romContainer romD;
    romDatabase * r1 = NULL;
    romDatabase * r2 = NULL;
    romDatabase * r3 = NULL;
    romDatabase * r4 = NULL;
    romDatabase * cp = NULL;

    r1 = (romDatabase*)malloc(sizeof(romDatabase));
    r2 = (romDatabase*)malloc(sizeof(romDatabase));
    r3 = (romDatabase*)malloc(sizeof(romDatabase));
    r4 = (romDatabase*)malloc(sizeof(romDatabase));

    r1->next = NULL;
    r2->next = NULL;
    r3->next = NULL;
    r4->next = NULL;

    romD.rom1 = r1;
    romD.rom2 = r2;
    romD.rom3 = r3;
    romD.rom4 = r4;
    romD.customPointer = NULL;
    return romD;
}

void loadDatabase(char hex_path[], char path[], romContainer * rom, romSelector type){
    FILE * mnemonic;
    FILE * hex;
    uint8_t buffer[256];
    strcpy(buffer, "0");
    if(((mnemonic = fopen(path,"r")) == NULL) || ((hex = fopen(hex_path,"r")) == NULL)){
        printf("\nCannot open indicated files, aborting\n");
        exit(0);
    }else{
        switch(type){
            case rom1:
                rom->customPointer = rom->rom1;
                while((fscanf(mnemonic, "%s\n", &buffer)) != EOF){
                    romDatabase*rp;
                    rp = (romDatabase*)malloc(sizeof(romDatabase));
                    rp->next = NULL;
                    strcpy(rom->customPointer->mnemonic, buffer);
                    rom->customPointer->next = rp;
                    rom->customPointer = rom->customPointer->next;
                }
                rom->customPointer->next = NULL;
                rom->customPointer = rom->rom1;
                while((fscanf(hex, "%s\n", &buffer)) != EOF){
                    strcpy(rom->customPointer->hex, buffer);
                    rom->customPointer = rom->customPointer->next;
                }
                break;

            case rom2:
                rom->customPointer = rom->rom2;
                while((fscanf(mnemonic, "%s\n", &buffer)) != EOF){
                    romDatabase*rp;
                    rp = (romDatabase*)malloc(sizeof(romDatabase));
                    rp->next = NULL;
                    strcpy(rom->customPointer->mnemonic, buffer);
                    rom->customPointer->next = rp;
                    rom->customPointer = rom->customPointer->next;
                }
                rom->customPointer->next = NULL;
                rom->customPointer = rom->rom2;
                while((fscanf(hex, "%s\n", &buffer)) != EOF){
                    strcpy(rom->customPointer->hex, buffer);
                    rom->customPointer = rom->customPointer->next;
                }
                break;

            case rom3:
                rom->customPointer = rom->rom3;
                while((fscanf(mnemonic, "%s\n", &buffer)) != EOF){
                    romDatabase*rp;
                    rp = (romDatabase*)malloc(sizeof(romDatabase));
                    rp->next = NULL;
                    strcpy(rom->customPointer->mnemonic, buffer);
                    rom->customPointer->next = rp;
                    rom->customPointer = rom->customPointer->next;
                }
                rom->customPointer->next = NULL;
                rom->customPointer = rom->rom3;
                while((fscanf(hex, "%s\n", &buffer)) != EOF){
                    strcpy(rom->customPointer->hex, buffer);
                    rom->customPointer = rom->customPointer->next;
                }
                break;

            case rom4:
                rom->customPointer = rom->rom4;
                while((fscanf(mnemonic, "%s\n", &buffer)) != EOF){
                    romDatabase*rp;
                    rp = (romDatabase*)malloc(sizeof(romDatabase));
                    rp->next = NULL;
                    strcpy(rom->customPointer->mnemonic, buffer);
                    rom->customPointer->next = rp;
                    rom->customPointer = rom->customPointer->next;
                }
                rom->customPointer->next = NULL;
                rom->customPointer = rom->rom4;
                while((fscanf(hex, "%s\n", &buffer)) != EOF){
                    strcpy(rom->customPointer->hex, buffer);
                    rom->customPointer = rom->customPointer->next;
                }
                break;
            default:
                printf("\nWrong Selection, aborting\n");
                exit(0);
                break;
        }
    }
    fclose(mnemonic);
    fclose(hex);
}

void listAddInstContent(listHeader * head, char inst[], int step, char add[]){
    node* dummy = NULL;
    dummy = (node*)malloc(sizeof(node));
    strcpy(dummy->name, inst);
    dummy->step = step;
    strcpy(dummy->ADDRESS,add);
    if(head->n == 0){
        head->pointer = dummy;
        head->first = dummy;
        head->n++;

    }else{
        while(head->pointer->next != NULL){
            head->pointer = head->pointer->next;
        }
        head->pointer->next = dummy;
        head->pointer = head->first;
        head->n++;
    }
}

void listAddInstNode(listHeader * head, node * n){
    if(head->n == 0){
        head->pointer = n;
        head->first = n;
        head->n++;
    }
    else{
        while(head->pointer->next != NULL){
            head->pointer = head->pointer->next;
        }
        head->pointer->next = n;
        head->pointer = head->first;
        head->n++;
    }
}

void extractFromDatabase(romContainer * rom, char data[], char out[], romSelector type){
    int found = 0;
    switch(type){
        case rom1:
                rom->customPointer = rom->rom1;
                while(rom->customPointer->next != NULL && found == 0){
                    if((strcmp(data, rom->customPointer->mnemonic)) == 0){
                        strcpy(out,rom->customPointer->hex);
                        found = 1;
                    }
                    rom->customPointer = rom->customPointer->next;
                }
                rom->customPointer = NULL;
                break;
        case rom2:
                rom->customPointer = rom->rom2;
                while(rom->customPointer->next != NULL && found == 0){
                    if((strcmp(data, rom->customPointer->mnemonic)) == 0){
                        strcpy(out,rom->customPointer->hex);
                        found = 1;
                    }else{
                        rom->customPointer = rom->customPointer->next;
                    }
                }
                rom->customPointer = NULL;
                break;
        case rom3:
                rom->customPointer = rom->rom3;
                while(rom->customPointer->next != NULL && found == 0){
                    if((strcmp(data, rom->customPointer->mnemonic)) == 0){
                        strcpy(out,rom->customPointer->hex);
                        found = 1;
                    }else{
                        rom->customPointer = rom->customPointer->next;
                    }
                }
                rom->customPointer = NULL;
                break;
        case rom4:
                rom->customPointer = rom->rom4;
                while(rom->customPointer->next != NULL && found == 0){
                    if((strcmp(data, rom->customPointer->mnemonic)) == 0){
                        strcpy(out,rom->customPointer->hex);
                        found = 1;
                    }else{
                        rom->customPointer = rom->customPointer->next;
                    }
                }
                rom->customPointer = NULL;
                break;
        default:
                printf("\nWrong Selection, aborting\n");
                exit(0);
                break;
    }
}

void freeList(node * n){
    if(n->next != NULL){
        n = n->next;
        freeList(n);
    }else{
        free(n);
    }
}

void freeISET(listHeader * head){
    freeList(head->pointer);
    head->pointer = NULL;
    head->first = NULL;
    head->n = 0;
}

void freeROM(romDatabase * rom){
    if(rom->next != NULL){
        rom = rom->next;
        freeROM(rom);
    }else{
        free(rom);
        rom = NULL;
    }
}

void freeRomDatabase(romContainer * rom){
    freeROM(rom->rom1);
    freeROM(rom->rom2);
    freeROM(rom->rom3);
    freeROM(rom->rom4);
    rom->customPointer = NULL;
}