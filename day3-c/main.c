#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

const char* SEQUENCE_BEG = "mul(";
const char* SEQUENCE_DO = "do()";
const char* SEQUENCE_DONT = "don't()";

void cleanBuffers(char* buffer1, char* buffer2) {
    memset(buffer1, 0, 4); // Clear buffer1
    memset(buffer2, 0, 4); // Clear buffer2
}

enum Sequence {
  MUL,
  DO_DONT,
  DO,
  DONT
};

int main() {
    int charnum = 0;
    char buffer1[4];
    char buffer2[4];
    int c;
    int current_sequence_char = -1;
    int current_sequence_num = 1;
    int num_index = 0;

    enum Sequence sequence = MUL;
    int doing = 1;

    long sum = 0;
    long num_1;
    long num_2;

    while ((c = getchar()) != EOF) {
      if(current_sequence_char == -1){
        if(c == 'm'){
          current_sequence_char = 0;
          sequence = MUL;
        }else if(c == 'd'){
          current_sequence_char = 0;
          sequence = DO_DONT;
        }
      }else if (sequence == MUL && current_sequence_char < 3) {
          if( c != SEQUENCE_BEG[current_sequence_char+1]){
            current_sequence_char = -1;
          }else{
            current_sequence_char ++;
          }
      }else if (sequence == DO_DONT){
        if(c == 'o' && current_sequence_char == 0){
          current_sequence_char += 1;
        }else if(c == '(' && current_sequence_char == 1){
          sequence = DO;
          current_sequence_char += 1;
        }else if(c == 'n' && current_sequence_char == 1){
          sequence = DONT;
          current_sequence_char += 1;
        }else{
          current_sequence_char = -1;
        }
      }else if (sequence == DO){
        if(c == ')' && current_sequence_char == 2){
          doing = 1;
        }
        current_sequence_char = -1;
      }else if(sequence == DONT && current_sequence_char < 6){
        if(current_sequence_char < 5){
          if(c == SEQUENCE_DONT[current_sequence_char + 1]){
            current_sequence_char += 1;
          }else{
            current_sequence_char = -1;
          }
        }else if(current_sequence_char == 5 && c == ')'){
          doing = 0;
          current_sequence_char = -1;
        }
      }
      
      else if(c == ',' && current_sequence_num == 1){
        buffer1[num_index] = '\0';
        current_sequence_num = 2;
        num_index = 0;
      }else if(isdigit(c) && num_index < 3){
        if(current_sequence_num == 1){
          buffer1[num_index] = c;
        }else{
          buffer2[num_index] = c;
        }
        num_index ++;
      }else if(c == ')' && doing){
        buffer2[num_index] = '\0';
        num_1 = atoi(buffer1);
        num_2 = atoi(buffer2);
        current_sequence_char = -1;
        current_sequence_num = 1;
        num_index = 0;
        cleanBuffers(buffer1, buffer2);
        sum += num_1 * num_2;
      }
      else{
        current_sequence_char = -1;
        current_sequence_num = 1;
        num_index = 0;
        cleanBuffers(buffer1, buffer2);
      }
      charnum ++;
    }
    printf("%li\n", sum);


    return 0;
}
