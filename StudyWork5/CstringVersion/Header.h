#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <locale.h>

int strIndex(const char* str, const char* need) {
    int str_size = strlen(str);
    int need_size = strlen(need);

    for (int i = 0; i < str_size - need_size + 1; ++i) {
        int j;
        for (j = 0; j < need_size; ++j)
            if (str[i + j] != need[j])
                break;
        if (j == need_size)
            return i;
    }

    return -1;
}

void CheckIndex(int index, char* str) {

    if (index == -1) {
    
        printf("Слово %s не найдено в строке\n", str);
        exit(1);

    }
    else {
        
        printf("Слово %s найдено в строке на позиции %d\n", str, index);

    }

}

void CheckWordOrder(int i1, int i2) {

    if (i1 >= i2) {
        printf("Неправильный порядок слов\n");
        exit(1);
    }

}

