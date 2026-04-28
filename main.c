#include <stdio.h>
#include <conio.h>

int main() {
  int lastChar = 0;
  int width = 20, height = 10;
  int plrx = 10, plry = 5;
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
  }
}
