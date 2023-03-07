#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=1e5;
const I LOGN=17;
vector<I>adjs[N];
I deps[N];
I ancs[N][LOGN];
I tbgs[N],teds[N];
pair<Lli,I>incs[N],decs[N];
pair<Lli,I>irms[N],drms[N];
Lli ress[N];
I t=0;
void dfs1(I a,I p,I d=0){
  tbgs[a]=t++;
  deps[a]=d;
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  for(auto b:adjs[a])if(b!=p)dfs1(b,a,d+1);
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
  I c=lca(a,b);
  return deps[a]+deps[b]-2*deps[c];
}
void dfs2(I a,I p=-1){
  for(auto b:adjs[a])if(b!=p){
    dfs2(b,a);
    incs[a].first+=incs[b].first,incs[a].second+=incs[b].second;
    decs[a].first+=decs[b].first,decs[a].second+=decs[b].second;
  }
  incs[a].first-=irms[a].first,incs[a].second-=irms[a].second;
  decs[a].first-=drms[a].first,decs[a].second-=drms[a].second;
  ress[a]+=incs[a].first+decs[a].first;
  incs[a].first+=incs[a].second;
  decs[a].first-=decs[a].second;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,s;cin>>n>>s;
  for(I i=0;i<n-1;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  dfs1(0,0);
  for(I i=0;i<s;i++){
    I a,b,t;cin>>a>>b>>t,a--,b--,t--;
    I c=lca(a,b),d=lca(a,t),e=lca(b,t);
    if(anc(d,c))d=c;
    if(anc(e,c))e=c;
    decs[a].first+=dis(a,t);
    decs[a].second++;
    drms[d].first+=dis(d,t);
    drms[d].second++;
    incs[d].first+=dis(d,t);
    incs[d].second++;
    irms[c].first+=dis(c,t);
    irms[c].second++;
    decs[b].first+=dis(b,t);
    decs[b].second++;
    drms[e].first+=dis(e,t);
    drms[e].second++;
    incs[e].first+=dis(e,t);
    incs[e].second++;
    irms[c].first+=dis(c,t);
    irms[c].second++;
    ress[c]+=dis(c,t);
  }
  for(I i=0;i<n;i++){}
  dfs2(0);
  for(I i=0;i<n;i++)printf("%lli ",ress[i]);
}