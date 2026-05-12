#include <stdio.h>
#include <conio.h>

int main() {
start:
  int lastChar = 0;
  int width = 20, height = 10;
  int plrx = 10, plry = 5;
  char *head = "";

  for(int y = 1; y <= height; y++){
    for(int x = 1; x <= width; x++){
      if( x == 1 || x == width || y == 1 || y == height){
        printf("0");
      }
      else if(x == plrx && y == plry){
        printf("#");
      }
      else{
        printf(".");
      }
    }
    printf("\n");
  }

  while(lastChar != 3) {
    lastChar = _getch();
    if(lastChar == 224){
      switch(_getch()){
        case 'H': //up
          plry -= 1;
          head = "^";
          break;
        case 'K': //left
          plrx -= 1;
          head = "<";
          break;
        case 'M': //right
          plrx += 1;
          head = ">";
          break;
        case 'P': //down
          plry += 1;
          head = "v";
          break;
      }
    }
    if(plrx == 1 || plrx == width || plry == 1 || plry == height){
      printf("\e[%dA", height);
      goto start;
    }
    else{
      printf("\e[%dA\e[%dC%s", height + 1 - plry, plrx - 1, head);
      printf("\e[%dD\e[%dB", plrx, height + 1 - plry); //breaks if x coordinates is 0
    }
    // printf("\e[%dA", height); 
  }
  // printf("\e[%dB", height); //jumps back down after exiting with C^
  return 0;
}
