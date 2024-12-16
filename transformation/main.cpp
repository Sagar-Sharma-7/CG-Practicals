#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

float vertices[4][2] = {
    {-100.0, -100.0}, // Bottom-left
    {100.0, -100.0},  // Bottom-right
    {100.0, 100.0},   // Top-right
    {-100.0, 100.0}
};

void drawSquare();
void translateSquare();
void RotateSquare();
void scaleSquare();
void menu(int);

void drawSquare(){
    glBegin(GL_POLYGON);
    for(int i = 0; i<4; i++){
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();
}

void translateSquare(){
    float tx, ty;
    cout << "Enter translation values: ";
    cin >> tx >> ty;
    for(int i = 0; i < 4; i++){
        vertices[i][0] += tx;
        vertices[i][1] += ty;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    drawSquare();
    glFlush();
}

void rotateSqaure(){
    float angle;
    cout << "Enter angle: ";
    cin >> angle;

    angle = angle * M_PI/180.0;
    float tempVertices[4][2];
    for(int i = 0; i < 4; i++){
        tempVertices[i][0] = vertices[i][0] * cos(angle) - vertices[i][1]*sin(angle);
        tempVertices[i][1] = vertices[i][0] * sin(angle) + vertices[i][1] * cos(angle);
    }

    for(int i = 0; i < 4; i++){
        vertices[i][0] = tempVertices[i][0];
        vertices[i][1] = tempVertices[i][1];
    }
    glClear(GL_COLOR_BUFFER_BIT);
    drawSquare();
    glFlush();
}

void scaleSquare(){
    float sx, sy;
    cout << "Enter scaling factors: ";
    cin >> sx >> sy;

    for(int i=0; i < 4; i++){
        vertices[i][0] *= sx;
        vertices[i][1] *= sy;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    drawSquare();
    glFlush();
}

void menu(int option){
    switch(option){
        case 1: translateSquare(); break;
        case 2: rotateSqaure(); break;
        case 3: scaleSquare(); break;
        case 4: exit(0); break;
        default: cout << "Invalid" << endl; break;
    }
}

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(-300, 300, -300, 300);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    drawSquare();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Transformation");

    init();
    glutDisplayFunc(display);
    glutCreateMenu(menu);
    glutAddMenuEntry("Translate", 1);
    glutAddMenuEntry("Rotate", 2);
    glutAddMenuEntry("Scale", 3);
    glutAddMenuEntry("Exit", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
