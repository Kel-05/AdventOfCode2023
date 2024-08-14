#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// shift read area by one line, then load next line in the last one
void shift_read_area(char read_area[3][150], char *buffer) {
  for(int y = 0; y < 2; y++) {
    for(int x = 0; x < 150; x++) {
      read_area[y][x] = read_area[y+1][x];
    }
  }

  for(int x = 0; x < 150; x++)
    read_area[2][x] = buffer[x];
}

// shift scanner right by one space relative to the read area
void shift_scanner(char read_area[3][150], char scanner[3][7], int absolute_x) {
  for(int y = 0; y < 3; y++) {
    for(int x = 0; x < 7; x++) {
      scanner[y][x] = read_area[y][x + absolute_x];
    }
  }
}

// shift array by one space to the left
void shift_array(char *array) {
  if(strlen(array) == 0 || strlen(array) == sizeof(array)) {
    return;
  }
  for(int i = strlen(array) - 1; i >= 0; i--)
    array[i+1] = array[i];
}

// fill str_number with numbers from left to right
void array(char scanner[3][7], char *str_number, int row, int column, int start, int size) {
  if(start < 0) { // to avoid going out of bounds when strlen = 0
    start = 0;
  }

  for(int i = 0; start < size; start++) {

    if(isdigit(scanner[row][column + i]))
      str_number[start] = scanner[row][column + i];

    i++;
    }
  str_number[size-1] = 0; // last array space MUST be 0
}

// fill str_number with numbers from right to left with a stack approach
void reverse_array(char scanner[3][7], char *str_number, int row, int column) {

  for(int i=0; i < 3; i++) {

    if(isdigit(scanner[row][column - i])) {
      shift_array(str_number);
      str_number[0] = scanner[row][column - i];
    }
  }
}

// check 3*3 central sub-matrix for any number and call respective functions
int find_number(char scanner[3][7]) {
  char str_number[4] = {};
  int sum = 0;
  
  for(int y = 0; y < 3; y++) {
    for(int x = 2; x < 5; x++) {

      // if digit is found in x and x-1, then add them via reverse_array
      if(isdigit(scanner[y][x]) && isdigit(scanner[y][x-1]))
        reverse_array(scanner, str_number, y, x);

      // if digit is found in x and x+1, then add them via array.
      //
      // if it already called reverse_array, it will start automagically
      // in the last space of the string, finishing the number.
      //
      // this resolves any problem regarding finding a central digit.
      if(isdigit(scanner[y][x]) && isdigit(scanner[y][x+1])) {
        array(scanner, str_number, y, x, strlen(str_number)-1, sizeof(str_number));
        x += strlen(str_number)-1;
      }

      // if none of the previous conditions was true and there is still
      // a digit in x, then just add it to the first position
      if(isdigit(scanner[y][x]) && strlen(str_number) == 0)
        str_number[0] = scanner[y][x];
      
      sum += atoi(str_number); // convert number and add it to sum
      memset(str_number, 0, sizeof(str_number)); // clear array to avoid ovelaps
    }
  }

  return sum;
}

// search for symbol at center of scanner along the read area
int find_symbol(char read_area[3][150]) {
  char scanner[3][7] = {};
  int sum = 0;
  
  // shift scanner by n-7 times
  // first time will intialize scanner
  for(int absolute_x = 0, i = 7; i < strlen(read_area[1]); i++) {
    shift_scanner(read_area, scanner, absolute_x);
    absolute_x++; // absolute position of scanner in read area

    // if symbol is found, then search for numbers around it
    if(scanner[1][3] != '.' && !isdigit(scanner[1][3]))
      sum += find_number(scanner);
  }

  return sum;
}

int main(int argc, char *argv[]) {
  FILE *stream_txt;
  char read_area[3][150] = {}, buffer[150] = {};
  int sum = 0;

  // check if only one argument is given
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

  // initialize first 3 lines of input and check if it is large enough.
  for(int i = 0; i < 3; i++) {
    fgets(read_area[i], 150, stream_txt);
    if(strlen(read_area[i]) < 7 || read_area[i][6] == '\n') {
      fprintf(stderr, "Error: input too small (min. 3x7 input)\n");
      return 1;
    }
  }
  
  // read next line, evaluate read area then shift it one line.
  while(fgets(buffer, 150, stream_txt) != NULL) {
    sum += find_symbol(read_area);
    shift_read_area(read_area, buffer);
  }

  printf("sum: %d\n", sum);
  fclose(stream_txt); // close file stream and exit
  return 0;
}
