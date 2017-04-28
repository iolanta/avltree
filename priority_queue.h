#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <functional>
#include <vector>
#include <algorithm>

template <class T, class Container = std::vector<T>,class comp
          = std::less<typename Container::value_type> >
class Priority_queue {
private:
    comp Compare;
    Container A;
    typedef typename Container::size_type sz_t;
    sz_t heap_size;

    void heapify(sz_t i){
      sz_t left = 2*i;
      sz_t right = 2*i+1;
      sz_t largest;
      if (left <= A.size() && Compare(A[i], A[left]))
        largest = left;
      else
          largest = i;
      if (right <= A.size() && Compare(A[largest], A[right]))
        largest = right;
      if (largest != i){
          std::swap(A[i], A[largest]);
          heapify(largest);
          }
    }

    void build_heap(){
     // heap_size = A.size();
        for(sz_t i = floor(A.size()/2); i >= 1; --i)
            heapify(i);
    }

    void heap_sort(){
        build_heap();
        for(auto i = A.size(); i >= 2; --i){
            std::swap(A[0], A[i - 2]);
            --heap_size;
            heapify(i);
        }
    }

  virtual void heap_insert(T key){
        ++heap_size;
        sz_t i = heap_size;
        A.resize(heap_size+1);
        while(i>1 && Compare(A[i/2],key)){
                A[i] = A[i/2];
                i = i/2;
            }
        A[i] = key;
        heapify(i);
    }
    void heap_extract_max(){
        if(heap_size < 1)
            return;
        A[0] = A[heap_size];
       --heap_size;
        heapify(0);
    }

public:
    Priority_queue(){
        A = Container();
        heap_size = 0;
        A.resize(heap_size+1);
    }

    const T& top(){ return A[1];}

    void pop(){
        heap_extract_max();
    }

    void push(const T&k){
        heap_insert(k);
        heap_sort();
    }

    bool empty(){return heap_size < 1;}


    };

template <class T,class _Compare
          = std::less<T> >
class fixed_Priority_queue {
public:
    _Compare Compare;
    T *A;
    typedef size_t sz_t;
    sz_t heap_size;
    sz_t max_sz;


    void heapify(sz_t i){
      sz_t left = 2*i;
      sz_t right = 2*i+1;
      sz_t largest = i;
      if (left <= heap_size && Compare( A[left], A[largest]))
        largest = left;
      if (right <= heap_size && Compare(A[right], A[largest]))
        largest = right;
      if (largest != i){
          std::swap(A[i], A[largest]);
          heapify(largest);
          }
    }

    void build_heap(){
      heap_size = max_sz;
      for(sz_t i = heap_size/2; i >= 1; --i)
         heapify(i);
    }


  virtual  void heap_insert( const T &key){
        if (heap_size == max_sz)
            return;
        heap_size+=1;
        sz_t i = heap_size;
        while(i>1 && Compare(A[i/2],key)){
                A[i] = A[i/2];
                i = i/2;
            }
       // A.resize(heap_size);
        A[i] = key;
        heapify(i);
    }
    void heap_extract_max(){
        if(heap_size<1)
            return;
        A[1] = A[heap_size-1];
        heap_size = heap_size -1;
        heapify(1);
    }


public:
    fixed_Priority_queue(size_t mx){
        max_sz = mx;
        A = new T[mx+1];
        heap_size = 0;
    }

    const T& top(){ return A[1];}

    void pop(){
        heap_extract_max();
    }

    void push(const T&k){
        heap_insert(k);
    }

    bool empty(){return heap_size<1;}

    void sort(){
        build_heap();
    }


    ~fixed_Priority_queue(){
    delete[] A;
}
    };

#endif // PRIORITY_QUEUE_H
