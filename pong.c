#include <stdio.h>

#define HEIGHT 25
#define WIDTH 80
#define max(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a > _b ? _a : _b;                                                         \
  })

#define min(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a < _b ? _a : _b;                                                         \
  })

void reloadGame(int *ball_pos, int *ball_vec, int *rockets_pos, int *score);
void drawField(int *const rockets_pos, int *const ball_pos, int *score) {
  printf("%02d  -  %02d\n", score[0], score[1]);
  for (int height = 0; height < 25; height++) { // height - высота поля
    for (int width = 0; width < 80; width++) {  // width - ширина поля
      if (height == 0 || height == 24)
        printf("-"); // верхние и нижние границы поля

      else if (((height == rockets_pos[0] || height == rockets_pos[0] + 1 ||
                 height == rockets_pos[0] - 1) &&
                width == 3) ||
               ((height == rockets_pos[1] || height == rockets_pos[1] + 1 ||
                 height == rockets_pos[1] - 1) &&
                width == 76))
        printf("|"); // положение рокеток

      else if (height == ball_pos[1] && width == ball_pos[0])
        printf("o"); //  положение мяча
      else
        printf(" ");
    }
    printf("\n");
  }
}

void ballMove(int *position, int *ball_vec, int const *rockets_pos) {
  if (position[1] == 1) {
    ball_vec[1] = 1;
  } else if (position[1] == 23) {
    ball_vec[1] = -1;
  }
  int diff;
  if (ball_vec[0] < 0) {
    if (position[0] - 3 == 1) {
      if ((diff = rockets_pos[0] - position[1]) < 2 && diff > -2) {
        ball_vec[0] = 1;
        ball_vec[1] = -diff;
      }
    }
  } else if (ball_vec[0] > 0) {
    if (position[0] - 74 == 1) {
      if ((diff = rockets_pos[1] - position[1]) < 2 && diff > -2) {
        ball_vec[0] = -1;
        ball_vec[1] = -diff;
      }
    }
  }
  position[0] += ball_vec[0];
  position[1] += ball_vec[1];
}

void rocketMove(int *position, int vec) {
  *position = min(HEIGHT - 3, max(2, *position + vec));
}

int main() {
  int rockets_pos[2] = {12, 12};
  int ball_pos[2] = {4, 12};
  int ball_vec[2] = {1, 0};
  int score[2] = {0, 0};
  while (score[0] < 21 && score[1] < 21) {
    drawField(rockets_pos, ball_pos, score);
    switch (getchar()) {
    case 'a':
    case 'A':
      rocketMove(&rockets_pos[0], -1);
      break;
    case 'z':
    case 'Z':
      rocketMove(&rockets_pos[0], 1);
      break;
    case 'k':
    case 'K':
      rocketMove(&rockets_pos[1], -1);
      break;
    case 'm':
    case 'M':
      rocketMove(&rockets_pos[1], 1);
      break;
    case ' ':
      break;
    default:
      continue;
      break;
    }
    ballMove(ball_pos, ball_vec, rockets_pos);
    if (ball_pos[0] < 1 || ball_pos[0] > 79) {
      reloadGame(ball_pos, ball_vec, rockets_pos, score);
    }
  }
  getchar();
  return 0;
}

void reloadGame(int *ball_pos, int *ball_vec, int *rockets_pos, int *score) {
  ball_pos[1] = 12;
  ball_vec[1] = 0;
  rockets_pos[0] = 12;
  rockets_pos[1] = 12;
  if (ball_vec[0] < 0) {
    ball_pos[0] = 4;
    ball_vec[0] = 1;
    score[1] += 1;
  } else if (ball_vec[0] > 0) {
    ball_pos[0] = 75;
    ball_vec[0] = -1;
    score[0] += 1;
  }
}