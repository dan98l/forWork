//
//  mySimpleComputer.c
//  mySimpleComputer
//
//  Created by Daniil G on 16.02.2018.
//  Copyright © 2018 Daniil G. All rights reserved.
//

#include "mySimpleComputer.h"

char flagsRegister = 0;

int sc_memoryInit (){ // a
    
    for (int i = 0; i < memorySize; i++) {
        RAM [i] = 0;
    }
    
    return 0;
}


int sc_memorySet (int address, int value){ // b
    
    if (address >= 0 && address <= memorySize ) {
        
            RAM [address] = value;
        
    } else {
        
        sc_regSet (OUT_MEMORY, 1);
        
        return 1;
        
    }
    
    return 0;
}


int sc_memoryGet (int address, int * value){ // c
    
    if (address >= 0 && address <= memorySize && value != NULL) {
        
        * value = RAM [address];
        
    } else {
        
        sc_regSet (OUT_MEMORY, 1);
        
        return 1;
        
    }
    
    return 0;
}


int sc_memorySave (char * filename){ // d
   
    FILE *ptrFile;
    
    ptrFile = fopen("RAMsave.txt", "wb");
    
        if(ptrFile == NULL){
        
            return 1;
        
        }
    
    fwrite(RAM, sizeof(int), memorySize, ptrFile);
    
    fclose(ptrFile);
    
    return 0;
}


int sc_memoryLoad (char * filename){ // e
    
    FILE *ptrFile;
    
    ptrFile = fopen("RAMsave.txt", "rb");
    
        if(ptrFile == NULL){
            
            return 1;
        }
    
    fread(RAM, sizeof(int), memorySize, ptrFile);
    
    fclose(ptrFile);
    
    return 0;
}


int sc_regInit (void){ // f
    
    flagsRegister = 0;
    
    return 0;
}


int sc_regSet (int registr, int value){ // g
    
    // if value register
    
    if(value == 1){
        
        flagsRegister = flagsRegister | 0x01 << registr;
    
    } else {
        
        flagsRegister &= ~(0x01 << registr);
    }
   
    return 0;
}


int sc_regGet (int registr, int * value){ // h
    
    // if value register
    
    if(*value == 1){
            
        flagsRegister |= 0x01<<registr;
            
    } if(value == 0) {
            
        flagsRegister &= ~(0x01<<registr);
            
    } else {
            
        return 1;
    }
    
    return 0;
}


int sc_commandEncode (int command, int operand, int *value){ // i
    
    if(operand < 0 || operand >= 128){
        
        return 2;
    }
    
    if(value == NULL){
        
        return 3;
    }
    
    if((command == 0x10) || (command == 0x11) || (command == 0x20) || (command == 0x21) ||
       (command >= 0x40 && command <= 0x43) || (command >= 0x51 && command <= 0x59) ||
       (command >= 0x60 && command <= 0x69) || (command >= 0x70 && command <= 0x76)){
        // encoding
        
        *value = 0;
        
        *value = (*value) | (command << 7);
        
        *value = (*value) | operand;
        
    } else {
        
        return 1;
    }
    
    return 0;
}


int sc_commandDecode (int value, int *command, int *operand){ // j
    
    if( ((value) >> 14) != 0){
        
        sc_regSet(ERROR_COMMAND, 1);
        
        return 1;
    }
    
    int dec_sevbit_mask = (value >> 7)& 0x7F;
    
    if((dec_sevbit_mask ) == 0x10 || ( dec_sevbit_mask ) == 0x11 ||
       ( dec_sevbit_mask ) == 0x20 || ( dec_sevbit_mask ) == 0x21 ||
       (( dec_sevbit_mask ) >= 0x40 && ( dec_sevbit_mask ) <= 0x43) ||
       (( dec_sevbit_mask ) >= 0x51 && ( dec_sevbit_mask ) <= 0x59) ||
       (( dec_sevbit_mask ) >= 0x60 && ( dec_sevbit_mask ) <= 0x69) ||
       (( dec_sevbit_mask ) >= 0x70 && ( dec_sevbit_mask ) <= 0x76)){
        
        *command = value >> 7;
        
    } else {
        
        sc_regSet(ERROR_COMMAND, 1);
        
        return 2;
    }
    
    *operand = value & 0x7F;
    
    return 0;
}


























