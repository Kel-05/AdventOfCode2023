#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *stream_txt; // file.txt
  char string[100]; // extracted line of text
  char digits[3]; // first and last digit from string combined
  int number, total = 0; // number-converted string and sum total
  
  // check if ONE arg is given
  if(argc != 2) {
    fprintf(stderr, "Error: please enter ONE file\n");
    return 1;
  }  

  // open file's stream specified in arg
  stream_txt = fopen(argv[1], "r");

  // if can't read file/doesn't exist, return error
  if(stream_txt == NULL) {
    fprintf(stderr, "Error: can't read or access file\n");
    return 1;
  }

  // read file lines until EOF is reached
  while(1) {
    if(fgets(string, 100, stream_txt) == NULL) {
      break; // if EOF, then exit
    }
    /* cycle through single chars until num is found
       then do the same thing starting from the end */
    for(int i = 0; i < strlen(string); i++) {
      if(isdigit(string[i])) {
	digits[0] = string[i]; // first digit
	break;
      }
    }
    for(int i = strlen(string) - 1; i >= 0; i--) {
      if(isdigit(string[i])) {
	digits[1] = string[i]; // second digit
	break;
      }
    }
    digits[2] = 0;
    number = atoi(digits);
    total += number;
  }
  
  printf("result: %d\n", total);
  
  // close file stream and exit
  fclose(stream_txt);
  return 0;
}
