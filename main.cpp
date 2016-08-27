#define ALIVE_CELL_COLOR glColor3f(0.0f, 0.0f, 0.0f);
#define DEAD_CELL_COLOR glColor3f(1.0f, 1.0f, 1.0f);

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

void recalculateCells(void) {
  for(unsigned int i = 0; i < COLUMNS; i++) {
    for(unsigned int j = 0; j < ROWS; j++) {
      // source of comments on the behavior are from wikipedia (https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)
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
  glutTimerFunc(1000 / 20, timer, 0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Game Of Life");
  glutDisplayFunc(renderFunction);
  init();

  glutTimerFunc(1000 / 20, timer, 0);

  glutMainLoop();
  return 0;
}
