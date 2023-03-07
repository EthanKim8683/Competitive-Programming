#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=2e5;
const I M=2e5;
const I LOGN=18;
vector<I>adjs[N];
pair<I,I>nsts[M];
I ancs[N][LOGN];
I tbgs[N],teds[N];
I cnts[N];
map<pair<I,I>,I>olps;
I t=0;
void dfs1(I a,I p){
  tbgs[a]=t++;
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  for(auto b:adjs[a])if(b!=p)dfs1(b,a);
  teds[a]=t;
}
B anc(I a,I b){
  return tbgs[a]<=tbgs[b]&&teds[a]>=teds[b];
}
I bef(I a,I b){
  for(I i=LOGN-1;i>=0;i--)if(!anc(ancs[a][i],b))a=ancs[a][i];
  return a;
}
I lca(I a,I b){
  if(anc(a,b))return a;
  if(anc(b,a))return b;
  return ancs[bef(a,b)][0];
}
void dfs2(I a,I p=-1){
  for(auto b:adjs[a])if(b!=p)dfs2(b,a),cnts[a]+=cnts[b];
}
I main(){
#ifndef ETHANKIM8683
  freopen("exercise.in","r",stdin);
  freopen("exercise.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  for(I i=0;i<m-(n-1);i++){
    I a,b;cin>>a>>b,a--,b--;
    nsts[i]={a,b};
  }
  dfs1(0,0);
  for(I i=0;i<m-(n-1);i++){
    auto[a,b]=nsts[i];
    I c=lca(a,b);
    if(c!=a)cnts[a]++,cnts[c]--;
    if(c!=b)cnts[b]++,cnts[c]--;
  }
  dfs2(0);
  Lli res=0;
  for(I i=0;i<m-(n-1);i++){
    auto[a,b]=nsts[i];
    I c=lca(a,b);
    if(c!=a)a=bef(a,c),cnts[a]--,res+=cnts[a];
    if(c!=b)b=bef(b,c),cnts[b]--,res+=cnts[b];
  }
  for(I i=0;i<m-(n-1);i++){
    auto[a,b]=nsts[i];
    I c=lca(a,b);
    if(c==a||c==b)continue;
    a=bef(a,c),b=bef(b,c);
    if(a>b)swap(a,b);
    olps[{a,b}]++;
  }
  for(auto[olp,cnt]:olps)res-=(Lli)cnt*(cnt-1)/2;
  printf("%lli\n",res);
}