#ifndef QTREE_NODE_INCLUDED
#define QTREE_NODE_INCLUDED

#include <iostream>
#include "Point.h"

using std::size_t;

template<size_t N, typename T>
struct QTreeNode{
    //Constructors & Destructors
    QTreeNode();
    QTreeNode(Point<N,T>*, size_t);
    ~QTreeNode();

    //Auxiliar Function
    bool converge(Point<N,T>) const;
    
    Point<N, T>* m_bounds;
    QTreeNode* m_children[4];
    size_t _depth, n_points;
};

template<size_t N, typename T>
bool QTreeNode<N,T>::converge(Point<N,T> point) const {
    //cout<<point.coords[0]<<" >= "<<m_bounds[0].coords[0]<<" && "<<point.coords[0]<<" <= "<<m_bounds[1].coords[0]<<"\n";
    //cout<<point.coords[1]<<" <= "<<m_bounds[0].coords[1]<<" && "<<point.coords[1]<<" >= "<<m_bounds[1].coords[1]<<"\n";
    //cout<<"Next Convergesion\n";
    bool x = point.coords[0]>=m_bounds[0].coords[0] && point.coords[0]<=m_bounds[1].coords[0];
    bool y = point.coords[1]<=m_bounds[0].coords[1] && point.coords[1]>=m_bounds[1].coords[1];
    return x&&y;
}

template<size_t N, typename T>
QTreeNode<N,T>::QTreeNode():_depth(0),n_points(0){
    m_bounds = new T[N];
    for(size_t i = 0; i < N; i++){
        m_bounds[i]=0;
    }
    m_children[0]=m_children[1]=m_children[2]=m_children[3]=nullptr;
}

template<size_t N, typename T>
QTreeNode<N,T>::QTreeNode(Point<N,T>* _bounds, size_t depth): _depth(depth), n_points(0){
    m_bounds = new Point<N,T>[N];
    for(size_t i = 0; i < N; i++){
        m_bounds[i]=_bounds[i];
    }
    m_children[0]=m_children[1]=m_children[2]=m_children[3]=nullptr;
}

template<size_t N, typename T>
QTreeNode<N,T>::~QTreeNode(){
    delete[] m_bounds;
    delete[] m_children;
}

#endif // QTREE_NODE_INCLUDED