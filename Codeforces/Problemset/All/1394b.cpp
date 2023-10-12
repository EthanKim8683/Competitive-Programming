#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I K=9;
vector<pair<I,I>>adjs1[N],adjs2[N];
set<pair<I,I>>curs;
I ords[N];
B invs[K][K][K][K];
I pres[K];
I k;
I res=0;
void dfs(I i){
  if(i==k){res++;return;}
  for(I j=0;j<=i;j++){
    pres[i]=j;
    B inv=0;
    for(I l=0;l<=i;l++)inv|=invs[i][j][l][pres[l]];
    if(!inv)dfs(i+1);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m>>k;
  for(I i=0;i<m;i++){
    I u,v,w;cin>>u>>v>>w,u--,v--;
    adjs1[u].push_back({v,i});
    adjs2[v].push_back({u,i});
    ords[i]=w;
  }
  for(I i=0;i<n;i++){
    sort(adjs1[i].begin(),adjs1[i].end(),[&](pair<I,I>a,pair<I,I>b){
      return ords[a.second]<ords[b.second];
    });
    for(I j=0;j<adjs1[i].size();j++)ords[adjs1[i][j].second]=j;
  }
  for(I i=0;i<n;i++){
    curs.clear();
    for(auto[x1,y1]:adjs2[i]){
      x1=adjs1[x1].size()-1,y1=ords[y1];
      for(auto[x2,y2]:curs)invs[x1][y1][x2][y2]=invs[x2][y2][x1][y1]=1;
      curs.insert({x1,y1});
    }
  }
  dfs(0);
  printf("%i\n",res);
}
/*
since, starting from every vertex u, it must be possible to return to u in
finite time, the selected edges (one for each node, a functional graph) must
form only cycles

therefore, every vertex must have an indegree no greater than 1 (since this is
a functional graph, this also implies no vertices have indegree less than 1)

with this, we can invalidate (i, c[i]) pairs that result in vertices having
indegree greater than 1 and brute force for the number of tuples containing
no such pairs
*/