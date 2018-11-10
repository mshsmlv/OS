void main() {
    char helloC[20] = "Hello C world!!!";
    char* video_memory = (char*) 0xb8000;
    int i = 0;
    for(i = 0; i < 17; i++) {
        *video_memory = helloC[i];
        *(video_memory + 1) = 0xd;
        video_memory += 2;
    }
}

