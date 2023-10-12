#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=200000;
const I R=25000;
const I LOGN=18;
I h_arr[N];
vector<I>adjs[N];
map<pair<I,I>,I>ress;
I tbgs[N],teds[N];
vector<I>cits[R];
vector<I>tims[R];
vector<I>spas[R][LOGN];
I viss[R];
I cnts[N];
I t=0;
void dfs(I a,I dep=0){
  I h=h_arr[a];
  cits[h].push_back(a);
  viss[h]++,cnts[a]=viss[h];
  tbgs[a]=t++;
  for(auto b:adjs[a])dfs(b,dep+1);
  teds[a]=t;
  viss[h]--;
}
void bld(I i){
  for(I j=1;j<LOGN;j++)for(I k=0;k+(1<<j)<=cits[i].size();k++)spas[i][j].push_back(max(spas[i][j-1][k],spas[i][j-1][k+(1<<(j-1))]));
}
I qry(I i,I l,I r){
  I d=31-__builtin_clz(r-l);
  return max(spas[i][d][l],spas[i][d][r-(1<<d)]);
}
I slv1(I i,I j){
  return lower_bound(tims[j].begin(),tims[j].end(),teds[i])-lower_bound(tims[j].begin(),tims[j].end(),tbgs[i]);
}
I slv2(I i,I j){
  I k=upper_bound(tims[j].begin(),tims[j].end(),tbgs[i])-tims[j].begin()-1;
  if(k<0)return 0;
  I l=0,r=k;
  while(l<r){
    I m=l+(r-l+1)/2;
    qry(j,m,k+1)>=teds[i]?l=m:r=m-1;
  }
  return qry(j,l,k+1)>=teds[i]?cnts[cits[j][l]]:0;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,r,q;cin>>n>>r>>q;
  I h;cin>>h,h--;
  h_arr[0]=h;
  for(I i=1;i<n;i++){
    I s,h;cin>>s>>h,s--,h--;
    adjs[s].push_back(i);
    h_arr[i]=h;
  }
  dfs(0);
  for(I i=0;i<r;i++){
    for(auto j:cits[i])tims[i].push_back(tbgs[j]),spas[i][0].push_back(teds[j]);
    bld(i);
  }
  while(q--){
    I r1,r2;cin>>r1>>r2,r1--,r2--;
    auto it=ress.find({r1,r2});
    if(it!=ress.end()){
      printf("%i\n",it->second),fflush(stdout);
      continue;
    }
    I res=0;
    if(cits[r1].size()<cits[r2].size())for(auto i:cits[r1])res+=slv1(i,r2);
    if(cits[r2].size()<=cits[r1].size())for(auto i:cits[r2])res+=slv2(i,r1);
    ress[{r1,r2}]=res;
    printf("%i\n",res),fflush(stdout);
  }
}