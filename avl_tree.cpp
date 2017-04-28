#include "avl_tree.h"
#include <ctime>
#include <set>

void time_test(int cnt){
    time_t start;
    time_t finish;
    std::set<int> st;
    double st_res;

    avl_tree<int> tr;
    double tr_res;

    start = clock();
    for(int i = 0; i< cnt;++i){
        st.insert(rand());
    }
     finish = clock();
     st_res = double(finish - start) / CLOCKS_PER_SEC;

     start = clock();
     for(int i = 0; i< cnt;++i){
         tr.insert(rand());
     }
     finish = clock();
     tr_res = double(finish - start) / CLOCKS_PER_SEC;

     std::cout << "Time test for "<< cnt <<" insertions"<< std::endl;
     std::cout << "Set: " << st_res << " sec." << '\n'
               << "AVL Tree: " << tr_res << " sec." << std::endl;
}
