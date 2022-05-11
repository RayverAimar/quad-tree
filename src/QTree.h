#ifndef Q_TREE_INCLUDED
#define Q_TREE_INCLUDED

#include "QTreeNode.h"
#include <cmath>

template<size_t N, typename T>
struct QTree{

private:

    QTreeNode<N,T>* _root;
    size_t max_depth;
    Point<N,T>* m_bounds;

public:
    //Constructors & Destructors
    QTree();
    QTree(Point<N,T>*, size_t);
    ~QTree();

    //Primary Functions
    bool insert(Point<N,T>, QTreeNode<N,T>*) const;
    size_t query(size_t*, size_t) const;

    //Auxiliar Functions
    QTreeNode<N,T>* root();
    void __init__(QTreeNode<N,T>*&, Point<N,T>*, size_t);  
};

template<size_t N, typename T>
QTree<N,T>::QTree():_root(nullptr), max_depth(0){
    m_bounds = new Point<N,T>[N];
    for(size_t i = 0; i < N; i++){
        size_t coords[N];
        for(size_t j = 0; j < N; j++){
            coords[j]=1000*pow(-1,j+2);
            m_bounds[i].coords[j]=coords[j];
        } 
    }
}

template<size_t N, typename T>
QTree<N,T>::QTree(Point<N,T>* p, size_t _max_depth): max_depth(_max_depth){
    m_bounds = new Point<N,T>[N];
    for(size_t i = 0; i < N; i++){
        m_bounds[i]=p[i];
    }
    _root = new QTreeNode<N,T>(m_bounds, 0);
    __init__(_root, m_bounds, 0);
}

template<size_t N, typename T>
QTree<N,T>::~QTree(){
    delete[] m_bounds;
}

template<size_t N, typename T>
void QTree<N,T>::__init__(QTreeNode<N,T>*& p, Point<N,T>* _bounds, size_t cur_depth){
    p = new QTreeNode<N,T>(_bounds, cur_depth);
    if(cur_depth==max_depth)
    {
        return;
    }

    T* mid_bounds = new T[N];
    mid_bounds[0]=(_bounds[1].coords[0]-_bounds[0].coords[0])/2;
    mid_bounds[1]=(_bounds[0].coords[1]-_bounds[1].coords[1])/2;

    Point<N,T>* temp_bounds = new Point<N,T>[N];

    temp_bounds[0] = _bounds[0];
    temp_bounds[1].coords[0]=_bounds[1].coords[0]-mid_bounds[0];
    temp_bounds[1].coords[1]=_bounds[1].coords[1]+mid_bounds[1];
    __init__(p->m_children[0], temp_bounds, cur_depth+1);
    temp_bounds[0].coords[0] += mid_bounds[0]; 
    temp_bounds[1].coords[0] += mid_bounds[0];
    __init__(p->m_children[1], temp_bounds, cur_depth+1);
    temp_bounds[0].coords[0] -= mid_bounds[0];
    temp_bounds[0].coords[1] = _bounds[0].coords[1]-mid_bounds[1];
    temp_bounds[1] = _bounds[1];
    temp_bounds[1].coords[0] -= mid_bounds[0]; 
    __init__(p->m_children[2], temp_bounds, cur_depth+1);
    temp_bounds[0].coords[0]+=mid_bounds[0];
    temp_bounds[1].coords[0]+=mid_bounds[0];
    __init__(p->m_children[3], temp_bounds, cur_depth+1);   
}

template<size_t N, typename T>
bool QTree<N,T>::insert(Point<N,T> p, QTreeNode<N,T>* cur_node) const{
    if(cur_node->_depth==max_depth){
        cur_node->n_points++;
        return 1;
    }
    for(size_t i = 0; i < 4; i++){
        if(cur_node->m_children[i]->converge(p)){
            cur_node->n_points++;
            return insert(p, cur_node->m_children[i]);
        }
    }
    return 0;
}

template<size_t N, typename T>
size_t QTree<N,T>::query(size_t* path, size_t depth) const{
    if(depth == 1){
        return _root->n_points;
    }
    QTreeNode<N,T>* p= _root;
    for(size_t i = 1; i < depth; i++){
        p= p->m_children[path[i]];
    }
    return p->n_points;
}

template<size_t N, typename T>
QTreeNode<N,T>* QTree<N,T>::root(){
    return _root;
}

#endif //Q_TREE_INCLUDED