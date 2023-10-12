#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
vector<I>adjs1[N],adjs2[N];
vector<I>tops;
I pars[3][N];
I tots[N];
B viss[N];
I fnd(I t,I i){
  if(pars[t][i]<0)return i;
  return pars[t][i]=fnd(t,pars[t][i]);
}
void uni(I t,I a,I b){
  if((a=fnd(t,a))==(b=fnd(t,b)))return;
  if(pars[t][a]>pars[t][b])swap(a,b);
  pars[t][a]+=pars[t][b],pars[t][b]=a;
}
I siz(I t,I i){
  return-pars[t][i];
}
void dfs1(I a,I p=-1){
  if(viss[a])return;
  viss[a]=1;
  for(auto b:adjs1[a])if(b!=p)dfs1(b,a);
  tops.push_back(a);
}
void dfs2(I a,I r,I p=-1){
  if(viss[a])return;
  viss[a]=1,uni(0,a,r);
  for(auto b:adjs2[a])if(b!=p)dfs2(b,r,a);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&pars[0][0],&pars[0][0]+3*N,-1);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs1[a].push_back(b);
    adjs2[b].push_back(a);
    uni(2,a,b);
  }
  for(I i=0;i<n;i++)dfs1(i);
  reverse(tops.begin(),tops.end());
  fill_n(viss,n,0);
  for(auto i:tops)if(!viss[i])dfs2(i,i);
  for(I i=0;i<n;i++)for(auto j:adjs1[i])uni(1,fnd(0,i),fnd(0,j));
  for(I i=0;i<n;i++)if(fnd(0,i)==i&&siz(0,i)>1)tots[fnd(1,i)]+=siz(0,i);
  I res=0;
  for(I i=0;i<n;i++)if(fnd(1,i)==i)tots[i]+=siz(1,i)-1,res+=min(tots[i],siz(2,fnd(2,i)));
  printf("%i\n",res);
}