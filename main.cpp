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
    t.insert(40);
    t.insert(5);
    t.insert(1);
    t.insert(12);
    t.insert(-9);
    t.insert(13);
    t.insert(0);
    t.insert(32);
    assert(t.count(32) == 2);
    assert(!t.empty());
    assert(*t.find(15) == 15);
     t.print();
    t.write_to_file_with_delim("avl_tree.txt");
    t.write_to_file("avl_tree2.txt");
    std::cout << std::endl;

    avl_tree<int> t2;
    t2.read_to_file("avl_tree2.txt");
    std::cout << std::endl;
   // t2.print();
    //time_test(10000000);

    priority_queue<int> p;
    p.push(5);
    p.push(10);
    p.push(3);
    p.push(1);
    fix_priority_queue<int> p1(5);
    p1.push(5);
    p1.push(12);
    p1.push(15);
    p1.push(20);
    p1.push(1);
    p1.push(13);
    p1.pop();

   // top_words_in_book("got.txt");

}

/*
Time test for 10000000 insertions
Set: 5.027 sec.
AVL Tree: 6.914 sec.
*/

