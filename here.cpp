struct slistEl{
  slistEl * next;
  int v, w;
};

int * findPath( slistEl **graf, int n, int start, int *p ){
  int i, j, u, *d;
  bool *QS;
  slistEl *pw;

  d = new int [ n ];
  p = new int [ n ];
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
