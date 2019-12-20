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
