#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I M=1e5;
pair<I,I>cans[N];
vector<I>bsbs[M+1];
I inds[M+1];
I csts[N];
B cmp(I a,I b){
  return bsbs[a].size()>bsbs[b].size();
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++){
    I s,r;cin>>s>>r;
    cans[i]={s,r};
  }
  for(I i=0;i<n;i++){
    auto[s,r]=cans[i];
    bsbs[s].push_back(-r);
  }
  for(I i=1;i<=m;i++)sort(bsbs[i].begin(),bsbs[i].end());
  iota(inds+1,inds+M+1,1);
  sort(inds+1,inds+M+1,cmp);
  I res=0;
  for(I i=1;i<=m;i++){
    I pre=0,upp=bsbs[inds[i]].size();
    for(I j=0;j<upp;j++){
      pre+=-bsbs[inds[i]][j];
      csts[j]+=max(pre,0);
    }
    for(I j=0;j<upp;j++)res=max(res,csts[j]);
  }
  printf("%i\n",res);
}