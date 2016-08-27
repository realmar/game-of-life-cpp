#define FPS 4

#define ALIVE_CELL_COLOR glColor3f(0.0f, 0.0f, 0.0f);
#define DEAD_CELL_COLOR glColor3f(1.0f, 1.0f, 1.0f);

#define ROUND_ZERO(a) ((a) - 1 < 0 ? 0 : (a) - 1)
#define ROUND_MAX(a, max) ((a) + 1 > (max) ? (max) : (a) + 1)

// using opengl for rendering
#include <GL/freeglut.h>
#include <GL/glut.h>

#include <iostream>

const unsigned int WIDTH = 512;
const unsigned int HEIGHT = 512;

const unsigned int ROWS = 80;
const unsigned int COLUMNS = 80;

const float CELL_WIDTH = (float)WIDTH / (float)ROWS;
const float CELL_HEIGHT = (float)HEIGHT / (float)COLUMNS;

bool cells[COLUMNS][ROWS];

void initCells(void) {
  for(unsigned int i = 0; i < COLUMNS; i++) {
    for(unsigned int j = 0; j < ROWS; j++) {
      if((int)rand()%2 == 0)
        cells[i][j] = false;
      else
        cells[i][j] = true;
    }
  }
}

void init(void) {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 1.0, 0.0, 1.0);
  glMatrixMode(GL_MODELVIEW);

  initCells();
}

unsigned int getAliveNeightborCount(const int y, const int x) {
  unsigned int neighbours = 0;

  // horizonal neighbours
  if(cells[y][ROUND_ZERO(x)])
    neighbours++;

  if(cells[y][ROUND_MAX(x, WIDTH)])
    neighbours++;

  // vertical neighbours
  if(cells[ROUND_ZERO(y)][x])
    neighbours++;

  if(cells[ROUND_MAX(y, HEIGHT)][x])
    neighbours++;

  // diagonal neighbours
  if(cells[ROUND_ZERO(y)][ROUND_MAX(x, WIDTH)])
    neighbours++;

  if(cells[ROUND_ZERO(y)][ROUND_ZERO(x)])
    neighbours++;

  if(cells[ROUND_MAX(y, HEIGHT)][ROUND_MAX(x, WIDTH)])
    neighbours++;

  if(cells[ROUND_MAX(y, HEIGHT)][ROUND_ZERO(x)])
    neighbours++;

  return neighbours;
}

void recalculateCells(void) {
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
          cells[i][j] = false;

        // Any live cell with two or three live neighbours lives on to the next generation.
        // nothing to do here, the cell survives
      }else{    // dead
        // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
        if(n_count == 3)
          cells[i][j] == true;
      }
    }
  }
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

  recalculateCells();
  glutSwapBuffers();
}

void timer(int) {
  glutPostRedisplay();
  glutTimerFunc(1000 / FPS, timer, 0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Game Of Life");
  glutDisplayFunc(renderFunction);
  init();

  glutTimerFunc(1000 / FPS, timer, 0);

  glutMainLoop();
  return 0;
}
