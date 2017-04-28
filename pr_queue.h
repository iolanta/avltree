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
       sz_t l = 2 * i;
       sz_t r = 2 * i + 1;
       sz_t largest;
       if (l <= A.size() && Compare(A[i], A[l]))
           largest = l;
       else
           largest = i;
       if (r <= A.size() && Compare(A[largest], A[r]))
           largest = r;
       if (largest != i){
           std::swap(A[i], A[largest]);
           heapify(largest);
       }
    }

    //builds a heap from an array
   void build_heap(T key){
       A.push_back(key);
       heap_size = A.size();
       if (heap_size > 1)
        for(auto i = std::floor(A.size() / 2); i >= 0; --i)
             heapify(i);
   }

   //removes and returns the element with the max key
   void heap_extract_max(){
       if(heap_size<1)
            return;
        A[0] = A[heap_size - 1];
        --heap_size;
        heapify(0);
        A.resize(heap_size);
   }

   /*void heapsort(){
       for (auto i = A.size(); i >= 2; --i){
           std::swap(A[0], A[i]);
           --heap_size;
           heapify(0);
       }
   }*/

public:
   priority_queue(){
       A = Container();
       heap_size = 0;
       A.resize(heap_size);
   }

   virtual void push(T key){
       build_heap(key);
   }

   const T & top(){return A[0];}

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
       if (priority_queue<T>::heap_size == max_size)
           return;
       priority_queue<T>::push(key);
   }

};

#endif // PR_QUEUE_H
