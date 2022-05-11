#ifndef POINT_INCLUDED
#define POINT_INCLUDED

#include <iostream>
using std::size_t; using std::cout;

template<size_t N, typename T>
struct Point{
    
    //Constructors & Destructor
    Point();
    Point(T*);
    ~Point();

    //Auxiliar Function
    void print();
    
    //Operators
    Point<N,T>& operator = (Point<N,T>&);
    T  operator []  (std::size_t) const;
    
    T* coords;
private:
    size_t _size;
};

template<size_t N, typename T>
Point<N,T>::Point():_size(N){
    coords = new T[N];
    for(size_t i = 0; i < _size; i++){
        coords[i]=0;
    }
}

template<size_t N, typename T>
Point<N,T>::Point(T* _coords):_size(N){
    coords = new T[N];
    for(size_t i = 0; i < _size; i++){
        coords[i]=_coords[i];   
    }
}

template<size_t N, typename T>
Point<N,T>::~Point(){

}

template <size_t N, typename T>
T Point<N, T>::operator[] (size_t i) const{
    return coords[i];
}

template <size_t N, typename T>
Point<N, T>& Point<N, T>::operator=(Point<N,T>& point)
{   
    for (size_t i = 0; i < _size; i++)
    {
        coords[i] = point[i];
    }
    return *this;
}

template <size_t N, typename T>
void Point<N, T>::print(){
    cout<<"(";
    for(size_t i = 0; i < _size; i++){
        cout<<coords[i];
        if (i<_size-1)
        {
            cout<<", ";
        }
    }
    cout<<")\n";
}


#endif //POINT_INCLUDED