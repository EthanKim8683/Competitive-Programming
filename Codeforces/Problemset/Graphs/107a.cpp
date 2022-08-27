#include<iostream>
#include<cstdio>
#include<vector>
#include<tuple>

using namespace std;

using I=int;

const I N=1000;
const I MAX=1e9;

I inds[N];
I outs[N];
pair<I,I>adjs[N];
vector<tuple<I,I,I>>ress;

void dfs(I a,I r,I m){
  if(outs[a]==0&&inds[a]>0){ress.push_back({r,a,m});return;}
  auto[b,d]=adjs[a];
  dfs(b,r,min(m,d));
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,p;cin>>n>>p;
  for(I i=0;i<p;i++){
    I a,b,d;cin>>a>>b>>d,a--,b--;
    inds[b]++,outs[a]++;
    adjs[a]={b,d};
  }
  for(I i=0;i<n;i++)if(inds[i]==0&&outs[i]>0)dfs(i,i,MAX);
  printf("%i\n",ress.size());
  for(auto[i,j,m]:ress)printf("%i %i %i\n",i+1,j+1,m);
  return 0;
}