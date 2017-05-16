#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <utility>
#include <algorithm>
#include <fstream>
#include <string>

template<typename value_type, class comp = std::less<value_type>>
class avl_tree{

    comp Compare;
     class node{
     public:
        typedef std::pair<value_type, size_t> pair_type;

        pair_type key;
        unsigned char height;
        node* left;
        node* right;
        node* parent;

        node(pair_type k, node * l = nullptr, node * r = nullptr, node * p = nullptr):
            key(k), left(l), right(r), height(1), parent(p) {}

        // _NLL constructor of false leaf with uninit key
        node(node * p):
            key(pair_type()),
            left(0),
            right(0),
            parent(p) {}
    };
private:

     void destroy_tree(node * r){
         if (r != _NLL)
         {
             destroy_tree(r->left);
             destroy_tree(r->right);
             delete r;
         }
     }

public:

     node * root;
     node * _NLL;
     size_t cnt_left_rotate;
     size_t cnt_right_rotate;

     avl_tree(){
         _NLL = new node(nullptr);
         _NLL->left = _NLL;
         _NLL->right = _NLL;
         _NLL->parent = _NLL;
         _NLL->height = 0;
         root = _NLL;
         cnt_left_rotate = 0;
         cnt_right_rotate = 0;
     }

    avl_tree(const avl_tree<value_type> & t){
        root = _NLL;
        auto it = t.cbegin();
        while(it != t.cend()){
            this->insert(*it);
            ++it;
        }
     }

private:

    unsigned char height(node * p)
    {
        if (p != _NLL)
            return p->height;
        else
            return 0;
    }

    // calculates the balance factor of the node
    int bfactor(node * p)
    {
        return height(p->right) - height(p->left);
    }

    // restores the correct value of the field height of the node
    void fixheight(node * p)
    {
        unsigned char hl = height(p->left);
        unsigned char hr = height(p->right);
        if (hr < hl)
            p->height = hl + 1;
        else
            p->height = hr + 1;
    }

    // updates _NLL with new root
    void set_root(node * r){
        _NLL->left = r;
        _NLL->right = r;
        r->parent = _NLL;
        root = r;
    }

    // reslizes a right rotate
    node* rotateright(node * n){
        ++cnt_right_rotate;
        if (n == _NLL)
            return _NLL;
        node *p = n->left;

        p->parent = n->parent; /* при этом, возможно, p становится корнем дерева */
        if(p->parent == _NLL)
            set_root(p);

        if (n->parent != _NLL) {
            if (n->parent->left == n)
                n->parent->left = p;
            else
                n->parent->right = p;
            }

        n->left = p->right;
        if (p->right != _NLL)
            p->right->parent = n;

        n->parent = p;
        p->right = n;
        fixheight(n);
        fixheight(p);
        return p;
    }

    // relizes a left rotate
    node* rotateleft(node * n){
        ++cnt_left_rotate;
        if (n == _NLL)
            return _NLL;
        node *p = n->right;

        p->parent = n->parent;
        if(p->parent == _NLL)
            set_root(p);

        if (n->parent != _NLL) {
            if (n->parent->left==n)
                n->parent->left = p;
            else
                n->parent->right = p;
        }

        n->right = p->left;
        if (p->left != _NLL)
            p->left->parent = n;

        n->parent = p;
        p->left = n;
        fixheight(n);
        fixheight(p);
        return p;
    }

    // balances of the node
    node* balance(node * p)
    {
        fixheight(p);
        if(bfactor(p) == 2)
        {
            if(bfactor(p->right) < 0)
                p->right = rotateright(p->right);
            return rotateleft(p);
        }
        if(bfactor(p) == -2)
        {
            if(bfactor(p->left) > 0)
                p->left = rotateleft(p->left);
            return rotateright(p);
        }
        return p;
    }

