#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I MAX=1e9;
const I LOGN=17;
vector<I>adjs[N];
I ancs[N][LOGN];
I deps[N];
I tbgs[N],teds[N];
queue<I>ques;
I diss[N];
I tim=0;
void add(I i,I d){
  if(d<diss[i])diss[i]=d,ques.push(i);
}
void dfs(I a,I p){
  tbgs[a]=tim++;
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  for(auto b:adjs[a])if(b!=p)deps[b]=deps[a]+1,dfs(b,a);
  teds[a]=tim;
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
I lca(I a,I b,I c){
  I x=lca(a,b),y=lca(a,c),z=lca(b,c);
  I res=x;
  if(anc(res,y))res=y;
  if(anc(res,z))res=z;
  return res;
}
I dis(I a,I b){
  I c=lca(a,b);
  return deps[a]+deps[b]-2*deps[c];
}
I dds(I r){
  return adjs[r].size()>=2?0:diss[r];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  fill_n(diss,n,MAX);
  for(I i=0;i<n;i++)if(adjs[i].size()>2)add(i,0);
  while(ques.size()){
    I a=ques.front();ques.pop();
    for(auto b:adjs[a])add(b,diss[a]+1);
  }
  dfs(0,0);
  while(q--){
    I a,b,r;cin>>a>>b>>r,a--,b--,r--;
    I c=lca(a,b,r);
    if(r==a||r==b){
      I res=MAX;
      res=min(res,dis(a,b));
      res=min(res,dds(r)*2+1);
      printf("%i\n",res);
      continue;
    }
    if(c==a||c==b){
      I res=MAX;
      res=min(res,dis(a,b));
      res=min(res,dds(r)*2);
      res=min(res,abs(dis(a,r)-dds(r))+dds(r)+1);
      res=min(res,abs(dis(b,r)-dds(r))+dds(r)+1);
      printf("%i\n",res);
      continue;
    }
    I res=MAX;
    res=min(res,dis(a,b));
    res=min(res,dis(c,r));
    res=min(res,dds(r)*2);
    printf("%i\n",res);
  }
}