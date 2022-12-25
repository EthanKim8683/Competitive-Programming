#include<iostream>
#include<cstdio>
#include<vector>
#include<tuple>
#include<algorithm>
#include<queue>
#include<unordered_map>

using namespace std;

using I=int;

/*
m colors means that, two edges of the same
color can always be corrected without
affecting other edges

actually, that's wrong. if one edge decides
to repaint itself, and leads to a node which
has an edge choosing to repaint all the
others, the first edge's repainting cost
would be counted twice.
*/

const I N=100000;
const I MAX = 1e9;

vector<tuple<I,I,I>>adjs1[N];
unordered_map<I,I>cols[N];
priority_queue<tuple<I,I,I>,vector<tuple<I,I,I>>,greater<tuple<I,I,I>>>que;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;
  cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b,c,p;
    cin>>a>>b>>c>>p;
    a--,b--,c--;
    adjs1[a].push_back({b,c,p});
    adjs1[b].push_back({a,c,p});
    cols[a][c]+=p,cols[b][c]+=p;
  }
  return 0;
}