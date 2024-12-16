#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

// Base class to handle vertices
class Polygon {
protected:
    vector<pair<int, int>> vertices; // Stores vertices
    int ymin = 10000, ymax = -10000; // Bounding Y-coordinates

public:
    // Add a vertex to the polygon
    void addVertex(int x, int y) {
        vertices.emplace_back(x, y);
        ymin = min(ymin, y);
        ymax = max(ymax, y);
    }

    // Complete the polygon by connecting the last vertex to the first
    void completePolygon() {
        if (!vertices.empty()) {
            vertices.push_back(vertices[0]); // Close the polygon
        }
    }

    // Get the vertices of the polygon
    vector<pair<int, int>> getVertices() const {
        return vertices;
    }

    // Get the bounding Y-coordinates
    int getYMin() const { return ymin; }
    int getYMax() const { return ymax; }
};

// Derived class to add scan-line filling functionality
class FillablePolygon : public Polygon {
public:
    // Find intersections for a given scanline
    vector<int> findIntersections(int scanlineY) {
        vector<int> intersections;
        for (size_t i = 0; i < vertices.size() - 1; i++) {
            int x1 = vertices[i].first, y1 = vertices[i].second;
            int x2 = vertices[i + 1].first, y2 = vertices[i + 1].second;

            if (y1 > y2) {
                swap(x1, x2);
                swap(y1, y2);
            }

            if (scanlineY >= y1 && scanlineY < y2) {
                int intersectX = x1 + (float)(x2 - x1) * (scanlineY - y1) / (y2 - y1);
                intersections.push_back(intersectX);
            }
        }
        sort(intersections.begin(), intersections.end());
        return intersections;
    }

    // Draw and fill the polygon using the scan-line algorithm
    void drawAndFill() {
        // Draw the polygon outline
        glColor3f(0, 0, 0); // Black outline
        glBegin(GL_LINE_STRIP);
        for (auto &[x, y] : vertices) {
            glVertex2i(x, y);
        }
        glEnd();

        // Fill the polygon
        glColor3f(1, 0, 0); // Red fill
        for (int y = ymin; y <= ymax; y++) {
            vector<int> intersections = findIntersections(y);
            for (size_t i = 0; i < intersections.size(); i += 2) {
                glBegin(GL_LINES);
                glVertex2i(intersections[i], y);
                glVertex2i(intersections[i + 1], y);
                glEnd();
            }
        }
    }
};

// Create a global FillablePolygon object
FillablePolygon polygon;
bool polygonComplete = false;

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    polygon.drawAndFill();
    glFlush();
}

// Mouse callback to handle input
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        polygon.addVertex(x - 320, 240 - y); // Adjust coordinates
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        polygon.completePolygon();
        polygonComplete = true;
    }
    glutPostRedisplay();
}

// Initialize OpenGL settings
void initOpenGL() {
    glClearColor(1, 1, 1, 1); // White background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-320, 320, -240, 240); // Set coordinate system
}

// Main function
int main(int argc, char **argv) {
    cout << "Left-click to add vertices.\n";
    cout << "Right-click to complete and fill the polygon.\n";

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Scan Line Polygon Fill");

    initOpenGL();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
