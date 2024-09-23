/*=============================================================================
| Assignment: pa02 - Calculating an 8, 16, or 32 bit
| checksum on an ASCII input file
|
| Author: Daniel A. Gomez
| Language: c
|
| To Compile: gcc -o pa02 pa02.c
|
| To Execute: c -> ./pa02 inputFile.txt 8
| where inputFile.txt is an ASCII input file
| and the number 8 could also be 16 or 32
| which are the valid checksum sizes, all
| other values are rejected with an error message
| and program termination
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Spring 2024
| Instructor: McAlpin
| Due Date: per assignment
|
+=============================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long int checkCal8(char *fileData);
unsigned long int checkCal16(char *fileData);
unsigned long int checkCal32(char *fileData);


int main(int argc, char *argv[]) {

    // Receives the file name and the bit count for the checksum.
    char *filename = argv[1];
    int checksumSize = atoi(argv[2]);

    // Checks to see if the chechsum bit count is a valid one.
    if (checksumSize != 8 && checksumSize != 16 && checksumSize != 32) {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return 1;
    }

    // Opens file and places it into file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file %s\n", filename);
        return 1;
    }

    // Prints the file content, with up to 80 characters per line.
    char line[80];
    while (fgets(line, sizeof(line), file) != NULL) {
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            // Remove trailing newline character
            line[len - 1] = '\0';
        }
        for (int i = 0; i < len; i += 80) {
            // Print up to 80 characters per line
            printf("%.80s\n", line + i);
        }
    }
    
    // Finds out the file size and allocate data to receive file content.
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    rewind(file);
    char *fileData = malloc(fileSize + 1);


    // File data is is received by fileData, and the last cell is given 
    // a null pointer. 
    fread(fileData, 1, fileSize, file);
    fileData[fileSize] = '\0'; 

    // Calculate checksum by checksum bit count of the file. long is used
    // because of the 32 bit checksum. 
    long checksum;
    if(checksumSize == 8){
        checksum = checkCal8(fileData);
        
        // Masking checksum so that all only the first 8 bits are read.
        checksum &= 0xFF;

        printf("\n");
    }
    else if(checksumSize == 16){
        // If the string length is odd, padd the string with an "X", 
        // so that the checksum is properly calculated. 
        if(strlen(fileData) % 2 == 1){
            // Realloc fileData to be big enough to receive another char in the string.
            // Print out an "X" to show how much padding was added. 
            fileData = realloc(fileData, (strlen(fileData) + 2) * sizeof(char));
            strcat(fileData, "X");
            printf("X");
            fileSize++;
        }

        printf("\n");
        
        // Calculate checksum based off the 16 bit checksum ammount.
        checksum = checkCal16(fileData);

        // Masking checksum so that all only the first 16 bits are read.
        checksum &= 0xFFFF;
    }
    else if(checksumSize == 32){
        // If the string length is odd, padd the string with an "X", 
        // so that the checksum is properly calculated. 
        while(strlen(fileData) % 4){
            // Realloc fileData to be big enough to receive another char in the string.
            // Print out an "X" to show how much padding was added. 
            fileData = realloc(fileData, (strlen(fileData) + 2) * sizeof(char));
            strcat(fileData, "X");
            printf("X");
            fileSize++;
        }

        printf("\n");
        
        // Calculate checksum based off of 32 bit checksum. 
        checksum = checkCal32(fileData);
    }

    // Print out the checksum size, the checksum, and the file size. 
    printf("%2d bit checksum is %lx for all %d chars\n", checksumSize, checksum, fileSize);

    // Cleanup
    fclose(file);
    free(fileData);
}

// Calculates the checksum based off the checksum size of 8 bits.
unsigned long int checkCal8(char *fileData)
{
    // For every char in the the string, add their values to the checksum
    // counter. The returned value is the checksum.
	int checkSum = 0;
	for (int i = 0; i < strlen(fileData); i++)
	{
		checkSum += fileData[i];
	}

	return checkSum;
}

// Calculates the checksum based off the checksum size of 16 bits.
unsigned long int checkCal16(char *fileData)
{
    // For every two chars in the string, add the first one in the upper 8 bit
    // register of the checksum ammount, and then the second one regularly
    // (as this well add the number to the lower 8 bit register).
	int checkSum = 0;
	for (int i = 0; i < strlen(fileData);)
	{
		checkSum += fileData[i] << 8;
		checkSum += (fileData[i + 1]);
		i += 2;
	}

	return checkSum;
}

// Calculates the checksum based off the checksum size of 32 bits.
unsigned long int checkCal32(char *fileData)
{
    // For every four chars in the string, add the first one in the upper 24 bit
    // register of the checksum ammount, and then the second one to the upper 16 bit register
    // then the thrid to the upper 8 bit register, then finally add the fourth regularly
    // (as this well add the number to the lower 8 bit register).
	unsigned long int checkSum = 0;
	for (int i = 0; i < strlen(fileData);)
	{
		checkSum += fileData[i] << 24;
		checkSum += (fileData[i + 1]) << 16;
		checkSum += (fileData[i + 2]) << 8;
		checkSum += (fileData[i + 3]);
		i += 4;
	}
	
	return checkSum;
}

/*=============================================================================
| I Daniel Gomez (5351345) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+============================================================================*/