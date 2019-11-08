//
// Created by arsze on 07.11.2019.
//

#ifndef TREE_SPLAY_H
#define TREE_SPLAY_H
#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

string cr,cl,cp;

class Node {
public:
        Node *up;
        Node *right;
        Node *left;
        int key;



    void insertSplay(Node * & root, int k){
           Node * newNode, * it;

           newNode = new Node;           // Tworzymy dynamicznie nowy węzeł

           newNode->left = NULL;
           newNode->right = NULL;// Zerujemy wskazania synów
           newNode->key = k;                // Wstawiamy klucz

           it = root;                  // Wyszukujemy miejsce dla w, rozpoczynając od korzenia

           if(!it)                     // Drzewo puste?
               root = newNode;                // Jeśli tak, to w staje się korzeniem
           else
               while(true)              // Pętla nieskończona
                   if(k < it->key)         // W zależności od klucza idziemy do lewego lub
                   {                      // prawego syna, o ile takowy istnieje
                       if(!it->left)         // Jeśli lewego syna nie ma,
                       {
                           it->left = newNode;       // to węzeł w staje się lewym synem
                           break;             // Przerywamy pętlę while
                       }
                       else it = it->left;
                   }
                   else
                   {
                       if(!it->right)        // Jeśli prawego syna nie ma,
                       {
                           it->right = newNode;      // to węzeł w staje się prawym synem
                           break;             // Przerywamy pętlę while
                       }
                       else it = it->right;
                   }

           newNode->up  = it;                // Ojcem węzła w jest zawsze węzeł wskazywany przez p

       }

    void splayRelease(Node * v)
    {
        if(v)
        {
            splayRelease(v->left);   // usuwamy lewe poddrzewo
            splayRelease(v->right);  // usuwamy prawe poddrzewo
            delete v;              // usuwamy sam węzeł
        }
    }

    void rot_L(Node * & root, Node * A)
    {
        Node * B = A->right, * p = A->up;

        if(B)
        {
            A->right = B->left;
            if(A->right) A->right->up = A;

            B->left = A;
            B->up = p;
            A->up = B;

            if(p)
            {
                if(p->left == A) p->left = B; else p->right = B;
            }
            else root = B;
        }
    }

// Rotacja w prawo
//----------------
    void rot_R(Node * & root, Node * A)
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

    void splay(Node * & root, int k)
    {
        Node * x, *y;

        x = root;                 // Poszukujemy węzła o kluczu k, poczynając od korzenia
        if(x)
        {
            do
            {
                if(x->key == k) break;
                y = x;                // Zapamiętujemy adres węzła
                x = k < x->key ? x->left: x->right;
            } while(x);

            if(!x) x = y;           // Jeśli w drzewie nie ma takiego węzła, to za x
            // bierzemy bezpośredni następnik lub poprzednik
            while(true)             // W pętli węzeł x przesuwamy do korzenia
            {
                if(!x->up) break;     // x jest korzeniem, kończymy

                if(!x->up->up)
                {                     // Ojcem x jest korzeń. Wykonujemy ZIG
                    if(x->up->left == x) rot_R(root,x->up);
                    else                 rot_L(root,x->up);
                    break;              // Kończymy
                }

                if((x->up->up->left == x->up) && (x->up->left == x))
                {                     // prawy ZIG-ZIG
                    rot_R(root,x->up->up);
                    rot_R(root,x->up);
                    continue;
                }

                if((x->up->up->right == x->up) && (x->up->right == x))
                {                    // lewy ZIG-ZIG
                    rot_L(root,x->up->up);
                    rot_L(root,x->up);
                    continue;
                }

                if(x->up->right == x)
                {                    // lewy ZIG, prawy ZAG
                    rot_L(root,x->up);
                    rot_R(root,x->up);
                }
                else
                {                    // prawy ZIG, lewy ZAG
                    rot_R(root,x->up);
                    rot_L(root,x->up);
                }
            }
        }
    }

    void printBT(string sp, string sn, Node * v)
    {
        string s;

        if(v)
        {
            s = sp;
            if(sn == cr) s [ s.length() - 2 ] = ' ';
            printBT(s + cp, cr, v->right);

            s = s.substr(0,sp.length()-2);
            cout << s << sn << v->key << endl;

            s = sp;
            if(sn == cl) s [ s.length() - 2 ] = ' ';
            printBT(s + cp, cl, v->left);
        }
    }

};

#endif //TREE_SPLAY_H
