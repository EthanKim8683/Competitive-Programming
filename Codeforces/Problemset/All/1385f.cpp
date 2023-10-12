#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I MAX=1e9;
vector<I>adjs[N];
I dp1[N],dp2[N];
I dp3[N],dp4[N];
I dp5[N],dp6[N];
I res;
I k;
void dfs1(I a,I p=-1){
  I cnt1=0,cnt2=0,cnt3=0;
  for(auto b:adjs[a])if(b!=p){
    dfs1(b,a);
    cnt1+=dp1[b]>0;
    cnt2+=dp1[b]==0;
    cnt3+=dp3[b]+dp5[b]/k;
  }
  dp1[a]=cnt1;
  dp1[a]+=(adjs[a].size()-(p!=-1))%k!=0;
  dp3[a]=cnt3;
  dp5[a]=cnt2;
}
void dfs2(I a,I p=-1){
  I cnt1=0,cnt2=0,cnt3=0;
  if(p!=-1){
    cnt1+=dp2[a]>0;
    cnt2+=dp2[a]==0;
    cnt3+=dp4[a]+dp6[a]/k;
  }
  for(auto b:adjs[a])if(b!=p){
    cnt1+=dp1[b]>0;
    cnt2+=dp1[b]==0;
    cnt3+=dp3[b]+dp5[b]/k;
  }
  for(auto b:adjs[a])if(b!=p){
    cnt1-=dp1[b]>0;
    cnt2-=dp1[b]==0;
    cnt3-=dp3[b]+dp5[b]/k;
    dp2[b]=cnt1;
    dp2[b]+=(adjs[a].size()-1)%k!=0;
    dp4[b]=cnt3;
    dp6[b]=cnt2;
    dfs2(b,a);
    cnt1+=dp1[b]>0;
    cnt2+=dp1[b]==0;
    cnt3+=dp3[b]+dp5[b]/k;
  }
  res=max(res,cnt3+cnt2/k);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n>>k;
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<n-1;i++){
      I x,y;cin>>x>>y,x--,y--;
      adjs[x].push_back(y);
      adjs[y].push_back(x);
    }
    fill_n(dp1,n,0),fill_n(dp2,n,0);
    fill_n(dp3,n,0),fill_n(dp4,n,0);
    fill_n(dp5,n,0),fill_n(dp6,n,0);
    res=0;
    dfs1(0),dfs2(0);
    printf("%i\n",res);
  }
}
/*
a vertex can become a leaf if it has some multiple of k children, and each
child can become a leaf

effectively, we are solving for all roots, where we never remove the root
*/