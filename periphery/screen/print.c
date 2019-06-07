#include "print.h"
#include "helpers.h"

char* VIDEO_MEMORY = (char*)0xb8000;
int BEGIN_OF_VIDEO_MEMORY = 0xb8000;
int COLUMNS_NUMBER = 80;
int STRINGS_NUMBER = 25;

void push_num(char* dst, int n, char a) {
    int i;
    for(i = n; i > 0; i--) {
        dst[i] = dst[i-1];
    }
    dst[0] = a;
    dst[n+1] = 0;
};

int str(char* dst, unsigned int a) {
    int i = 0;
    int r;
    do {
        r = a%10;
        push_num(dst, i, r + '0');
        a = a/10;
        i++;
    } while(a);
}

void clean_last_string() {
    char* cursor = (char*)(BEGIN_OF_VIDEO_MEMORY + (STRINGS_NUMBER)*COLUMNS_NUMBER*2);
    while (cursor < (char*)(BEGIN_OF_VIDEO_MEMORY + (STRINGS_NUMBER+1)*COLUMNS_NUMBER*2)) {
        *cursor = ' ';
        *(cursor + 1) = 0xd;
        cursor += 2;

    }
}

int rewrite_string(int index) {
    char* current_string = (char*)(BEGIN_OF_VIDEO_MEMORY+ (COLUMNS_NUMBER*2)*index);
    char* previous_string = (char*)(BEGIN_OF_VIDEO_MEMORY + (COLUMNS_NUMBER*2) * (index-1));
    int i;
    for(i = 0; i < (COLUMNS_NUMBER*2); i++) {
        *(previous_string + i) = *(current_string + i);
    }
    clean_last_string();
}

int scroll() {
    int i;
    for(i = 1; i < 26; i++) {
        rewrite_string(i);
    }
}

int carriage_return() {
    int next_string = (int)(VIDEO_MEMORY) + COLUMNS_NUMBER*2 - ((int)VIDEO_MEMORY - BEGIN_OF_VIDEO_MEMORY)%(COLUMNS_NUMBER*2);
    while ((int)(VIDEO_MEMORY) < next_string) {
        *VIDEO_MEMORY = ' ';
        *(VIDEO_MEMORY + 1) = 0xd;
        VIDEO_MEMORY += 2;
    }
}

void tabulation() {
    if(
        (*(VIDEO_MEMORY - 2)) != ' ' && 
        (*(VIDEO_MEMORY - 2)) != '\n' ) {
        return;
    }

    int i = 0;
    while(((int)VIDEO_MEMORY - BEGIN_OF_VIDEO_MEMORY)%(COLUMNS_NUMBER*2) && i < 4) {
        i++;
        VIDEO_MEMORY++;
    }
}

int print(char* format_string) {
    save_state();
    int i = 0;
    while (format_string[i]) {
        if ((int)(VIDEO_MEMORY+2) >= BEGIN_OF_VIDEO_MEMORY + STRINGS_NUMBER*COLUMNS_NUMBER*2) {
            scroll();
            VIDEO_MEMORY = (char*)(BEGIN_OF_VIDEO_MEMORY + (STRINGS_NUMBER-1)*COLUMNS_NUMBER*2);
        }
        if (format_string[i] == '\n') {
            carriage_return(); 
            i++;
            continue;
        }
        if (format_string[i] == '\t') {
            tabulation();
            i++;
            continue;
        }
        *VIDEO_MEMORY = format_string[i];
        *(VIDEO_MEMORY + 1) = 0xd;
        VIDEO_MEMORY += 2;
        i++;
    }
    restore_state();
}

void print_num(int num) {
    char int_no[100];
    str(int_no, num);
    print(int_no);
}

void print_char(char letter) {
    char str[2];
    str[0] = letter;
    str[1] = 0;
    print(str);
}
