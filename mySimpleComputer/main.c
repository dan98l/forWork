//
//  main.cpp
//  mySimpleComputer
//
//  Created by Daniil G on 16.02.2018.
//  Copyright © 2018 Daniil G. All rights reserved.
//


#include <stdio.h>
#include "mySimpleComputer.h"

int main(int argc, char **argv)
{
    int code;
    
    code = sc_memoryInit();
    printf("sc_memoryInit() = %1d\n", code);
    
    code = sc_memorySet(23, 10);
    printf("\nsc_memorySet(23, 10) = %1d\n", code);
    
    for(int i = 0; i < 30; ++i)
        sc_memorySet(rand() % 100, rand() % 10000);
    
    code = sc_memorySet(101, 10);
    printf("sc_memorySet(101, 10) = %1d\n - Память переполнена. Установлен флаг выход за границы памяти! \n", code);
    
    code = sc_memorySave("RAMsave.txt");
    printf("sc_memorySave('RAMsave.txt') = %1d\n", code);
    
    code = sc_memoryInit();
    printf("sc_memoryInit() = %1d\n", code);
    
    code = sc_memoryLoad("RAMsave.txt");
    printf("sc_memoryLoad('RAMsave.txt') = %1d\n", code);
    
    int val;
    code = sc_memoryGet(23, &val);
    printf("\nsc_memoryGet(23, &val) = %1d\n", code);
    printf("int val = %3d\n", val);
    
    code = sc_memoryGet(200, &val);
    printf("sc_memoryGet(200, &val) = %1d\n", code);
    printf("int val = %3d (shouldn't be changed)\n", val);
    
    code = sc_regInit();
    printf("\nsc_regInit() = %1d\n", code);
    
    printf("\n**sc_memorySet(101, 10) change the flag with code 3 (overloading memory)\n");
    
    code = sc_regGet(3, &val);
    printf("sc_regGet(3, &val) = %1d\n", code);
    printf("int val = %3d\n", val);
    
    code = sc_regSet(OUT_MEMORY, 0);
    printf("sc_regSet(3, 0) = %1d\n", code);
    
    code = sc_regGet(OUT_MEMORY, &val);
    printf("sc_regGet(3, &val) = %1d\n", code);
    printf("int val = %3d\n", val);
    
    code = sc_commandEncode (32, 32, &val);
    printf("\nsc_commanEncode (32, 32, &val) = %1d\n", code);
    printf("int val = %6d(should be 4128 = '0 0100000 0100000')\n", val);
    
    code = sc_commandEncode (12, 32, &val);
    printf("\nsc_commanEncode (12, 32, &val) = %1d\n", code);
    printf("int val = %6d(should be 4128 = '0 0100000 0100000')\n", val);
    
    code = sc_commandEncode (32, 1000, &val);
    printf("\nsc_commanEncode (32, 1000, &val) = %1d\n", code);
    printf("int val = %6d(should be 4128 = '0 0100000 0100000')\n", val);
    
    int cmd = 0, oper = 0;
    code = sc_commandDecode (val, &cmd, &oper);
    printf("\nsc_commandDecode (val, &cmd, &oper) = %1d\n - команда введена верно. Флаг Ошибочная Команда не установлен \n", code);
    printf("int cmd = %2d, int oper = %2d(should be 32; 32)\n", cmd, oper);
    
    return 0;
}
