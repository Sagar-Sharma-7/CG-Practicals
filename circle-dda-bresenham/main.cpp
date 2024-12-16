#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;


class Pixel{
protected:
    int centerX, centerY;
public:
    Pixel(int x = 0, int y = 0){
        centerX = x;
        centerY = y;
    }

    void drawPixel(int x, int y){
        glBegin(GL_POINTS);
        glVertex2i(centerX + x, centerY + y);
        glEnd();
    }
};

class Circle : public Pixel{
private:
    int radius;
    void drawSymmetricalPixels(int x, int y){
        drawPixel(x, y);
        drawPixel(x, -y);
        drawPixel(-x, y);
        drawPixel(-x, -y);
        drawPixel(y, x);
        drawPixel(-y, x);
        drawPixel(y, -x);
        drawPixel(-y, -x);
    };
public:
    Circle(int x, int y, int r):Pixel(x,y){
        radius = r;
    }


    // Bresenham's algo
     void drawCircle() {
        int x = 0;
        int y = radius;
        int decision = 3 - (2 * radius);

        drawSymmetricalPixels(x, y);

        while (y >= x) {
            x++;
            if (decision > 0) {
                y--;
                decision += 4 * (x - y) + 10;
            } else {
                decision += 4 * x + 6;
            }
            drawSymmetricalPixels(x, y);
        }
    }

    void drawCircle(float){
        int x = 0;
        int y = radius;
        float decision = 5/4 - radius;
        drawSymmetricalPixels(x,y);
        while(y > x){
            if(decision < 0){
                x++;
                decision += 2*x + 1;
            }else{
                y--;
                x++;
                decision += 2*(x-y) + 1;
            }
            drawSymmetricalPixels(x, y);
        }
    }


};

Circle* circle;

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    circle->drawCircle(0.0f);
    glFlush();
}

void initOpenGL(){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0,0.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-320, 320, -320, 320);

}

int main(int argc, char** argv){
    int centerX, centerY, radius;
    cout << "Enter x: ";
    cin >> centerX;
    cout << "Enter y: ";
    cin >> centerY;
    cout << "Enter radius: ";
    cin >> radius;

    circle = new Circle(centerX, centerY, radius);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(100, 200);
    glutCreateWindow("Circle");
    initOpenGL();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
