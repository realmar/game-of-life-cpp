#define INITIAL_FPS 4;

#define ALIVE_CELL_COLOR glColor3f(0.0f, 0.0f, 0.0f);
#define DEAD_CELL_COLOR glColor3f(1.0f, 1.0f, 1.0f);

#define ROUND_ZERO(a) ((a) - 1 < 0 ? 0 : (a) - 1)
#define ROUND_MAX(a, max) ((a) + 1 > (max) ? (max) : (a) + 1)

// using opengl for rendering
#include <GL/freeglut.h>
#include <GL/glut.h>

#include <iostream>
#include <algorithm>

const unsigned int WIDTH = 1024;
const unsigned int HEIGHT = 1024;

const unsigned int ROWS = 140;
const unsigned int COLUMNS = 140;

unsigned int FPS = INITIAL_FPS;

const float CELL_WIDTH = (float)WIDTH / (float)ROWS;
const float CELL_HEIGHT = (float)HEIGHT / (float)COLUMNS;

bool cells[COLUMNS][ROWS];

bool continue_calc = true;

void initCells(bool randomize) {
  for(unsigned int i = 0; i < COLUMNS; i++) {
    for(unsigned int j = 0; j < ROWS; j++) {
      if((int)rand()%2 == 0 || !randomize)
        cells[i][j] = false;
      else
        cells[i][j] = true;
    }
  }

  continue_calc = randomize;
  if(!randomize) FPS = 60;
}

void init(void) {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 1.0, 0.0, 1.0);
  glMatrixMode(GL_MODELVIEW);

  initCells(true);
}

unsigned int getAliveNeightborCount(const int y, const int x) {
  unsigned int neighbours = 0;

  // horizonal neighbours
  if(cells[y][ROUND_ZERO(x)])
    neighbours++;

  if(cells[y][ROUND_MAX(x, COLUMNS)])
    neighbours++;

  // vertical neighbours
  if(cells[ROUND_ZERO(y)][x])
    neighbours++;

  if(cells[ROUND_MAX(y, COLUMNS - 1)][x])
    neighbours++;

  // diagonal neighbours
  if(cells[ROUND_ZERO(y)][ROUND_MAX(x, ROWS - 1)])
    neighbours++;

  if(cells[ROUND_ZERO(y)][ROUND_ZERO(x)])
    neighbours++;

  if(cells[ROUND_MAX(y, COLUMNS - 1)][ROUND_MAX(x, ROWS - 1)])
    neighbours++;

  if(cells[ROUND_MAX(y, COLUMNS - 1)][ROUND_ZERO(x)])
    neighbours++;

  return neighbours;
}

void recalculateCells(void) {
  bool new_cells[COLUMNS][ROWS];
  std::copy(&cells[0][0], &cells[0][0] + ROWS * COLUMNS, &new_cells[0][0]);

  for(unsigned int i = 0; i < COLUMNS; i++) {
    for(unsigned int j = 0; j < ROWS; j++) {
      // source of comments on the behavior are from wikipedia (https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

      unsigned int n_count = getAliveNeightborCount(i, j);
      // alive
      if(cells[i][j]) {

        // Any live cell with fewer than two live neighbours dies, as if caused by under-population.
        // and
        // Any live cell with more than three live neighbours dies, as if by over-population.
        if(n_count < 2 || n_count > 3)
          new_cells[i][j] = false;

        // Any live cell with two or three live neighbours lives on to the next generation.
        // nothing to do here, the cell survives
      }else{    // dead
        // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
        if(n_count == 3)
          new_cells[i][j] = true;
      }
    }
  }

  std::copy(&new_cells[0][0], &new_cells[0][0] + ROWS * COLUMNS, &cells[0][0]);
}

