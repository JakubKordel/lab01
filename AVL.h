#ifndef AVL_AVL_H
#define AVL_AVL_H

template <typename Data>
class AVL{
    struct Node{
    public:
        Node * parent;
        Node * left;
        Node * right;
        Data data;
        int bf;
        int key;
    };
public:

    Node * root;
    AVL(){
        root = nullptr;
    }

    ~AVL(){
        deleteTree(root);
    }

    void deleteTree(Node * n){
        if(n){
            deleteTree(n->left);
            deleteTree(n->right);
            delete n;
        }
    }

    void add(int k, Data data){
        insert(k, data);
    }

    Data getData(int k){
        Node * n = find(root, k);
        return n ->data;
    }

    void del(int k){
        Node * n = find(root, k);
        remove(n);
    }

    Node * remove(Node * x){
        Node  *t,*y,*z;
        bool nest;

        if(x->left && x->right){
            y    = remove(prev(x));
            nest = false;
        }
        else{
            if(x->left)
            {
                y = x->left; x->left = nullptr;
            }
            else
            {
                y = x->right; x->right = nullptr;
            }
            x->bf = 0;
            nest  = true;
        }

        if(y){
            y->parent    = x->parent;
            y->left  = x->left;  if(y->left)  y->left->parent  = y;
            y->right = x->right; if(y->right)  y->right->parent = y;
            y->bf    = x->bf;
        }

        if(x->parent){
            if(x->parent->left == x) x->parent->left = y; else x->parent->right = y;
        }
        else root = y;

        if(nest){
            z = y;
            y = x->parent;
            while(y){
                if(!y->bf){
                    if(y->left == z)  y->bf = -1; else y->bf = 1;
                    break;
                }
                else{
                    if(((y->bf == 1) && (y->left == z)) || ((y->bf == -1) && (y->right == z))){
                        y->bf = 0;
                        z = y; y = y->parent;
                    }
                    else{
                        if(y->left == z)  t = y->right; else t = y->left;
                        if(!t->bf){
                            if(y->bf == 1)
                                LL(y);
                            else
                                RR(y);
                            break;
                        }
                        else if(y->bf == t->bf){
                            if(y->bf == 1)
                                LL(y);
                            else
                                RR(y);
                            z = t; y = t->parent;
                        }
                        else{
                            if(y->bf == 1)
                                LR(y);
                            else
                                RL(y);
                            z = y->parent; y = z->parent;
                        }
                    }
                }
            }
        }
        return x;
    }

    Node * find(Node * p, int k){
        while(p && p->key != k)
            p = (k < p->key) ? p->left: p->right;
        return p;
    }

    Node * prev(Node * p){
        Node * r;

        if(p){
            if(p->left){
                p = p->left;
                while(p->right) p = p->right;
            }
            else
                do{
                    r = p;
                    p = p->parent;
                } while(p && p->right != r);
        }
        return p;
    }

private:

    void insert( int k, Data d ){
        Node * w = new Node;
        w ->left = nullptr;
        w ->right = nullptr;
        w ->key = k;
        w->data = d;
        bool t;
        Node * r;
        w ->bf = 0;
        Node * p = root;
        if (!p) {
            root = w;
            return;
        }
        while ( true ){
            if ( k < p ->key ){
                if ( p ->left ){
                    p = p ->left;
                } else {
                    p ->left = w;
                    break;
                }
            } else {
                if ( p ->right )
                    p = p ->right;
                else {
                    p->right = w;
                    break;
                }
            }
        }
        w ->parent = p;
        if(p->bf) p->bf = 0;
        else{
            if(p->left == w)
                p->bf = 1;
            else
                p->bf = -1;

            r = p->parent;
            t = false;
            while(r)
            {
                if(r->bf)
                {
                    t = true;
                    break;
                };
                if(r->left == p) r->bf =  1;
                else             r->bf = -1;

                p = r;
                r = r->parent;
            }

            if(t){
                if(r->bf == 1){
                    if(r->right == p) r->bf = 0;
                    else if(p->bf == -1)
                        LR(r);
                    else
                        LL(r);
                }
                else{
                    if(r->left == p) r->bf = 0;
                    else if(p->bf == 1)
                        RL(r);
                    else
                        RR(r);
                }
            }
        }
    }

    void RR ( Node * node ) {
        Node * p = node ->parent;
        Node * newMain = node ->right;
        node ->right = newMain ->left;
        if ( node ->right )
            node ->right ->parent = node;
            newMain ->left = node;
            newMain ->parent = p;
            node ->parent = newMain;
            if (p){
                if (p ->left == node )
                    p ->left = newMain;
                else
                    p ->right = newMain;
            } else
                root = newMain;
            if (newMain ->bf == -1 ){
                node ->bf = 0;
                newMain ->bf = 0;
            } else {
                node ->bf = -1;
                newMain ->bf = 1;
            }
    };

    void LL( Node * node){
        Node * p = node ->parent;
        Node * newMain = node ->left;
        node ->left = newMain ->right;
        if ( node ->left )
            node ->left ->parent = node;
        newMain ->right = node;
        newMain ->parent = p;
        node ->parent = newMain;
        if (p){
            if (p ->left == node )
                p ->left = newMain;
            else
                p ->right = newMain;
        } else
            root = newMain;
        if (newMain ->bf == -1 ){
            node ->bf = 0;
            newMain ->bf = 0;
        } else {
            node ->bf = 1;
            newMain ->bf = -1;
        }
    }

    void RL ( Node * a ){
        Node * b = a ->right;
        Node * c = b ->left;
        Node * p = a ->parent;
        b ->left = c ->right;
        if (b -> left)
            b -> left -> parent = b;
        a ->right = c ->left;
        if ( a -> right )
            c ->right ->parent = a;
        c ->left = a;
        c ->right = b;
        a ->parent = c;
        b ->parent = c;
        c ->parent = p;
        if (p){
            if (p ->left == a)
                p ->left = c;
            else
                p ->right = c;
        } else
            root = c;
        if (c ->bf == -1 )
            a ->bf = 1;
        else{
            a ->bf = 0;
            if (c ->bf == 1 )
                b ->bf = -1;
            else b ->bf = 0;
        }
        c ->bf = 0;
    }

    void LR ( Node * a ){
        Node * b = a ->left;
        Node * c = b ->right;
        Node * p = a ->parent;
        b ->right = c ->left;
        if (b -> right)
            b -> right -> parent = b;
        a ->left = c ->right;
        if ( a -> left )
            c ->left ->parent = a;
        c ->right = a;
        c ->left = b;
        a ->parent = c;
        b ->parent = c;
        c ->parent = p;
        if (p){
            if (p ->left == a)
                p ->left = c;
            else
                p ->right = c;
        } else
            root = c;
        if (c ->bf == -1 )
            a ->bf = 1;
        else{
            a ->bf = 0;
            if (c ->bf == 1 )
                b ->bf = -1;
            else b ->bf = 0;
        }
        c ->bf = 0;
    }
};

#endif //AVL_AVL_H
