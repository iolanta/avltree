#include "pr_queue.h"
#include <ctime>
#include <deque>

void time_test_queue(int cnt){
    time_t start;
    time_t finish;
    priority_queue<int> pv;
    double pv_res;

    priority_queue<int, std::deque<int>> pq;
    double pq_res;

    start = clock();
    for(int i = 0; i< cnt; ++i){
        pv.push(rand());
    }
     finish = clock();
     pv_res = double(finish - start) / CLOCKS_PER_SEC;

     start = clock();
     for(int i = 0; i< cnt; ++i){
         pq.push(rand());
     }
     finish = clock();
     pq_res = double(finish - start) / CLOCKS_PER_SEC;

     std::cout << "Time test for "<< cnt <<" insertions"<< std::endl;
     std::cout << "Priority_queue<int, vector>: " << pv_res << " sec." << '\n'
               << "Priotity_queue<int, deque>: " << pq_res << " sec." << std::endl;
}
