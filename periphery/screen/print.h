#define PANIC(msg) {printf("\nPANIC "); printf(__FILE__); char line[10]; str(line, __LINE__); printf(":"); printf(line); printf(": "); printf(msg);}


int print(char* format_string);
int str(char* dst, unsigned int a);
