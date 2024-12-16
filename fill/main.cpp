#include <GL/glut.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Polygon{
protected:
    vector<pair<int,int>> vertices;
public:
    virtual void drawPolygon() = 0;
};

class Scanline: public Polygon{
private:
    int ymin, ymax;

    void calculateYBounds(){
        ymin = ymax = vertices[0].second;
        for(auto& vertex:vertices){
            if(vertex.second < ymin){
                ymin = vertex.second;
            }
            if(vertex.second > ymax){
                ymax = vertex.second;
            }
        }
    }

    void fillPolygon(){
        calculateYBounds();
    }
};
