#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I LOGN=17;
vector<I>adjs[N];
I sizs[N];
I ancs[N][LOGN];
I tbgs[N],teds[N];
I t=0;
I dfs(I a,I p){
  tbgs[a]=t++;
  sizs[a]=1;
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  for(auto b:adjs[a])if(b!=p)sizs[a]+=dfs(b,a);
  teds[a]=t;
  return sizs[a];
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
I bef(I a,I b){
  I c=lca(a,b);
  if(c!=b)return ancs[b][0];
  for(I i=LOGN-1;i>=0;i--)if(!anc(ancs[a][i],b))a=ancs[a][i];
  return a;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs(0,0);
  while(q--){
    I a,b,c;cin>>a>>b>>c,a--,b--,c--;
    a=bef(a,c),b=bef(b,c);
    I res=0;
    if(a!=b){
      res=n;
      if(anc(a,c))res-=n-sizs[c];
      if(anc(b,c))res-=n-sizs[c];
      if(anc(c,a))res-=sizs[a];
      if(anc(c,b))res-=sizs[b];
    }
    printf("%i\n",res);
  }
}