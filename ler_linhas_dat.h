#include <stdio.h>

int getFileLines(FILE* dat) {
	int countLines = 1;
	char c;
   	for (c = getc(dat); c != EOF; c = getc(dat)) {
   		if (c == '\n') {
   			countLines = countLines + 1;
	   	}
   	}
   	fclose(dat);
    return countLines;
}
