#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

class Pixel{
public:

    void drawPixel(int x, int y){
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
    }
    // DDA Algo
    void drawLine(int x1, int y1, int x2, int y2){
       float dx = x2 - x1;
       float dy = y2 - y1;
       int step = max(abs(dx), abs(dy));
       float xIncrement = dx/step;
       float yIncrement = dy/step;

       float x = x1;
       float y = y1;
       for(int i = 0; i <= step; i++){
            drawPixel(round(x), round(y));
            x += xIncrement;
            y += yIncrement;
       }
    }

    void drawLine(int x1, int y1, int x2, int y2, bool bresenham){
        int dx = abs(x2 - x1); // Absolute difference in x
        int dy = abs(y2 - y1); // Absolute difference in y

        int x = x1; // Starting x-coordinate
        int y = y1; // Starting y-coordinate

        int sx = (x2 > x1) ? 1 : -1; // Step for x (direction)
        int sy = (y2 > y1) ? 1 : -1; // Step for y (direction)

        int err = 2 * dy - dx; // Initial decision parameter

        int i = 1;
        do {
            drawPixel(x, y); // Plot the pixel

            if (err >= 0) {
                y += sy;         // Increment y when error is non-negative
                err -= 2 * dx;   // Adjust the error parameter
            }

            x += sx;             // Always increment x
            err += 2 * dy;       // Update the error parameter
            i++;
        } while (i <= dx);

    }
};

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    int x1 = 200, y1 = 0, x2 = 0, y2 = 200;
    Pixel pixel;
    glColor3f(1.0, 0.0, 0.0);
    pixel.drawLine(x1, y1, x2, y2);

    glColor3f(0.0, 1.0, 0.0);
    pixel.drawLine(x1 + 10, y1, x2+10, y2, true);




    glFlush();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    gluOrtho2D(0,500,0, 500);
}


int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("DDA and Bresenham's Line Drawing");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
};
