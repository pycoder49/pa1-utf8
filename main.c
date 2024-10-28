#include <stdio.h>
#include <stdint.h>
#include <string.h>

int32_t isascii(char str[]){
    int32_t index = 0;
    while(str[index] != '\0'){
        if (!(0 < str[index] && str[index] < 128)){
            return 0;
        }
        index++;
    }
    return 1;
}

int32_t capitalize_ascii(char str[]){
    int32_t count = 0;
    int32_t index = 0;
    while(str[index] != '\0'){
        if(97 <= str[index] && str[index] <= 122){
            str[index] = str[index] - 32;
            count++;
        }
        index++;
    }
    return count;
}

int32_t width_from_start_byte(unsigned char start_byte){
    if((start_byte & 0b10000000) == 0b00000000){ 
        return 1;
    }
    else if((start_byte & 0b11100000) == 0b11000000){
        return 2;
    }
    else if((start_byte & 0b11110000) == 0b11100000){
        return 3;
    }
    else if((start_byte & 0b11111000) == 0b11110000){
        return 4;
    }
    else {
        return -1;
    }
}

int32_t utf8_strlen(char str[]){
    int count = 0;
    int index = 0;
    while(str[index] != '\0'){
        count++;
        index += width_from_start_byte(str[index]);
    }
    return count;
}

int32_t codepoint_index_to_byte_index(char str[], int32_t cpi){
    int byte_index = 0;
    int str_index = 0;
    while(str[str_index] != '\0' && str_index <= cpi){
        int32_t width = width_from_start_byte(str[str_index]);
        byte_index += width;
        str_index += width;
    }
    return byte_index;
}

void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[]){
    int index = 0;
    int start_byte = codepoint_index_to_byte_index(str, cpi_start);
    int end_byte = codepoint_index_to_byte_index(str, cpi_end);
    for(int i = start_byte; i < end_byte; i++){
        result[index++] = str[i];
    }
}


int main(){
    printf("----------\n");
    
    char string[] = "Hello!";
    printf("is ascii: %d\n", isascii(string));
    printf("----------\n");

    int32_t ret = 0;
    char str[] = "abcd";
    ret = capitalize_ascii(str);
    printf("Capitalized string: %s\nCharacters updated: %d\n", str, ret);
    printf("----------\n");

    char strr[] = "Héy";
    printf("Width: %d bytes\n", width_from_start_byte(strr[2]));
    printf("----------\n");

    char s[] = "Joséph";
    printf("Length of string %s is %d\n", s, utf8_strlen(s));
    printf("----------\n");

    int32_t idx = 4;
    printf("Codepoint index %d is byte index %d\n", idx, codepoint_index_to_byte_index("Joséph", idx));
    printf("----------\n");

    char result[17];
    // utf8_substring("🦀🦮🦮🦀🦀🦮🦮", 3, 7, result);
    // printf("String: %s\nSubstring: %s\n", "🦀🦮🦮🦀🦀🦮🦮", result);
    // printf("----------\n");

    return 0;
}
