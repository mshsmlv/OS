char* VIDEO_MEMORY = (char*)0xb8000;

int carriage_return() {
    VIDEO_MEMORY = VIDEO_MEMORY + 80*2 - ((int)VIDEO_MEMORY - 0xb8000)%(80*2);
}

int tabulation() {
    if(
            (*(VIDEO_MEMORY - 2)) != ' ' && 
            (*(VIDEO_MEMORY - 2)) != '\n' ) {
        return;
    }

    int i = 0;
    while(((int)VIDEO_MEMORY - 0xb8000)%(80*2) && i < 4) {
        i++;
        VIDEO_MEMORY++;
    }
}

int printf(char* format_string) {
        int i = 0;
        while (format_string[i]) {
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
}

void main() {
    printf("first\n\0");
    printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa \taaaaaaaaaaaaaa\0");
}


