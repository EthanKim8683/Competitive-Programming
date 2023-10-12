#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2e5;
const I M=2e5;
pair<Lli,Lli>ilds[N];
Lli a_arr[M];
pair<Lli,Lli>rngs[N-1];
I inds1[M],inds2[N-1];
multimap<Lli,I>upps;
Lli ress[N-1];
B cmp1(I a,I b){
  return a_arr[a]<a_arr[b];
}
B cmp2(I a,I b){
  return rngs[a]<rngs[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++){
    Lli l,r;cin>>l>>r;
    ilds[i]={l,r};
  }
  for(I i=0;i<m;i++)cin>>a_arr[i];
  for(I i=0;i+1<n;i++){
    auto[l1,r1]=ilds[i];
    auto[l2,r2]=ilds[i+1];
    rngs[i]={l2-r1,r2-l1};
  }
  iota(inds1,inds1+m,0);
  sort(inds1,inds1+m,cmp1);
  iota(inds2,inds2+n-1,0);
  sort(inds2,inds2+n-1,cmp2);
  fill_n(ress,n-1,-1);
  for(I i=0,j=0;i<m;i++){
    I x=inds1[i];Lli a=a_arr[x];
    for(;j<n-1;j++){
      I y=inds2[j];auto[l,r]=rngs[y];
      if(l>a)break;
      upps.insert({r,y});
    }
    while(upps.size()){
      auto it=upps.begin();
      auto[r,y]=*it;
      if(r>=a)break;
      upps.erase(it);
    }
    if(!upps.size())continue;
    auto it=upps.begin();
    auto[r,y]=*it;upps.erase(it);
    ress[y]=x;
  }
  for(I i=0;i<n-1;i++){
    if(ress[i]!=-1)continue;
    printf("No\n"),exit(0);
  }
  printf("Yes\n");
  for(I i=0;i<n-1;i++)printf("%i ",ress[i]+1);
}