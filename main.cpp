#include "avl_tree.h"
#include "pr_queue.h"
#include "text.h"
#include <cassert>
#include <queue>

int main()
{
    avl_tree<int> t;
    t.insert(15);
    t.insert(32);
    t.insert(35);
    t.erase(15);
    t.erase(32);
    t.erase(35);
    assert(t.empty());
    //t.print();
    //t.write_to_file_with_delim("avl_tree.txt");
    //t.write_to_file("avl_tree2.txt");
    std::cout << std::endl;

    avl_tree<int> t2;
    //t2.read_to_file("avl_tree2.txt");
    std::cout << std::endl;
   //t2.print();
   //time_test(10000000);

    fix_priority_queue<int> p1(5);
    p1.push(5);
    p1.push(12);
    p1.push(15);
    p1.push(20);
    p1.push(1);
    p1.push(13);
    p1.push(17);
    p1.pop();

    //time_test_queue(10000);
    //top_words_in_book("D:\\User\\desktop\\Lesson4\\GameofThrones.txt");
    top_names_in_book("D:\\User\\desktop\\Lesson4\\GameofThrones.txt");
    //the_largest_pair_of_anagrams("C:\\Users\\user\\Documents\\Qt\\GameofThrones.txt");

}

/*
Time test for 10000000 insertions
Set: 5.027 sec.
AVL Tree: 6.914 sec.
*/

/*
Time test for 10000 insertions
Priority_queue<int, vector>: 0.561 sec.
Priotity_queue<int, deque>: 17.815 sec.
*/

