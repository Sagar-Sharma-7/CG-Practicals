#include <GL/glut.h>
#include <cmath>
using namespace std;

void drawtri(){
    glClear(GL_COLOR_BUFFER_BIT);
    float sideLength = 100.0;
    float height = (sqrt(3.0)/2.0) * sideLength;
    float vertices[3][2] = {
        {
            -sideLength/2.0, -height/3.0
        },
        {
            sideLength/2.0, -height/3.0
        },
        {
            0.0, 2.0 * height/3.0
        }
    };

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 0.0, 0.0);
    for(int i = 0; i < 3; i++){
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();

    glFlush();

}

void drawCircle(float radius){
    int numSegment = 100;
    float angleStep = 2.0 * M_PI/numSegment;
    glColor3f(0.0f, 0.0f, 1.0f); // Set color to blue
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i< numSegment; i++){
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the equilateral triangle
    drawtri();

    // Draw a circle with radius 0.5
    int height = (sqrt(3)/2) * 100;
    float r1 = height/3.0;
    drawCircle(r1);
    float r2 = 2.0 * height/3.0;
    drawCircle(r2);


    glFlush(); // Ensure all OpenGL commands are executed
}

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(-300, 300, -300, 300);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);              // Set window size
    glutInitWindowPosition(100, 100);          // Set window position
    glutCreateWindow("Equilateral Triangle");  // Create window with title

    init();
    glutDisplayFunc(display);  // Set the display callback
    glutMainLoop();                            // Enter the event loop

    return 0;
}
