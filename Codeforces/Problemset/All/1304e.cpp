#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I LOGN=17;
const I MAX=2e9;
vector<I>adjs[N];
I ancs[N][LOGN];
I tbgs[N],teds[N];
I diss[N];
I t=0;
void dfs(I a,I p,I d=0){
  tbgs[a]=t++,ancs[a][0]=p,diss[a]=d;
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
I dis(I a,I b){
  return diss[a]+diss[b]-2*diss[lca(a,b)];
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
    I x,y,a,b,k;cin>>x>>y>>a>>b>>k,a--,b--,x--,y--;
    I dis1=dis(a,x)+1+dis(y,b),dis2=dis(a,y)+1+dis(x,b),dis3=dis(a,b),res=MAX;
    if(dis1%2==k%2)res=min(res,dis1);
    if(dis2%2==k%2)res=min(res,dis2);
    if(dis3%2==k%2)res=min(res,dis3);
    printf("%s\n",res<=k?"YES":"NO");
  }
}