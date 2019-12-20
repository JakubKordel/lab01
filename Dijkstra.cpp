int i, j, n, v, u, sptr, *d, *p, *S;
    bool *QS;                       // Zbiory Q i S
    slistEl **graf;                 // Tablica list sąsiedztwa
    slistEl *pw, *rw;
    n = 35;
    v = 0;
              // Węzeł startowy, liczba wierzchołków i krawędzi

    // Tworzymy tablice dynamiczne

    d = new int [ n ];                // Tablica kosztów dojścia
    p = new int [ n ];                // Tablica poprzedników
    QS = new bool [ n ];              // Zbiory Q i S
    graf = new slistEl * [ n ];       // Tablica list sąsiedztwa
    S = new int [ n ];                // Stos
    sptr = 0;                       // Wskaźnik stosu

    // Inicjujemy tablice dynamiczne

    for(i = 0; i < n; i++)
    {
        d [ i ] = MAXINT;
        p [ i ] = -1;
        QS [ i ] = false;
        graf [ i ] = NULL;
    }

    // Odczytujemy dane wejściowe

    int k = 0;
    int tab_val [6] [6];
    int tab_num [6] [6];
    for(int i =0; i < 6; ++i){
        for(int j = 0; j<6; ++j){
            /*cin >>*/ tab_val [i] [j] =1;
            tab_num[i][j] = k;
            ++k;
        }
    }
    for (int i = 0; i <6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if(j != 5) {
                pw = new slistEl;
                pw->v =  tab_num[i + 1][j];                  // Wierzchołek docelowy krawędzi
                pw->w =  tab_val[i + 1][j];;                 // Waga krawędzi
                pw->next = graf[tab_num[i][j]];
                graf[tab_num[i][j]] = pw;
            }
            if(i!=5){
                pw = new slistEl;
                pw->v = tab_num[i][j + 1];                    // Wierzchołek docelowy krawędzi
                pw->w = tab_val[i][j + 1];                    // Waga krawędzi
                pw->next = graf[tab_num[i][j]];
                graf[tab_num[i][j]] = pw;
            }
        }
    }
