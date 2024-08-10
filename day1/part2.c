#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// shift array elements one space
void arraymove(char *string) {
  if(strlen(string) == 0) {
    return;
  }
  for(int i = strlen(string) - 1; i >= 0; i--)
    string[i+1] = string[i];
}

// check if one of index's entries matches a substring of string
// return it's corresponding digit in ASCII if yes
char strtoint(char *string, const char **index, int index_size) {
  for(int i = 0; i < index_size; i++) {
    if(strstr(string, index[i]))
      return i + 48;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  FILE *stream_txt;
  char string[100], substring[100];
  char digits[3], digit; // first and last digit from string combined
  int number, sum = 0; // int-converted digital and sum total
  const char *num_index[10] = {"zero", "one", "two", "three", "four",
			      "five", "six", "seven", "eight", "nine"}; // english digits index
  
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
    if(fgets(string, 100, stream_txt) == NULL)
      break; // if EOF, then exit

    // check first if current char is digit, then
    // check if substring matches index until
    // a match is found. Then store it on digits first slot
    for(int i = 0; i < strlen(string); i++) {
      substring[i] = string[i];
      if(isdigit(substring[i])) {
	digits[0] = substring[i]; // second digit
	break;
      }
      digit = strtoint(substring, num_index, 10);
      if(digit != 0) {
	digits[0] = digit; // first digit
	break;
      }
    }
    memset(substring, 0, sizeof(substring)); // clear substring before using it again
    // same thing as before, but do it in reverse order
    // and for the second digit
    for(int i = strlen(string) - 1; i >= 0; i--) {
      // things fuck up when the first slot of a string is empty
      // so for this to work I had to use a stack approach.
      arraymove(substring);
      substring[0] = string[i];
      if(isdigit(substring[0])) {
	digits[1] = substring[0]; // second digit
	break;
      }
      digit = strtoint(substring, num_index, 10);
      if(digit != 0) {
	digits[1] = digit; // second digit
	break;
      }
    }
    memset(substring, 0, sizeof(substring));
    digits[2] = 0;
    number = atoi(digits);
    sum += number;
  }  
  printf("result: %d\n", sum);
  
  // close file stream and exit
  fclose(stream_txt);
  return 0;
}  
