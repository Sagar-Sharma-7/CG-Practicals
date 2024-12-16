#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

void drawLine(float x1, float y1, float x2, float y2){
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void kochCurve(float x1, float y1, float x2, float y2, int depth){
    if(depth==0){
        drawLine(x1, y1, x2, y2);
        return;
    }

    float dx = x2 - x1;
    float dy = y2 - y1;

    float x3 = x1 + dx/3.0;
    float y3 = y1 + dy/3.0;

    float x5 = x1 + 2*dx/3.0;
    float y5 = y1 + 2*dy/3.0;

    float x4 = x3 + (cos(M_PI/3.0) * (x5 - x3) - sin(M_PI/3.0) *(y5 - y3));
    float y4 = y3 + (sin(M_PI/3.0)*(x5 - x3) + cos(M_PI/3.0) * (y5 - y3));

    kochCurve(x1, y1, x3, y3, depth - 1);
    kochCurve(x3, y3, x4, y4, depth - 1);
    kochCurve(x4, y4, x5, y5, depth - 1);
    kochCurve(x5, y5, x2, y2, depth - 1);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    int depth = 4;
    float x1 = -200.0, y1 = 0.0, x2 = 200.0, y2 = 0.0;
    glColor3f(0.0, 1.0, 0.0);
    kochCurve(x1, y1,x2, y2, depth);
    glFlush();
}
void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    gluOrtho2D(-300, 300, -300, 300);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("koch curve");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


