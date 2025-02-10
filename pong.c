#include <stdio.h>

void main_field(int ry1, int ry2, int rx1, int rx2, int ball_x, int ball_y,
                int width, int height, int score_x, int player1, int player2);
void final_field(int ry1, int ry2, int rx1, int rx2, int ball_x, int ball_y,
                 int width, int height, int score_x, int player1, int player2);
int rocket_touch(int rx1, int rx2, int ry1, int ry2, int ball_x, int ball_y);
int vert_mov(int ball_x);
int change_mov_y(int m_ball_y);
int change_mov_x(int m_ball_x);

int main() {
  int rx1 = 12, ry1 = 2, rx2 = 12, ry2 = 74;
  int width = 80, height = 25;
  int score_x = 5;
  int ball_x_start = height / 2,
      ball_y_start = width / 2 - 1;  // Стартовые координаты мячика
  int ball_x = ball_x_start, ball_y = ball_y_start;  // Текущие координаты
                                                     // мячика
  int m_ball_x = -1, m_ball_y = -1;  // Направление движения мячика
  int player1 = 0, player2 = 0;
  char move;     // нажатая клавиша
  int flag = 1;  // для запуска движения
  int win_score = 21;
  int sum_of_symbol;
  char first_symbol = '\n';
  while (player1 != win_score && player2 != win_score) {
    main_field(ry1, ry2, rx1, rx2, ball_x, ball_y, width, height, score_x,
               player1, player2);
    for (sum_of_symbol = 0; (move = getchar()) != '\n'; sum_of_symbol++) {
      first_symbol = move;  // Запись первого символа
    }
    if (sum_of_symbol != 1) continue;  // проверка введен только один символ
    switch (first_symbol) {
      case 'a':
      case 'A':
        if ((rx1 - 1) >= 0) {
          rx1--;
          flag = 1;
          break;
        }
        flag = 1;
        break;
      case 'z':
      case 'Z':
        if ((rx1 + 3) < 23) {
          rx1++;
          flag = 1;
          break;
        }
        flag = 1;
        break;

      case 'k':
      case 'K':
        if ((rx2 - 1) >= 0) {
          rx2--;
          flag = 1;
          break;
        }
        flag = 1;
        break;
      case 'm':
      case 'M':
        if ((rx2 + 3) < 23) {
          rx2++;
          flag = 1;
          break;
        }
        flag = 1;
        break;
      case ' ':
        flag = 1;
        break;
      default:
        flag = 0;
        break;
    }

    if (flag) {
      if (rocket_touch(rx1, rx2, ry1, ry2, ball_x, ball_y))
        m_ball_y *= -1;  // Если мяч касается ракетки
      if (ball_x == 22 || ball_x == 0)
        m_ball_x = vert_mov(ball_x);  // Отскок мяча от границ поля
      ball_y += change_mov_y(m_ball_y);  // Смена направления движения мяча по y
      ball_x += change_mov_x(m_ball_x);  // Смена направления движения мяча по x

      if (ball_y == 0) {  // Если забили гол
        player2 += 1;
        ball_x = ball_x_start;
        m_ball_y *= -1;
        ball_y = ball_y_start;
      }
      if (ball_y == 77) {
        player1 += 1;
        ball_x = ball_x_start;
        m_ball_y *= -1;
        ball_y = ball_y_start;
      }
    }
    flag = 0;
  }

  if (player1 == win_score || player2 == win_score) {
    final_field(ry1, ry2, rx1, rx2, ball_x, ball_y, width, height, score_x,
                player1, player2);
  }

  return 0;
}

void main_field(int ry1, int ry2, int rx1, int rx2, int ball_x, int ball_y,
                int width, int height, int score_x, int player1, int player2) {
  for (int i = 0; i < 80; i++) {
    printf("#");  // Верхняя часть поля
  }
  printf("\n");
  for (int x = 0; x < height - 2; x++) {  // Основная отрисовка
    printf("#");                          // Левая стенка
    for (int y = 0; y < width; y++) {
      if ((y == ry1 && (x == rx1 || x == rx1 + 1 || x == rx1 + 2)) ||
          (y == ry2 && (x == rx2 || x == rx2 + 1 || x == rx2 + 2))) {
        printf("|");  // Отрисовка ракеток
      } else if (x == ball_x && y == ball_y) {
        printf("@");  // Отрисовка мяча
      } else if (y == width / 2 - 1) {
        printf("|");  // Отрисовка сетки
      } else if (x == score_x && y == width / 2 - 7) {
        printf("%02d", player1);  // Отрисовка счета игрока 1
        y++;
      } else if (x == score_x && y == width / 2 + 4) {
        printf("%02d", player2);  // Отрисовка счета игрока 2
        y++;
      } else if (y == width - 2) {
        printf("#");  // Отрисовка правой стенки
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
  //

  // Нижняя часть поля
  for (int i = 0; i < 80; i++) {
    printf("#");
  }
  printf("\n");
  //
}

void final_field(int ry1, int ry2, int rx1, int rx2, int ball_x, int ball_y,
                 int width, int height, int score_x, int player1, int player2) {
  for (int i = 0; i < 80; i++) {
    printf("#");  // Верхняя часть поля
  }
  printf("\n");
  for (int x = 0; x < height - 2; x++) {  // Основная отрисовка
    printf("#");                          // Левая стенка
    for (int y = 0; y < width; y++) {
      if ((y == ry1 && (x == rx1 || x == rx1 + 1 || x == rx1 + 2)) ||
          (y == ry2 && (x == rx2 || x == rx2 + 1 || x == rx2 + 2))) {
        printf("|");  // Отрисовка ракеток
      } else if (x == 2 && y == 33) {
        if (player1 > player2) {
          printf("Player 1 win!");  // Отрисовка победителя
        } else {
          printf("Player 2 win!");
        }
        y = y + 12;
      } else if (x == ball_x && y == ball_y) {
        printf("@");  // Отрисовка мяча
      } else if (y == width / 2 - 1) {
        printf("|");  // Отрисовка сетки
      } else if (x == score_x && y == width / 2 - 7) {
        printf("%02d", player1);  // Отрисовка счета игрока 1
        y++;
      } else if (x == score_x && y == width / 2 + 4) {
        printf("%02d", player2);  // Отрисовка счета игрока 2
        y++;
      } else if (y == width - 2) {
        printf("#");  // Отрисовка правой стенки
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }

  for (int i = 0; i < 80; i++) {
    printf("#");  // Нижняя часть поля
  }
  printf("\n");
}

int rocket_touch(int rx1, int rx2, int ry1, int ry2, int ball_x, int ball_y) {
  if (ball_y == ry1 + 1 &&
      (ball_x == rx1 || ball_x == rx1 + 1 || ball_x == rx1 + 2))
    return 1;
  if (ball_y == ry2 - 1 &&
      (ball_x == rx2 || ball_x == rx2 + 1 || ball_x == rx2 + 2))
    return 1;
  return 0;
}

int vert_mov(int ball_x) {
  if (ball_x == 22) return 1;
  if (ball_x == 0)
    return -1;
  else
    return 0;
}

int change_mov_y(int m_ball_y) {
  if (m_ball_y == 1) return 1;
  if (m_ball_y == -1)
    return -1;
  else
    return 0;
}

int change_mov_x(int m_ball_x) {
  if (m_ball_x == -1) return 1;
  if (m_ball_x == 1)
    return -1;
  else
    return 0;
}
