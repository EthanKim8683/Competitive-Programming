#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=3e5;
const I LOGN=19;
vector<I>adjs[N];
I deps[N];
I ancs[N][LOGN];
I tbgs[N],teds[N];
I t=0;
void dfs(I a,I p,I d=0){
  tbgs[a]=t++;
  deps[a]=d;
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  for(auto b:adjs[a])if(b!=p)dfs(b,a,d+1);
  teds[a]=t;
}
B anc(I a,I b){
  return tbgs[a]<=tbgs[b]&&teds[a]>=teds[b];
}
I lca(I a,I b){
  if(anc(a,b))return a;
  if(anc(b,a))return b;
  for(I i=LOGN-1;i>=0;i--)if(!anc(ancs[a][i],b))a=ancs[a][i];
  return ancs[a][0];
}
I jmp(I a,I i){
  for(I j=0;j<LOGN;j++)if(i>>j&1)a=ancs[a][j];
  return a;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  dfs(0,0);
  I q;cin>>q;
  while(q--){
    I a,b,c;cin>>a>>b>>c,a--,b--;
    I d=lca(a,b);
    I dis1=deps[a]-deps[d],dis2=deps[b]-deps[d];
    I e=c<dis1?jmp(a,c):jmp(b,max(dis2-(c-dis1),0));
    printf("%i\n",e+1);
  }
}