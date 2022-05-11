#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include "QTree.h"
using namespace std;

typedef QTree<size_t(2), double> QTree2D;
typedef Point<size_t(2), double> Point2D;

size_t N, N_points;

int main(){
    ifstream file("../data/points.in");
    file>>N>>N_points;
    double** coords= new double*[N];
    for(size_t i = 0; i < N; i++){
        coords[i] = new double[N];
    }
    for(size_t i = 0; i < N; i++){
        for(size_t j = 0; j < N; j++){
            file>>coords[i][j];
        }
    }
    Point2D* bounds= new Point2D[N];
    for(size_t i = 0; i < N; i++){
        Point2D* t = new Point2D(coords[i]);
        bounds[i]=*t;
    }
    file>>N_points;
    vector<Point2D> Points;
    for(size_t i = 0; i < N_points; i++){
        double* coords=new double[2];
        file>>coords[0]>>coords[1];
        Point2D* t = new Point2D(coords);
        Points.emplace_back(*t);
    }
    QTree2D myQTree(bounds, 4);
    cout<<"Initiating Quad-Tree testing...\n";
    cout<<"\n(1) Initiating Quad-Tree Insertion assert...\n";
    for(size_t i = 0; i < N_points; i++){
        assert(myQTree.insert(Points[i], myQTree.root())==1);
    }
    cout<<"  -> Insertion test passed!!\n";
    cout<<"\n(2) Initiating Quad-Tree Region-Query assert...\n";
    size_t* path = new size_t[4];
    for(size_t i = 0; i < 4; i++){
        path[i]=0;
    }
    assert(myQTree.query(path, 4) == N_points);
    cout<<"  -> Query test passed!!\n";
}