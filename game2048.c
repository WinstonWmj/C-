#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
/*
判断能否移动
1. 能够相消
2. 能够有空间移动

出现的格子
1. 每次都出现2 | 出现2和出现4的概率不同
2. 出现的位置都是随机的

相消的时候
1. 一次移动，每个格子只合并一次
2. 按顺序合并，例如，从下往上滑动时，先从最下面的一个和最下面的倒数第二个判断
*/
int board[4][4];
void Show() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("|%4d", board[i][j]);
    }
    printf("\n");
  }
}
int concat(int queue[], int k) {
  int length = 0;
  for (int i = 0; i < k; i++) {
    if (queue[i] == queue[i + 1]) {
      queue[length++] = queue[i] + queue[i + 1];
      i++;
    } else {
      queue[length++] = queue[i];
    }
  }
  return length;
}
void W() {
  // 从下往上判断
  for (int i = 0; i < 4; i++) {
    // 每列都要单独判断
    // 使用队列，先进先出
    int queue[4];
    int k = 0;
    for (int j = 0; j < 4; j++) {
      if (board[j][i] != 0) {
        queue[k++] = board[j][i];
        board[j][i] = 0;
      }
    }
    int length = concat(queue, k);
    for (int j = 0; j < length; j++) {
      board[j][i] = queue[j];
    }
  }
}
void S() {
  for (int i = 0; i < 4; i++) {
    int queue[4];
    int k = 0;
    for (int j = 0; j < 4; j++) {
      if (board[3 - j][i] != 0) {
        queue[k++] = board[3 - j][i];
        board[3 - j][i] = 0;
      }
    }
    int length = concat(queue, k);
    for (int j = 0; j < length; j++) {
      board[3 - j][i] = queue[j];
    }
  }
}
void A() {
  for (int i = 0; i < 4; i++) {
    int queue[4];
    int k = 0;
    for (int j = 0; j < 4; j++) {
      if (board[i][j] != 0) {
        queue[k++] = board[i][j];
        board[i][j] = 0;
      }
    }
    int length = concat(queue, k);
    for (int j = 0; j < length; j++) {
      board[i][j] = queue[j];
    }
  }
}
void D() {
  for (int i = 0; i < 4; i++) {
    int queue[4];
    int k = 0;
    for (int j = 0; j < 4; j++) {
      if (board[i][3 - j] != 0) {
        queue[k++] = board[i][3 - j];
        board[i][3 - j] = 0;
      }
    }
    int length = concat(queue, k);
    for (int j = 0; j < length; j++) {
      board[i][3 - j] = queue[j];
    }
  }
}
void newcorr(int *x, int *y) {
  srand((unsigned)time(NULL));
  *x = rand() % 4;  // 输出的数字在0~3
  *y = rand() % 4;
}
int main(int argc, char const *argv[]) {
  for (int i = 0; i < 4; i++) {
    memset(board[i], 0, sizeof(board[i]));
  }
  int x, y;
  newcorr(&x, &y);
  board[x][y] = 2;
  Show();
  char a;
  char input = 'w';
  while (input != 'q') {
    if (kbhit()) {
      system("cls");
      input = getch();
      if (input == 'w') {
        W();
      } else if (input == 'a') {
        A();
      } else if (input == 's') {
        S();
      } else if (input == 'd') {
        D();
      }
      do {
        newcorr(&x, &y);
        Sleep(200);
      } while (board[x][y] != 0);
      board[x][y] = 2;
      Show();
    }
  }
  return 0;
}
