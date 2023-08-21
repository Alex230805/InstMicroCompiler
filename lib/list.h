#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>



#define MAX_MICRO_END 64
typedef enum{rom1, rom2, rom3,rom4}romSelector;


typedef struct n{
    int step;
    char ADDRESS[5];
    char name[16];
    char microcode_rom1[MAX_MICRO_END][MAX_MICRO_END];
    char microcode_rom2[MAX_MICRO_END][MAX_MICRO_END];
    char microcode_rom3[MAX_MICRO_END][MAX_MICRO_END];
    char microcode_rom4[MAX_MICRO_END][MAX_MICRO_END];
    struct n* next;
}node;

typedef struct{
    int n;
    node* pointer;
    node* first;
}listHeader;

typedef struct rd{
    char mnemonic[MAX_MICRO_END];
    char hex[MAX_MICRO_END];
    struct rd* next;
}romDatabase;

typedef struct{
    romDatabase * rom1;
    romDatabase * rom2;
    romDatabase * rom3;
    romDatabase * rom4;

    romDatabase * customPointer;
}romContainer;




listHeader initializeHeader();
romContainer initializeRomContainer();
void listAddInstContent(listHeader * head, char inst[], int step, char add[]);
void listAddInstNode(listHeader * head, node * n);

void loadDatabase(char hex_path[], char path[], romContainer * rom, romSelector type);

void extractFromDatabase(romContainer * rom, char data[], char out[], romSelector type);

void freeISET(listHeader * head);
void freeList(node * n);

void freeRomDatabase(romContainer * rom);
void freeROM(romDatabase * rom);


#ifndef LIST_C
#define LIST_C

#endif

#endif