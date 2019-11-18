#include <iostream>
#include <chrono>
#include <utility>

/*!
 *  Narzedzie do zliczania czasu
 *
 *  Sposob uzycia:
 *
 *  {
 *    Benchmark<std::chrono::nanoseconds> b;
 *    // kod do zbadania
 *    size_t elapsed = b.elapsed();
 *  }
 *
 *  lub
 *
 *  {
 *    Benchmark<std::chrono::milliseconds> b(true);
 *    // kod do zbadania
 *  } // obiekt wypisze wartosc czasu w podanych jednostkach na stderr
 */
template<typename D = std::chrono::microseconds>
class Benchmark {
public:

    Benchmark(bool printOnExit = false) : m_print(printOnExit) {
        start = std::chrono::high_resolution_clock::now();
    }
    typename D::rep elapsed() const {
        auto end = std::chrono::high_resolution_clock::now();
        auto result = std::chrono::duration_cast<D>(end-start);
        return result.count();
    }
    ~Benchmark() {
        auto result = elapsed();
        if (m_print)
        {
            std::cerr << "Czas: " << result << "\n";
        }
    }
private:
    std::chrono::high_resolution_clock::time_point start;
    bool m_print = true;
};




/*
 * Slownik
 *
 */

template<typename KeyType, typename ValueType>
class TreeMap{


public:
    using key_type = KeyType;
    using mapped_type = ValueType;
    using value_type = std::pair< key_type, mapped_type>;

    TreeMap() = default;    // konstruktor trywialny
    ~TreeMap() = default;   // destruktor trywialny

private:
    struct Node {
        Node *up;
        Node *right;
        Node *left;
        value_type v;
    };
    Node * root= nullptr;

public:
    /*!
     * true jezeli slownik jest pusty
     */
    bool isEmpty() const{
        if(!root){
            return true;
        }
        else{
            return false;
        }
    }

    /*!
     * dodaje wpis do slownika
     */
    void insert(const key_type& key, const mapped_type &value){
        Node * newNode, * it;
        key_type k = key;
        newNode = new Node;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode-> v.first = k;
        newNode-> v.second = value;
        it = root;
        if(!it)
            root = newNode;
        else
            while(true)
                if(key < it->v.first){
                    if(!it->left){
                        it->left = newNode;
                        break;
                    }
                    else it = it->left;
                }
                else{
                    if(!it->right){
                        it->right = newNode;
                        break;
                    }
                    else it = it->right;
                }
        newNode->up  = it;
    }

    /*!
     * dodaje wpis do slownika przez podanie pary klucz-wartosc
     */
    void insert(const value_type &key_value){
        Node * newNode, * it;
        newNode = new Node;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->v = key_value;
        it = root;
        if(!it)
            root = newNode;
        else
            while(true)
                if(newNode ->v.first < it->v.first){
                    if(!it->left){
                        it->left = newNode;
                        break;
                    }
                    else it = it->left;
                }
                else{
                    if(!it->right){
                        it->right = newNode;
                        break;
                    }
                    else it = it->right;
                }
        newNode->up  = it;
    }

    /*!
     * zwraca referencje na wartosc dla podanego klucza
     *
     * jezeli elementu nie ma w slowniku, dodaje go
     */
    mapped_type& operator[](const key_type& key)
    {
        throw std::runtime_error("TODO: operator[]");
    }

    /*!
  * zwraca wartosc dla podanego klucza
  */

    Node* find(const key_type& key) const
    {
        Node* help = root;
        while(help){
            if(key == help->v.first){
                return help;

            }
            else if(key > help->v.first){
                help = help->right;
            }
            else if(key < help->v.first){
                help = help->left;
            }
        }
        return nullptr;
    }



    /*!
     * zwraca informacje, czy istnieje w slowniku podany klucz
     */
    bool contains(const key_type& key)
    {
        Node* help;
        help = find(key);
        if(help!=nullptr){
            splay(help);
            return true;
        }
        else{
            return false;
        }
    }

    mapped_type& value(const key_type& key)
    {
        Node* help;
        if(contains(key)){
            help=find(key);
            return help->v.second;
        }
        throw std::runtime_error("There's no member with that key");
    }

    /*!
     * zwraca liczbe wpisow w slowniku
     */
    size_t size() const {
        return getfullCount(root);
    }

private:
    void rot_R( Node * & root, Node * A)
    {
        Node * B = A->left;
        Node* p = A->up;

        if(B)
        {
            A->left = B->right;
            if(A->left) {
                A->left->up = A;
            }

            B->right = A;
            B->up = p;
            A->up = B;

            if(p)
            {
                if(p->left == A)
                {
                    p->left = B;
                }
                else
                {
                    p->right = B;
                }
            }
            else
            {
                root = B;
            }
        }
    }

    void rot_L(Node * & root, Node* A)
    {
        Node * B = A->right;
        Node * p = A->up;
        if(B)
        {
            A->right = B->left;
            if(A->right){
                A->right->up = A;
            }
            B->left = A;
            B->up = p;
            A->up = B;

            if(p)
            {
                if(p->left == A) {
                    p->left = B;
                }
                else {
                    p->right = B;
                }
            }
            else{
                root = B;
            }
        }

    }

    void splay(Node * & help)
    {
        Node * x, *y;
        KeyType k = help->v.first;

        x = root;
        if(x){
            do{
                if(x->v.first == k){
                    break;
                }
                y = x;
                x = k < x->v.first ? x->left: x->right;
            } while(x);

            if(!x){
                x = y;
            }


            while(true){
                if(!x->up) {
                    break;
                }

                if(!x->up->up){
                    if(x->up->left == x) {
                        rot_R(root,x->up);
                    }
                    else{
                        rot_L(root,x->up);
                    }
                    break;
                }

                if((x->up->up->left == x->up) && (x->up->left == x)){

                    rot_R(root,x->up->up);
                    rot_R(root,x->up);
                    continue;
                }

                if((x->up->up->right == x->up) && (x->up->right == x)){

                    rot_L(root,x->up->up);
                    rot_L(root,x->up);
                    continue;
                }

                if(x->up->right == x){

                    rot_L(root,x->up);
                    rot_R(root,x->up);
                }
                else{

                    rot_R(root,x->up);
                    rot_L(root,x->up);
                }
            }
        }
    }

    size_t getfullCount(Node* r) const {
        if (r == nullptr)
            return 0;
        size_t res = 1;
        res += (getfullCount(r->left) +
                getfullCount(r->right));
        return res;
    }
};

#include "tests.h"

int main()
{
    unit_test();

    return 0;
}
