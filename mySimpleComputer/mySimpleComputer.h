//
//  mySimpleComputer.h
//  mySimpleComputer
//
//  Created by Daniil G on 16.02.2018.
//  Copyright © 2018 Daniil G. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>

#ifndef mySimpleComputer_h
#define mySimpleComputer_h

#define memorySize 99
extern char flagsRegister;

#define OUT_MEMORY 0x01
#define ERROR_COMMAND 0x02

int RAM [memorySize];

int sc_memoryInit (); // a

int sc_memorySet (int address, int value); // b

int sc_memoryGet (int address, int * value); // c

int sc_memorySave (char * filename); // d

int sc_memoryLoad (char * filename); // e

int sc_regInit (void); // f
    
int sc_regSet (int registr, int value); //g

int sc_regGet (int registr, int * value); // h

int sc_commandEncode (int command, int operand, int *value); // i

int sc_commandDecode (int value, int *command, int *operand); // j

#endif /* mySimpleComputer_h */
