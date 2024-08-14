#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void shift_array(char *array) {
  
  if(strlen(array) == 0) {
    return;
  }
  
  for(int i = strlen(array) - 1; i >= 0; i--) {
    array[i+1] = array[i];
  }
}

int reverse_array(char *array, int position) {
  char str_number[3] = {};
  for(int i=0; i < sizeof(str_number)-1; i++) {
    if(isdigit(array[position - i])) {
      shift_array(str_number);
      str_number[0] = array[position - i];
    }
  }
  return atoi(str_number);
}

int is_match(int number_a, int number_b) {
  if(number_a == number_b) {
    return 1;
  }
  return 0;
}

int compare_numbers(int *winning_numbers,int *numbers, int size_wn, int size_n) {
  int sum = 0;
  for(int i = 0; i < size_wn; i++) {
    for(int j = 0; j < size_n; j++) {
      sum += is_match(numbers[j], winning_numbers[i]);
    }
  }
  return sum;
}

int check_card(char* string, int card_id, int*scratchcards) {
  int winning_numbers[10], numbers[25];
  int sum, total = 0, position = 11;
  int size_wn = sizeof(winning_numbers)/sizeof(winning_numbers[0]);
  int size_n = sizeof(numbers)/sizeof(numbers[0]);

  for(int i = 0; i < size_wn; i++) {
    winning_numbers[i] = reverse_array(string, position);
    position += 3;
  }

  position += 2;
  
  for(int i = 0; i < size_n; i++) {
    numbers[i] = reverse_array(string, position);
    position += 3;
  }

  for(int i = 0; i < scratchcards[card_id]; i++) {
    sum = compare_numbers(winning_numbers, numbers, size_wn, size_n);
    total++;
    for(int j = 1; j <= sum; j++) {
      scratchcards[card_id+j]++;
    }
  }

  return total;
}

int main(int argc, char* argv[]) {
  FILE* stream_txt;
  char string[150];
  int card_id = 0, sum = 0;
  int scratchcards[250];
  int size_sc = sizeof(scratchcards)/sizeof(scratchcards[0]);

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

  for(int i = 0; i < size_sc; i++) {
    scratchcards[i] = 1;
  }

  while(fgets(string, 150, stream_txt) != NULL) {
    sum += check_card(string, card_id, scratchcards);
    card_id++;
  }

  printf("sum: %d\n", sum);
  fclose(stream_txt);
  return 0;
}
