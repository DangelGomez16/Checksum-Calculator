# Checksum-Calculator
A program that calculates the checksum for the text in a file.

The following is the prompt for this project:

### 1 Checksum
In this assignment you’ll write a program that calculates the checksum for the text in a file.
Your program will take two command line parameters. The first parameter will be the name
of the input file for calculating the checksum. The second parameter will be for the size of the
checksum (8, 16, or 32 bits). The program must generate output to the console (terminal) screen
as specified below.

#### 1.1 Command line parameters
1. Your program must compile and run from the command line.  
2. Input the required file name and the checksum size as command line parameters. Your
program may NOT prompt the user to enter the file names. The first parameter must be
the name of the file used for calculating the checksum, as described below. The second
parameter must be the size, in bits, of the checksum. The sample run command near the
end of this document contains an example of how the parameters will be entered.  
3. Your program should open the input text files, echo the processed input to the screen,
make the necessary calculations, and then output the checksum to the console (terminal)
screen in the format described below.  

#### Note
All of the test data files contain a termination character LF represented as a hexadecimal ’0A’.
This character is included in all the checksum calculations.  
#### 1.2 Checksum size  
The checksum size is a single integer, passed as the second command line argument. The valid
values are the size of the checksum, which can be either 8, 16, or 32 bits. Therefore, if the second
parameter is not one of the valid values, the program should advise the user that the value is
incorrect with a message formatted as shown below:  

fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");  

The message should be sent to STDERR1.  
#### 1.2.1 Format of the input file
The input file specified as the first command line argument, will consist of the valid 8 bit ASCII
characters normally associated with the average text file. This includes punctuation, numbers,
special characters, and whitespace.
#### 1.2.2 Output Format
The program must output the following to the console (terminal) screen, also known as STDOUT:
1. Echo the text from the input file.  
2. The echoed input text should be in rows of exactly 80 characters per row, except for the
last row, which may possibly have fewer. These characters should correspond to the input
text.  
#### 3. Print the checksum.
• Remember to pad with X (an uppercase X) if the input data does not align with
checksum size for the checksum calculation. For example, if calculating a 16 bit
checksum, it could be necessary to add an additional X to arrive at an input file size
of an even 16 bit size input. Likewise for 32 bits. However, note that it may be
necessary to pad with 1, 2, or 3 X characters for an even 32 bit size input.

### 4. The checksum line should be formatted as follows2 :  
printf("%2d bit checksum is %8lx for all %4d chars\n",
checkSumSize, checksum, characterCnt);
