#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define RED 3
#define GREEN 5
#define BLUE 4


// return how many digits a number has
int numdigits(int num) {
  int digits = 1;
  while(num > 9) {
    num /= 10;
    digits++;
  }
  return digits;
}

// check if color is greater than value 
int greaterthan(int color, int value) {
  if(color > value) {
    return color;
  }
  else {
    return value;
  }
}

// for each number in string, checks if
// it is greater than maximum color-coded value
int checkgame(char* string, int gameid) {
  char buffer[3];
  int i = 0, wordlength, value;
  int red = 0, green = 0, blue = 0; /* if set to 0, the initial value will
					     always be less than the current value */
  
  for(i += 7 + numdigits(gameid); i < strlen(string); i += wordlength + 2) {
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
      red = greaterthan(red, value);
      wordlength = RED;
      break;
    case 'g':
      green = greaterthan(green, value);
      wordlength = GREEN;
      break;
    case 'b':
      blue = greaterthan(blue, value);
      wordlength = BLUE;
      break;
    default:
      fprintf(stderr, "Error: unexpected initials found when searching for color\n");
      exit(1);
      break;
    }

  }
  return (red * green * blue); // return the ID of the game cause game is possible
}

int main(int argc, char* argv[]) {
  FILE* stream_txt;
  char string[200];
  int gameid = 0, sum = 0;

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
    gameid++;
    sum += checkgame(string, gameid);
  }

  printf("sum: %d\n", sum);
  fclose(stream_txt);
  return 0;
}
