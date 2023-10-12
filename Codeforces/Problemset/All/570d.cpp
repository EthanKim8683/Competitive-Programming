#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I N=500000;
const I M=500000;
vector<I>adjs[N];
C strs[N+1];
vector<I>viss[N];
I tbgs[N],teds[N];
pair<I,I>qrys[M];
vector<I>inds[N];
I chrs[N];
I ps[N+1][26];
I cnts[2];
B ress[M];
I t=0;
void dfs(I a,I d=0){
  tbgs[a]=t,chrs[t]=strs[a]-'a',viss[d].push_back(t),t++;
  for(auto b:adjs[a])dfs(b,d+1);
  teds[a]=t-1;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=1;i<n;i++){
    I p;cin>>p,p--;
    adjs[p].push_back(i);
  }
  cin>>strs;
  dfs(0);
  for(I i=0;i<m;i++){
    I v,h;cin>>v>>h,v--,h--;
    I l=lower_bound(viss[h].begin(),viss[h].end(),tbgs[v])-viss[h].begin();
    I r=upper_bound(viss[h].begin(),viss[h].end(),teds[v])-viss[h].begin();
    qrys[i]={l,r},inds[h].push_back(i);
  }
  for(I i=0;i<n;i++){
    for(I j=0;j<26;j++)ps[0][j]=0;
    for(I j=0;j<viss[i].size();j++)for(I k=0;k<26;k++)ps[j+1][k]=ps[j][k]+(chrs[viss[i][j]]==k);
    for(auto j:inds[i]){
      auto[l,r]=qrys[j];
      cnts[0]=cnts[1]=0;
      for(I k=0;k<26;k++)cnts[(ps[r][k]-ps[l][k])%2]++;
      ress[j]=cnts[1]<=1;
    }
  }
  for(I i=0;i<m;i++)printf("%s\n",ress[i]?"Yes":"No");
}