    // push new elem in tree
    node* push(node * p, node * f, value_type val) {
        cnt_left_rotate = 0;
        cnt_right_rotate = 0;

        if(root == _NLL) {
            root = new node({val, 1}, _NLL, _NLL, _NLL);
            _NLL->left = root;
            _NLL->right = root;
            return balance(root);
        }

        if(p == _NLL)
            return new node({val,1}, _NLL, _NLL, f);

        if(Compare(val,p->key.first))
            p->left = push(p->left, p, val);
        else if (!Compare(p->key.first, val))
            ++p->key.second;
        else
            p->right = push(p->right, p, val);
        return balance(p);
       }

    // returns min node in tree from r, if root is _NLL returns _NLL
    node* min_node(node * r) const{
        return (r->left != _NLL)?min_node(r->left):r;
    }

    // removes the node with min key from the tree
    node* remove_min(node * p)
    {
        if(p->left == _NLL)
            return p->right;
        p->left = remove_min(p->left);
        return balance(p);
    }

    //delete node of k in tree from p
    node* remove_node(node * p, node * f, value_type k)
    {
        if(p == _NLL)
            return _NLL;
        if(Compare(k, p->key.first)){
            p->left = remove_node(p->left, p, k);
            if (p->left != _NLL)
                p->left->parent = p;
        }
        else
            if(Compare(p->key.first, k)){
                 p->right = remove_node(p->right, p, k);
                 if (p->right != _NLL)
                     p->right->parent = p;
            }

            else //  k == p->key
            {
                node * q = p->left;
                node * r = p->right;

                if(r == _NLL){
                    if(p == root)
                        set_root(q);
                    delete p;
                    return q;
                }
                node * min = min_node(r);
                node * rm = remove_min(r);
                min->right = rm;
                rm->parent = min->right;
                min->left = q;
                if(p == root)
                    set_root(min);
                delete p;
                return balance(min);
            }
        return balance(p);
    }

    // returns node of val in tree from r, if not found returns _NLL
    node * find_node(node * r,const value_type val) const{
        if (root == _NLL)
            return _NLL;

        if (r == _NLL)
            r = root;

        if (Compare(val, r->key.first)){
            if (r->left != _NLL)
                return find_node(r->left, val);
            else
                return _NLL;
        }
        else if(!Compare(r->key.first, val))
            return r;
        else
            if (r->right != _NLL)
                return find_node(r->right, val);
            else
                return _NLL;
    }

    //returns first elem >= val, if root is _NLL returns _NLL
    node * first_lower_bound(const value_type val) const{
        if (root == _NLL)
            return _NLL;

        node * res = root;
        while (Compare(res->key.first, val) && (res->right != _NLL))
            res = res->right;

        if (Compare(res->key.first, val))
            return _NLL;
        return res;
    }

    //returns first elem <= val, if root is _NLL returns _NLL
    node * first_upper_bound(const value_type val) const{
        if (root == _NLL)
            return _NLL;

        node * res = root;
        while (Compare(val, res->key.first) && (res->left != _NLL))
            res = res->left;

        if (Compare(val, res->key.first))
            return _NLL;

        return res;
    }

    node * next(node * r) const {
        if(r->right != _NLL){
              r = r->right;
              while(r->left != _NLL)
                  r =r->left;
              return r;
          }
        else
            if(r->parent != _NLL && r->parent->left == r)
                 return r->parent;
            else{
                while ((r->parent->right == r) && (r->parent != _NLL))
                    r = r->parent;
                if (r->parent != _NLL)
                    return r->parent;
            }
        return _NLL;
    }

    node * prev(node * r) const {
        if(r->left != _NLL){
              r = r->left;
              while(r->right != _NLL)
                  r = r->right;
              return r;
          }
          else
            if(r->parent != _NLL && r->parent->right == r)
               return r->parent;
            else{
                while ((r->parent->left == r) && (r->parent != _NLL))
                    r = r->parent;
                if (r->parent != _NLL)
                    return r->parent;
            }
        return _NLL;
    }

    void print_tree(node * p, int level){
        if(p != _NLL)
        {
            print_tree(p->left,level + 1);
            for(int i = 0; i< level; ++i)
                std::cout << "   ";
            std::cout << p->key.first << std::endl;
            print_tree(p->right,level + 1);
        }
    }

public:

    class iterator
         {
    public:
        typedef iterator self_type;
        typedef value_type& reference;
        typedef node* pointer;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef size_t difference_type;

