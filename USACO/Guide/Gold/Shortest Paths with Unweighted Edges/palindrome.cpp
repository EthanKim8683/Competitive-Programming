#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I N=1000;
const I MAX=1e9;
set<I>adjs[N][26];
B neis[N][N];
I diss[N][N];
queue<pair<I,I>>ques;
void add(I dis,I i,I j){
  if(dis>=diss[i][j])return;
  diss[i][j]=dis,ques.push({i,j});
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&diss[0][0],&diss[0][0]+N*N,MAX);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;C c;cin>>a>>b>>c,a--,b--;
    adjs[a][c-'a'].insert(b);
    adjs[b][c-'a'].insert(a);
    neis[a][b]=neis[b][a]=1;
  }
  I res=MAX;
  add(0,0,n-1);
  while(ques.size()){
    auto[a,b]=ques.front();ques.pop();
    if(a==b)res=min(res,diss[a][b]);
    if(neis[a][b])res=min(res,diss[a][b]+1);
    for(I i=0;i<26;i++)for(auto c:adjs[a][i])for(auto d:adjs[b][i])add(diss[a][b]+2,c,d);
  }
  printf("%i\n",res==MAX?-1:res);
}