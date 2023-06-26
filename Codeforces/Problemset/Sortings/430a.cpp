#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100;
const I M=100;
I x_arr[N];
I inds[N],stds[N];
pair<I,I>rngs[M];
vector<I>brds;
I ress[N];
B cmp(I a,I b){
  return x_arr[a]<x_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  for(I i=0;i<m;i++){
    I l,r;cin>>l>>r;
    rngs[i]={l,r};
  }
  for(I i=0;i<m;i++){
    auto[l,r]=rngs[i];
    brds.push_back(l);
    brds.push_back(r+1);
  }
  sort(brds.begin(),brds.end());
  brds.erase(unique(brds.begin(),brds.end()),brds.end());
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  for(I i=0;i<n;i++)stds[i]=x_arr[inds[i]];
  I sgn=0;
  for(I i=0;i+1<brds.size();i++){
    I low=lower_bound(stds,stds+n,brds[i])-stds;
    I upp=lower_bound(stds,stds+n,brds[i+1])-stds;
    I mid=low+(upp-low)/2;
    if((upp-low)%2)sgn=!sgn;
    for(I j=low;j<mid;j++)ress[inds[j]]=sgn;
    for(I j=mid;j<upp;j++)ress[inds[j]]=!sgn;
  }
  for(I i=0;i<n;i++)printf("%i ",ress[i]);
}