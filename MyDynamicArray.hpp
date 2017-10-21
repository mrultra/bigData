//
// Created by highz on 10/8/2017.
//

#ifndef BIGDATA_MYDYNAMICARRAY_HPP
#define BIGDATA_MYDYNAMICARRAY_HPP

/*
 *
 * This is the coding part!
 *
 */

#include <iostream>

using namespace std;

template<typename T>
class MyDynamicArray {

private:

    T *values;
    int cap;
    T dummy;

public:

    /*
     *  This function I brought in because <algorithms> was not working properly with cLion.
     *  credits go to -> http://www.cplusplus.com/reference/algorithm/min/
     */
    const T &min(const T &a, const T &b) {
        return !(b < a) ? a : b;
    } // min function

    MyDynamicArray(int = 2); // default constructor

    ~MyDynamicArray() { delete[] values; } // deconstructor


    int capacity() const { return cap; }; // getter
    void capacity(int); //setter

    T operator[](int) const; // Getter
    T &operator[](int); // setter


};

template<typename T>
MyDynamicArray<T>::MyDynamicArray(int cap) {

    this->cap = cap; // sets capacity
    values = new T[cap];

    for (int i = 0; i < cap; ++i) {

        values[i] = T();

    }// for init

} // Constructor

template<typename T>
T MyDynamicArray<T>::operator[](int index) const {

    if (index < 0 || index >= cap) {
        //std::cout << "No such value." << std::endl;
        return T();
    } // if

    //std::cout << "You got this -> ";
    return values[index];


} // getter

template<typename T>
T &MyDynamicArray<T>::operator[](int index) {

    if (index < 0) {
        return dummy;
    } // if
    else if (index >= cap) {
        capacity(2 * index);
    } // else
        return values[index];

}// setter

template<typename T>
void MyDynamicArray<T>::capacity(int newCap) {

    T *temp = new T[newCap];

    // int limit = min(newCap, cap);

    int limit = newCap;

    if (limit > cap) {
        limit = cap;
    }//if

    for (int i = 0; i < limit; ++i) {

        temp[i] = values[i]; // copy contents from one array to another.

    } // for


    for (int j = limit; j < cap; ++j) {

        values[j] = T(); // set defaults for left overs

    }// for


    delete[] values;

    values = temp;

    cap = newCap;

}// capacity

#endif //BIGDATA_MYDYNAMICARRAY_HPP
