#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using S=string;
using Lli=long long int;
const I N=300000;
const I MIN=-1e9;
C lens[N];
I adjs[N][2];
vector<pair<I,I>>bnds[N];
Lli res=0;
I dfs(I a){
  I cen=0;
  if(adjs[a][0]==0&&adjs[a][1]==0);
  if(adjs[a][0]!=0&&adjs[a][1]==0){
    I b=adjs[a][0];
    cen=dfs(b);
    swap(bnds[a],bnds[b]);
    bnds[b].clear();
    res+=3;
  }
  if(adjs[a][0]!=0&&adjs[a][1]!=0){
    I b=adjs[a][0],c=adjs[a][1];
    I cen1=dfs(b),cen2=dfs(c);
    if(bnds[c].size()>bnds[b].size()){
      I dis=MIN;
      for(I i=0;i<bnds[b].size();i++){
        I j=i+bnds[c].size()-bnds[b].size();
        auto[l1,r1]=bnds[b][i];
        auto[l2,r2]=bnds[c][j];
        dis=max(dis,r1-l2+cen2-cen1|1);
      }
      for(I i=0;i<bnds[b].size();i++){
        I j=i+bnds[c].size()-bnds[b].size();
        auto[l1,r1]=bnds[b][i];
        auto[l2,r2]=bnds[c][j];
        bnds[c][j]={l1+cen2-cen1-dis-1,r2};
      }
      swap(bnds[a],bnds[c]);
      bnds[b].clear();
      bnds[c].clear();
      cen=cen2-dis/2-1;
      res+=dis+5;
    }else{
      I dis=MIN;
      for(I i=0;i<bnds[c].size();i++){
        I j=i+bnds[b].size()-bnds[c].size();
        auto[l1,r1]=bnds[b][j];
        auto[l2,r2]=bnds[c][i];
        dis=max(dis,r1-l2+cen2-cen1|1);
      }
      for(I i=0;i<bnds[c].size();i++){
        I j=i+bnds[b].size()-bnds[c].size();
        auto[l1,r1]=bnds[b][j];
        auto[l2,r2]=bnds[c][i];
        bnds[b][j]={l1,r2+cen1-cen2+dis+1};
      }
      swap(bnds[a],bnds[b]);
      bnds[b].clear();
      bnds[c].clear();
      cen=cen1+dis/2+1;
      res+=dis+5;
    }
  }
  I len=lens[a];
  bnds[a].push_back({cen-(len+1)/2,cen+(len+2)/2});
  res+=3*len+6;
  return cen;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S nam;cin>>nam;
  lens[0]=nam.size();
  for(I i=1;i<n;i++){
    S nam;I par;cin>>nam>>par,par--;
    lens[i]=nam.size();
    adjs[par][!!adjs[par][0]]=i;
  }
  dfs(0);
  printf("%lli\n",res);
}