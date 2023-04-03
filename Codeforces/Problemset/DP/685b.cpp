#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=300000;
const I LOGN=19;
vector<I>adjs[N];
I sizs[N],lrgs[N];
I ancs[N][LOGN];
I cens[N];
I tbgs[N],teds[N];
I dfs1(I a,I p){
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  sizs[a]=1;
  for(auto b:adjs[a]){
    sizs[a]+=dfs1(b,a);
    lrgs[a]=max(lrgs[a],sizs[b]);
  }
  return sizs[a];
}
B chk(I a,I siz){
  return siz>=2*lrgs[a]&&siz>=2*(siz-sizs[a]);
}
I fnd(I a,I siz){
  if(siz>=2*(siz-sizs[a]))return a;
  for(I i=LOGN-1;i>=0;i--)if(siz<2*(siz-sizs[ancs[a][i]]))a=ancs[a][i];
  return ancs[a][0];
}
void dfs2(I a){
  cens[a]=a;
  for(auto b:adjs[a]){
    dfs2(b);
    I c=fnd(cens[b],sizs[a]);
    if(chk(c,sizs[a]))cens[a]=c;
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=1;i<n;i++){
    I p;cin>>p,p--;
    adjs[p].push_back(i);
  }
  dfs1(0,0),dfs2(0);
  while(q--){
    I v;cin>>v,v--;
    printf("%i\n",cens[v]+1);
  }
}