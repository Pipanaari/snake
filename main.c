#include <stdio.h>
#include <conio.h>

int main() {
  int lastChar = 0;
  while(lastChar != 3) {
    lastChar = _getch();
    printf("%d\n", lastChar - 96);
  }
}
