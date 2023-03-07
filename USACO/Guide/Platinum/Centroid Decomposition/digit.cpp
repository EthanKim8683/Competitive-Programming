#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=100000;
vector<pair<I,I>>adjs[N];
I sizs[N];
B viss[N];
map<Lli,I>cnts1,cnts2;
Lli itn;
Lli res=0;
Lli m;
Lli mod(Lli x){
  return(x%m+m)%m;
}
tuple<Lli,Lli,Lli>gcd(Lli a,Lli b) {
  if(!b)return{1,0,a};
  auto[x,y,d]=gcd(b,a%b);
  return{y,x-a/b*y,d};
}
Lli inv(Lli a) {
  auto[x,y,d]=gcd(a,m);
  return(x%m+m)%m;
}
I dfs1(I a,I p=-1){
  sizs[a]=1;
  for(auto[b,w]:adjs[a])if(b!=p&&!viss[b])sizs[a]+=dfs1(b,a);
  return sizs[a];
}
I dfs2(I a,I siz,I p=-1){
  for(auto[b,w]:adjs[a])if(b!=p&&!viss[b]&&sizs[b]*2>siz)return dfs2(b,siz,a);
  return a;
}
void dfs4(I a,I p,Lli upp,Lli low,Lli ufc,Lli lfc){
  res+=cnts1[mod(0-low)]+cnts2[mod(0-upp)];
  for(auto[b,w]:adjs[a])if(b!=p&&!viss[b])dfs4(b,a,(upp+w*ufc)%m,(low+w*lfc)%m,ufc*10%m,lfc*itn%m);
}
void dfs5(I a,I p,Lli upp,Lli low,Lli ufc,Lli lfc){
  cnts1[upp]++,cnts2[low]++;
  for(auto[b,w]:adjs[a])if(b!=p&&!viss[b])dfs5(b,a,(upp+w*ufc)%m,(low+w*lfc)%m,ufc*10%m,lfc*itn%m);
}
void dfs3(I a){
  a=dfs2(a,dfs1(a));
  viss[a]=1;
  cnts1.clear(),cnts2.clear();
  cnts1[0]++,cnts2[0]++;
  for(auto[b,w]:adjs[a])if(!viss[b])dfs4(b,a,w%m,w*itn%m,10%m,itn*itn%m),dfs5(b,a,w%m,w*itn%m,10%m,itn*itn%m);
  for(auto[b,w]:adjs[a])if(!viss[b])dfs3(b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>m;
  for(I i=0;i<n-1;i++){
    I u,v,w;cin>>u>>v>>w;
    adjs[u].push_back({v,w});
    adjs[v].push_back({u,w});
  }
  if(m==1)printf("%lli\n",(Lli)n*(n-1)),exit(0);
  itn=inv(10);
  dfs3(0);
  printf("%lli\n",res);
}