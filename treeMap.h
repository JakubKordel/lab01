#include <iostream>


template<typename KeyType, typename ValueType>
class TreeMap
{
  private:
      struct Node{
    Node* up;
    Node* left;
    Node* right;
    KeyType key;
    ValueType val;
    };
    Node *root = NULL;


  public:
    using key_type = KeyType;
    using mapped_type = ValueType;
    using value_type = std::pair<const key_type, mapped_type>;

    void splayRelease(Node* root){
    if(root){
            splayRelease(root->left);
            splayRelease(root->right);
            delete root;
        }
    }

    TreeMap() = default;    // konstruktor trywialny
    ~TreeMap(){
        splayRelease(root);

    }   // destruktor trywialny

    /*!
     * true jezeli slownik jest pusty
     */
    bool isEmpty() const
    {
        return !root;
    }

    /*!
     * dodaje wpis do slownika
     */
    Node* find(key_type& key)
    {
        Node* help = this->root;
    while(help){
        if(key == help->key){
            return help;

        }else if(key > help->key){
            help = help->right;
        }else if(key < help->key){
            help = help->left;
        }
    }
    return NULL;
    }


    void insert(const key_type& key, const mapped_type &value)
    {
        throw std::runtime_error("TODO: insert");
    }

    /*!
     * dodaje wpis do slownika przez podanie pary klucz-wartosc
     */
    void insert(const value_type &key_value)
    {

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
    const mapped_type& value(const key_type& key) const
    {
        Node* help;
        if(contains(key)){
            help=find(key);
            return help;
        }
        else{
            return NULL;
        }
    }

    /*!
     * zwraca informacje, czy istnieje w slowniku podany klucz
     */
    bool contains(const key_type& key) const {
        Node* help;
        help = find(key);
        if(help){
            splay(help);
            return true;
        }
        else{
            return false;
        }


    }

    void rot_R(Node * & root, Node * A){
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

    void rot_L(Node * & root, Node* A){
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
        KeyType k = help->key;

        x = this->root;
        if(x)
        {
            do
            {
                if(x->key == k){
                    break;
                }
                y = x;
                x = k < x->key ? x->left: x->right;
            } while(x);

            if(!x){
                x = y;
            }


            while(true)
            {
                if(!x->up) {
                        break;
                }

                if(!x->up->up)
                {
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

    /*!
     * zwraca liczbe wpisow w slowniku
     */
    size_t size() const {
        throw std::runtime_error("TODO: size");
    }
private:

};