void renderFunction(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for(unsigned int i = 0; i < COLUMNS; i++) {
    for(unsigned int j = 0; j < ROWS; j++) {
      if(cells[i][j])
        ALIVE_CELL_COLOR
      else
        DEAD_CELL_COLOR

      glRectf(
        (CELL_WIDTH * j) / WIDTH,
        (CELL_HEIGHT * i) / HEIGHT,
        (CELL_WIDTH * (j + 1)) / WIDTH,
        (CELL_HEIGHT * (i + 1)) / HEIGHT
      );

    }
  }

  if(continue_calc) recalculateCells();
  glutSwapBuffers();
}

void timer(int) {
  glutPostRedisplay();
  glutTimerFunc(1000 / FPS, timer, 0);
}

void keyboardInput(unsigned char key, int x, int y) {
  switch(key) {
    case 'c':
      initCells(false);
      return;
    case 'r':
      initCells(true);
      return;
    case 's':
      continue_calc = true;
      FPS = INITIAL_FPS;
      return;
    case '1':
      // glider gun

      initCells(false);
      unsigned int start_x = (unsigned int)(ROWS / 2) - 18;
      unsigned int start_y = (unsigned int)(COLUMNS / 2) - 4;

      cells[start_y][start_x] = true;
      cells[start_y][start_x + 1] = true;
      cells[start_y + 1][start_x] = true;
      cells[start_y + 1][start_x + 1] = true;

      cells[start_y][start_x + 10] = true;
      cells[start_y + 1][start_x + 10] = true;
      cells[start_y - 1][start_x + 10] = true;

      cells[start_y + 2][start_x + 10 + 1] = true;
      cells[start_y - 2][start_x + 10 + 1] = true;

      cells[start_y + 3][start_x + 10 + 2] = true;
      cells[start_y - 3][start_x + 10 + 2] = true;
      cells[start_y + 3][start_x + 10 + 3] = true;
      cells[start_y - 3][start_x + 10 + 3] = true;

      cells[start_y][start_x + 10 + 4] = true;

      cells[start_y + 2][start_x + 10 + 5] = true;
      cells[start_y - 2][start_x + 10 + 5] = true;

      cells[start_y + 1][start_x + 10 + 6] = true;
      cells[start_y][start_x + 10 + 6] = true;
      cells[start_y - 1][start_x + 10 + 6] = true;

      cells[start_y][start_x + 10 + 7] = true;

      cells[start_y + 1][start_x + 20] = true;
      cells[start_y + 2][start_x + 20] = true;
      cells[start_y + 3][start_x + 20] = true;

      cells[start_y + 1][start_x + 21] = true;
      cells[start_y + 2][start_x + 21] = true;
      cells[start_y + 3][start_x + 21] = true;

      cells[start_y + 4][start_x + 22] = true;
      cells[start_y][start_x + 22] = true;

      cells[start_y + 5][start_x + 24] = true;
      cells[start_y + 4][start_x + 24] = true;
      cells[start_y][start_x + 24] = true;
      cells[start_y - 1][start_x + 24] = true;

      cells[start_y + 2][start_x + 34] = true;
      cells[start_y + 3][start_x + 34] = true;

      cells[start_y + 2][start_x + 35] = true;
      cells[start_y + 3][start_x + 35] = true;

      return;
  }
}

void adaptCell(const int& mx, const int& my, const bool& revert = true) {
  unsigned int x = (unsigned int)(mx / CELL_WIDTH);
  unsigned int y = COLUMNS - (unsigned int)(my / CELL_HEIGHT) - 1;
  if(revert) cells[y][x] = !cells[y][x];
  else cells[y][x] = true;
}

void mouseInput(int button, int state, int mx, int my) {
  if(state == GLUT_UP) adaptCell(mx, my);
}

void continuousMouseInput(int mx, int my) {
  adaptCell(mx, my, false);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Game Of Life");
  glutDisplayFunc(renderFunction);
  glutKeyboardFunc(keyboardInput);
  glutMouseFunc(mouseInput);
  glutMotionFunc(continuousMouseInput);

  init();

  glutTimerFunc(1000 / FPS, timer, 0);

  glutMainLoop();
  return 0;
}