        iterator(node * ptr,avl_tree<value_type> * f) : ptr_(ptr), father(f), cnt(ptr->key.second) {}
        self_type operator++() {
            if (cnt > 1){
                --cnt;
                return *this;
            }
            self_type i = *this;
            ptr_ = father->next(ptr_);
            cnt = ptr_->key.second;
            return i;
        }

        self_type operator++(int junk) {
            if (cnt > 1){
                --cnt;
                return *this;
            }
            ptr_=father->next(ptr_);
            cnt = ptr_->key.second;
            return *this;
        }

        self_type operator--() {
            if(ptr_->key.second > 1){
                --cnt;
                return *this;
            }
            self_type i = *this;
            ptr_=father->prev(ptr_);
            cnt = 1;
            return i;
        }

        self_type operator--(int junk) {
            if(ptr_->key.second > 1 && cnt !=1){
                --cnt;
                return *this;
            }
            ptr_=father->prev(ptr_);
            cnt = 1;
            return *this;
        }

        const value_type& operator*() { return ptr_->key.first; }
        self_type operator+(difference_type c){
            self_type it = *this;
            for(difference_type i = 0; i < c; ++i) ++it; return it;
        }
        bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
        bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
        size_t count() { return ptr_->key.second; }

    private:
        avl_tree<value_type> * father;
        node *  ptr_;
        size_t  cnt;
   };

    class const_iterator: public iterator {
    public:
        const_iterator(node * ptr,avl_tree<value_type> * f) : iterator(ptr,f){}
        const value_type & operator*() { return iterator::ptr_->key ; }
    };

    iterator begin(){
        auto r = root;
        while(r->left != _NLL)
            r = r->left;
        return iterator(r,this);
    }

    iterator end(){
        auto r = root;
        while(r->right != _NLL)
            r = r->right;
        return iterator(r,this);
    }

    const_iterator cbegin() const{
        auto r = root;
        while(r->left != _NLL)
            r = r->left;
        return const_iterator(r,this);
    }

    const_iterator cend() const{
        auto r = root;
        while(r->right != _NLL)
            r = r->right;
        return const_iterator(r,this);
    }

    iterator upper_bound(const value_type & v){
        return iterator(first_upper_bound(v), this);
    }

    iterator lower_bound(const value_type & v){
         return iterator(first_lower_bound(v), this);
    }

    void insert(const value_type & v){
        push(root, _NLL, v);
    }

    iterator find(const value_type & v) {
        return iterator(find_node(_NLL, v),this);
    }

    size_t erase(const value_type & v){
        node * r = find_node(root, v);
        if(r == _NLL)
            return 0;
        size_t c = r->key.second;
        remove_node(root, _NLL, v);
        return c;
    }

    bool empty(){
        return begin() == end();
    }

    bool empty() const {
        return cbegin() == cend();
    }

    void clear(){
        while(!empty()){
            iterator it = begin();
            erase(*it);
        }
        erase(*begin());
    }

    ~avl_tree(){
        destroy_tree(root);
        delete _NLL;
    }

    size_t count(const value_type & v)  {
        iterator it = find(v);
        size_t count = 0;
        while (it != end() && *it == v){
            ++count;
            ++it;
       }
        return count;
    }

  /*  value_type& operator*(){
        this-
    }*/

    //Prints the contents of tree to the screen "sideways"
    void print(int level = 0)
    {
        print_tree(this->root, level);
    }

    void write_to_file(std::string fname){
        std::ofstream os(fname);
        iterator it = this->begin();
        while (it != this->end()){
            os << *it << " ";
            ++it;
        }
        os << *it;
    }

    void write_to_file_with_delim(std::string fname, std::string delim = ", "){
        std::ofstream os(fname);
        iterator it = this->begin();
        while (it != this->end()){
            os << *it << delim;
            ++it;
        }
        os << *it;
    }

    void read_to_file(std::string fname){
        std::ifstream is(fname);
        while (is) {
            value_type t;
            is >> t;
            this->insert(t);
        }
    }
};

// time test;
void time_test(int cnt);

#endif // AVL_TREE_H

