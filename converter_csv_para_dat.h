#include <conio.h>
#include <stdio.h>
#include <string.h>

int conversion(FILE* fp,FILE* dat) {
	char buffer[1024];
	char aux[] = "";
	int row = 0;
	int column = 0;
	while (fgets(buffer, 1024, fp)) {
        column = 0;
        row++;
        if (row == 1) continue;
        char* value = strtok(buffer, ";");
        while (value) {
          	if (column != 8)
           	{
           		strcpy(aux, value);
               	fputs(aux, dat);
               	fputs(";", dat);
			} else {
				strcpy(aux, value);
               	fputs(aux, dat);
			}
				
			value = strtok(NULL, ";");
            column++;
        }
    }
	//fclose(dat);
	fclose(fp);
}
