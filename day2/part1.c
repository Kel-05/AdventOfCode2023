#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define RED 3
#define GREEN 5
#define BLUE 4


// return how many digits a number has
int numdigits(int n) {
  int p = 1;
  while(n > 9) {
    n /= 10;
    p++;
  }
  return p;
}

// check if value is greater than max 
int checkmax(int max, int value) {
  if(value > max) {
    return 1;
  }
  else {
    return 0;
  }
}

// for each number in string, checks if
// it is greater than maximum color-coded value
int checkgame(char* string, int j) {
  char buffer[3];
  int i = 0, x, value, check;
  const int rgb[3] = {12, 13, 14}; // maximum values for each color

  for(i += 7 + numdigits(j); i < strlen(string); i += x + 2) {
    buffer[0] = string[i]; // first char will always be a number

    // if next char is a number, store it and move by 3
    // if not, just move by 2.
    // this is done has it is presumed that cubes won't exceed 99.
    if(isdigit(string[i+1])) {
      buffer[1] = string[i+1];
      buffer[2] = 0;
      i += 3;
    }
    else {
      buffer[1] = 0;
      i += 2;
    }
    value = atoi(buffer); // convert string into int
    memset(buffer, 0, sizeof(buffer)); // clear buffer, just to be safe QwQ

    // check first letter and presume color by that
    // if no match then exit with error
    switch(string[i]) {
    case 'r':
      check = checkmax(rgb[0], value);
      x = RED;
      break;
    case 'g':
      check = checkmax(rgb[1], value);
      x = GREEN;
      break;
    case 'b':
      check = checkmax(rgb[2], value);
      x = BLUE;
      break;
    default:
      fprintf(stderr, "Error: unexpected initials found when searching for color\n");
      exit(1);
      break;
    }

    // check if previous function returned true.
    // if so then game is impossible and return 0.
    if(check) {
      return 0;
    }
  }
  return j; // return the ID of the game cause game is possible
}

int main(int argc, char* argv[]) {
  FILE* stream_txt;
  char string[200];
  int j = 0, sum = 0;

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

  while(fgets(string, 200, stream_txt) != NULL) {
    j++;
    sum += checkgame(string, j);
  }
  printf("sum: %d\n", sum);
  
  return 0;
}
