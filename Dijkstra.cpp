#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

struct slistEl{
    slistEl * next;
    int v, w;
};

int * findPath( slistEl **graf, int n, int start, int *p ){
    int i, j, u, *d;
    bool *QS;
    slistEl *pw;

    d = new int [ n ];
    QS = new bool [ n ];

    for(i = 0; i < n; i++){
        d [ i ] = INT_MAX;
        p [ i ] = -1;
        QS [ i ] = false;
        graf [ i ] = NULL;
    }

    d [ start ] = 0;

    for(i = 0; i < n; i++) {

        for(j = 0; QS [ j ]; j++);
        for(u = j++; j < n; j++)
            if(!QS [ j ] && (d [ j ] < d [ u ]))
                u = j;
        QS [ u ] = true;

        for(pw = graf [ u ]; pw; pw = pw->next)
            if(!QS [ pw->v ] && (d [ pw->v ] > d [ u ] + pw->w))
            {
                d [ pw->v ] = d [ u ] + pw->w;
                p [ pw->v ] = u;
            }
    }
    delete [ ] d;
    delete [ ] QS;

    return p;
}

int main()
{
    int * p;
    slistEl *pw;
    slistEl ** graf;
    graf = new slistEl * [ 36 ];
    for( int i = 0; i < 36; i++){
        graf [ i ] = nullptr;
    }

    p = new int [ 36 ];
    int tab_val [6] [6] = {
        {0,2,2,3,3,3},
        {1,1,1,1,3,3},
        {9,9,4,1,5,6},
        {9,9,1,1,3,2},
        {7,7,1,4,2,2},
        {8,8,1,1,1,0}
    };
    int tab_num [6] [6];
    int k = 0;

    for(int i =0; i < 6; ++i){
        for(int j = 0; j<6; ++j){
            //cin >> tab_val [i][j];
            tab_num[i][j] = k;
            ++k;
        }
    }


    for (int i = 0; i <6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if(i != 5) {
                pw = new slistEl;
                pw->v =  tab_num[i + 1][j];                  // Wierzchołek docelowy krawędzi
                pw->w =  tab_val[i + 1][j];                 // Waga krawędzi
                pw->next = graf[tab_num[i][j]];
                graf[tab_num[i][j]] = pw;

            }
            if(j!=5){
                pw = new slistEl;
                pw->v = tab_num[i][j + 1];                    // Wierzchołek docelowy krawędzi
                pw->w = tab_val[i][j + 1];                    // Waga krawędzi
                pw->next = graf[tab_num[i][j]];
                graf[tab_num[i][j]] = pw;

            }
            if(i != 0) {
                pw = new slistEl;
                pw->v =  tab_num[i - 1][j];                  // Wierzchołek docelowy krawędzi
                pw->w =  tab_val[i - 1][j];                 // Waga krawędzi
                pw->next = graf[tab_num[i][j]];
                graf[tab_num[i][j]] = pw;

            }
            if(j!=0) {
                pw = new slistEl;
                pw->v = tab_num[i][j - 1];                    // Wierzchołek docelowy krawędzi
                pw->w = tab_val[i][j - 1];                    // Waga krawędzi
                pw->next = graf[tab_num[i][j]];
                graf[tab_num[i][j]] = pw;
            }
        }
    }

    p = findPath(graf, 36, 0, p);

    std::vector<int> onPath;
    int prev = 35;
    while ( prev ){
        onPath.push_back( prev );
        prev =  p[prev];
    }
    onPath.push_back(0);

    for (int i = 0; i < 6; ++i){
        for (int j = 0; j < 6; ++j) {
            bool contains = false;
            for (int i = 0; i < onPath.size(); ++i ) {
                if (onPath[i] == tab_num[i][j]) {
                    contains = true;
                    break;
                }
            }
            if (contains)
                std::cout << tab_val[i][j];
            else
                std::cout << " ";
        }
        cout << endl;
    }

    return 0;
}
