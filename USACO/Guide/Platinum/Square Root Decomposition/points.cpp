#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e6;
const I X=1e6+1;
const I SQTX=1e3;
pair<I,I>pnts[N];
vector<I>inds[(X+SQTX-1)/SQTX];
B cmp1(I a,I b){
  return pnts[a].second<pnts[b].second;
}
B cmp2(I a,I b){
  return pnts[a].second>pnts[b].second;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    pnts[i]={x,y};
    inds[(x+SQTX-1)/SQTX].push_back(i);
  }
  for(I i=0;i<(X+SQTX-1)/SQTX;i++){
    sort(inds[i].begin(),inds[i].end(),i%2?cmp1:cmp2);
    for(auto j:inds[i])printf("%i ",j+1);
  }
}