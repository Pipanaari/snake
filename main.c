#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

int main() {
start:
  int lastChar = 0;
  int width = 20, height = 10, grid = (width - 2) * (height - 2);
  int plrx = width / 2, plry = height / 2, score = 3, wait = 1;
  char *head = "";
  int posx[grid], posy[grid];
  memset(posx, 0, sizeof(posx));
  memset(posy, 0, sizeof(posy));
  int x = 1;
  posx[0] = plrx; posy[0] = plry;

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
    posy[x] = plry;
    posx[x] = plrx;
    for(int i = 1, y = x - 2; i < score - 1; i++){
      int calc = (y + grid) % grid;
      if(plrx == posx[calc] && plry == posy[calc]){
        printf("\e[%dA", height);
        goto start;
      }
      y--;
      y %= grid;
    }
    if(plrx == 1 || plrx == width || plry == 1 || plry == height || score == grid){
      printf("\e[%dA", height);
      goto start;
    }
    else{
      int scalc = ((x - score) + grid) % grid;
      int bcalc = ((x - 1) + grid) % grid;
      if(wait >= score){ 
        printf("\e[%dA\e[%dC.", height + 1 - posy[scalc], posx[scalc] - 1);
        printf("\e[%dD\e[%dB", posx[scalc], height + 1 - posy[scalc]); 
      }
      printf("\e[%dA\e[%dC%s", height + 1 - plry, plrx - 1, head);
      printf("\e[%dD\e[%dB", plrx, height + 1 - plry); 
      printf("\e[%dA\e[%dC#", height + 1 - posy[bcalc], posx[bcalc] - 1);
      printf("\e[%dD\e[%dB", posx[bcalc], height + 1 - posy[bcalc]); 
      printf("%d %d %d     \n\e[A", scalc, wait, x);
      wait++;
      x++;
      x = x % grid;
    }
    // printf("\e[%dA", height); 
  }
  // printf("\e[%dB", height); //jumps back down after exiting with C^
  return 0;
}
