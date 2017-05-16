#ifndef PR_QUEUE_H
#define PR_QUEUE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>

template <class T, class Container = std::vector<T>,class comp
          = std::less<typename Container::value_type> >
class priority_queue {
protected:
    comp Compare;

    Container A;
    typedef typename Container::size_type sz_t;
    sz_t heap_size;

    //restores the properties of a heap for the i-th element
    void heapify(sz_t i){
        sz_t left = 2*i;
        sz_t right = 2*i+1;
        sz_t largest = i;
        if (left <= heap_size && Compare(A[left], A[largest]))
          largest = left;
        if (right <= heap_size && Compare(A[right], A[largest]))
          largest = right;
        if (largest != i){
            std::swap(A[i], A[largest]);
            heapify(largest);
        }
    }

    //builds a heap from an array
   void build_heap(T key){
       A.push_back(key);
       heap_size = A.size() - 1;
      // if (heap_size > 1)
        for(auto i = (A.size() / 2); i >= 1; --i)
             heapify(i);
   }

   //removes and returns the element with the max key
   void heap_extract_max(){
       if(heap_size < 1)
            return;
        A[1] = A[heap_size];
        --heap_size;
        heapify(1);
        A.resize(heap_size + 1);
   }

public:
   priority_queue(){
       A = Container();
       heap_size = 0;
       A.resize(1);
   }

   virtual void push(T key){
       build_heap(key);
   }

   const T & top(){return A[1];}

   void pop(){
       heap_extract_max();
   }

   bool empty(){return heap_size < 1;}

   sz_t size(){return A.size();}

};


template <class T, class Container = std::vector<T>,class comp
          = std::less<typename Container::value_type> >
class fix_priority_queue: public priority_queue<T> {
    typedef typename Container::size_type sz_t;
    sz_t max_size;

public:
   fix_priority_queue(sz_t mx_sz): priority_queue<T>(){
       max_size = mx_sz;
   }

   void push(T key){
       if (priority_queue<T>::heap_size == max_size + 1)
           priority_queue<T>::pop();
       priority_queue<T>::push(key);
   }

};

void time_test_queue(int cnt);

#endif // PR_QUEUE_H
