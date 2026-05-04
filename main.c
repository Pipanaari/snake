#include <stdio.h>
#include <conio.h>

int main() {
  int lastChar = 0;
  int width = 20, height = 10;
  int plrx = 10, plry = 5;

  while(lastChar != 3) {
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
    lastChar = _getch();
    if(lastChar == 224){
      switch(_getch()){
        case 'H': //up
          plry -= 1;
          break;
        case 'K': //left
          plrx -= 1;
          break;
        case 'M': //right
          plrx += 1;
          break;
        case 'P': //down
          plry += 1;
          break;
      }
    }
    printf("\e[%dA", height); 
  }
  printf("\e[%dB", height); //jumps back down after exiting with C^
  return 0;
}
