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
    using value_type = std::pair< const key_type, mapped_type>;

    TreeMap() = default;    // konstruktor trywialny
    ~TreeMap() { deleteTree(root); }   // destruktor trywialny

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
        return !root;
    }

    /*!
     * dodaje wpis do slownika
     */
    void insert(const key_type& key, const mapped_type &value){
        insert(value_type(key, value));
    }

    /*!
     * dodaje wpis do slownika przez podanie pary klucz-wartosc
     */
    void insert(const value_type &key_value){

        if(contains( key_value.first)){
            Node* help;
            help = find(key_value.first);
            help->v.second = key_value.second;
            return;
        }
        Node * newNode, * it;

        newNode = new Node{nullptr, nullptr, nullptr, key_value};

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
        if(contains(key)) {
            Node * help = find(key);
            splay(help);
            return help ->v.second;
        }
        else{
            mapped_type empty;
            insert(key, empty);
            return value(key);
        }
    }

    /*!
     * zwraca wartosc dla podanego klucza
     */
    mapped_type& value(const key_type& key)
    {
        if(contains(key)){
            Node* help;
            help=find(key);
            splay( help );
            return help->v.second;
        }
        throw std::runtime_error("There's no member with that key");
    }

    /*!
     * zwraca informacje, czy istnieje w slowniku podany klucz
     */
    bool contains(const key_type& key) const
    {
        Node* help = find(key);
        return help;
    }

    /*!
     * zwraca liczbe wpisow w slowniku
     */
    size_t size() const {
        return getfullCount(root);
    }


private:
    void rot_R( Node * A)
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

    void rot_L( Node* A)
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
                        rot_R(x->up);
                    }
                    else{
                        rot_L(x->up);
                    }
                    break;
                }

                if((x->up->up->left == x->up) && (x->up->left == x)){

                    rot_R(x->up->up);
                    rot_R(x->up);
                    continue;
                }

                if((x->up->up->right == x->up) && (x->up->right == x)){

                    rot_L(x->up->up);
                    rot_L(x->up);
                    continue;
                }

                if(x->up->right == x){

                    rot_L(x->up);
                    rot_R(x->up);
                }
                else{

                    rot_R(x->up);
                    rot_L(x->up);
                }
            }
        }
    }

    Node* find(const key_type& key) const {
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

    size_t getfullCount(Node* r) const {
        if (r == nullptr)
            return 0;
        size_t res = 1;
        res += (getfullCount(r->left) +
                getfullCount(r->right));
        return res;
    }

    void deleteTree(Node * node){
        if ( !node ) return;
        deleteTree(node ->left);
        deleteTree(node ->right);
        delete node;
    }

};

#include "tests.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main()
{
    unit_test();
    std::vector<std::string> data;
    std::ifstream file;
    std::string word;
    TreeMap<std::string, std::string> dict;
    file.open("text");
    while (file.good()){
        file >> word;
        data.push_back(word);
    }
    file.close();
    Benchmark<std::chrono::nanoseconds> b;
    for ( size_t i = 0 ; i < data.size() ; ++i ){
        dict.insert(data[i], data[i] + " :Data");
    }
    size_t elapsed = b.elapsed();
    std::cout << elapsed << std::endl;

    Benchmark<std::chrono::nanoseconds> b2;
    for ( size_t i = 0 ; i < data.size() ; ++i ){
        dict.value(data[i]);
    }
    elapsed = b2.elapsed();
    std::cout << elapsed << std::endl;

    std::map<std::string, std::string> map;
    Benchmark<std::chrono::nanoseconds> b3;
    for ( size_t i = 0 ; i < data.size() ; ++i ){
        map.insert(std::pair<std::string, std::string> (data[i], data[i] + " :Data" ));
    }
    elapsed = b3.elapsed();
    std::cout << elapsed << std::endl;

    Benchmark<std::chrono::nanoseconds> b4;
    for ( size_t i = 0 ; i < data.size() ; ++i ){
        map.find(data[i]);
    }
    elapsed = b4.elapsed();
    std::cout << elapsed << std::endl;

    return 0;
}
