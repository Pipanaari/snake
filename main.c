#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

int getch_noblock() {
  if (_kbhit()){
    return _getch();
  }
  else{
    return -1;
  }
}

int main() {
start:
  int lastChar = 0;
  int width = 20, height = 10, grid = (width - 2) * (height - 2);
  int plrx = width / 4 + 1, plry = height / 2 + 1, score = 3, wait = 1, apple = (width - 2) * ((height - 2) / 2) + ((width - 2) - (width / 4));
  char head = 0;
  int posx[grid], posy[grid];
  memset(posx, 0, sizeof(posx));
  memset(posy, 0, sizeof(posy));
  int x = 1;
  posx[0] = plrx; posy[0] = plry;

  for(int y = 1; y <= height; y++){
    for(int x = 1; x <= width; x++){
      if( x == 1 || x == width || y == 1 || y == height) printf("0");
      else if(x == plrx && y == plry) printf("#");
      else if(y == ((apple - 1) / (width - 2) + 2) && x == ((apple - 1) % (width - 2) + 2)) printf("@");
      else printf(".");
    }
    printf("\n");
  }

  while(lastChar != 3) {
    Sleep(150);

    do{
      lastChar = getch_noblock();
      if(lastChar == 224) lastChar = getch_noblock();
      if (lastChar  == 'H' && head != 'v') head = '^'; //up
      if (lastChar  == 'K' && head != '>') head = '<'; //left
      if (lastChar  == 'M' && head != '<') head = '>'; //right
      if (lastChar  == 'P' && head != '^') head = 'v'; //down

      if(head == '^') plry -= 1;
      if(head == '<') plrx -= 1;
      if(head == '>') plrx += 1;
      if(head == 'v') plry += 1;

    }while(head == 0 && lastChar != 3);
    if(lastChar == 3) break;

    int location = (plrx - 1) + ((width - 2) * (plry - 2));
    int snkLocation[score]; //all coordinates of snake body
    int openSpace[grid - score]; //coordinates of everything except snake body
    posy[x] = plry;
    posx[x] = plrx;
    for(int i = 0, y = x - 1; i < score - 1; i++){
      int calc = (y + grid) % grid;
      snkLocation[i] = (posx[calc] - 1) + ((width - 2) * (posy[calc] - 2)); //getting data for snkLocation
      if(plrx == posx[calc] && plry == posy[calc]){
        printf("Last score = %d     \nCtrl + C to Quit\n\e[%dA", score - 3, height + 2);
        goto start;
      }
      y--;
      y %= grid;
    }
    snkLocation[score - 1] = location;
    for(int i = 0, y = 1; i < grid - score; i++){ //getting data for openSpace
      for(int z = 0; z < score; z++){
        if(y == snkLocation[z]){
          y++;
          i--;
          break;
        }
        else if(z == score - 1){
          openSpace[i] = y;
          y++;
        }
      }
    }
    if(location == apple){
      score++;
      apple = openSpace[rand() % (grid - score)]; //randomize apple location from open spaces only
    }
    if(plrx == 1 || plrx == width || plry == 1 || plry == height || score == grid){
      printf("Last score = %d     \nCtrl + C to Quit\n\e[%dA", score - 3, height + 2);
      goto start;
    }
    else{
      int scalc = ((x - score) + grid) % grid;
      int bcalc = ((x - 1) + grid) % grid;
      if(wait >= score){
        printf("\e[%dA\e[%dC.", height + 1 - posy[scalc], posx[scalc] - 1); //remove everything after snake tail
        printf("\e[%dD\e[%dB", posx[scalc], height + 1 - posy[scalc]); 
      }
      printf("\e[%dA\e[%dC%c", height + 1 - plry, plrx - 1, head); //print snake head
      printf("\e[%dD\e[%dB", plrx, height + 1 - plry); 
      printf("\e[%dA\e[%dC#", height + 1 - posy[bcalc], posx[bcalc] - 1); //transorm heads into snake body after one move
      printf("\e[%dD\e[%dB", posx[bcalc], height + 1 - posy[bcalc]);
      printf("\e[%dA\e[%dC@", height - ((apple - 1) / (width - 2) + 1), ((apple - 1) % (width - 2) + 1)); //print apple
      printf("\e[%dD\e[%dB", (apple - 1) % (width - 2) + 2, height - ((apple - 1) / (width - 2) + 1));

      wait++;
      x++;
      x = x % grid;
    }
  }
  return 0;
}
