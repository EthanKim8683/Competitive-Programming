#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I M=1e5;
const I N=1e5;
const I MAX=2e9;
I a_arr[M];
I b_arr[N];
I c_arr[N];
I inds1[N],inds2[N];
I ress[M];
set<pair<I,I>>pres;
I n,m,s;
B cmp1(I a,I b){
  return a_arr[a]>a_arr[b];
}
B cmp2(I a,I b){
  return b_arr[a]>b_arr[b];
}
B chk(I x){
  Lli tot=0;
  pres.clear();
  for(I i=0,j=0;i<m;){
    while(j<n){
      I k=inds2[j];
      if(b_arr[k]<a_arr[inds1[i]])break;
      pres.insert({c_arr[k],k}),j++;
    }
    if(!pres.size())return 0;
    auto it=pres.begin();
    auto[cst,k]=*it;
    pres.erase(it);
    tot+=cst;
    for(I l=0;l<x&&i<m;i++,l++)ress[inds1[i]]=k;
  }
  return tot<=s;
}
I fnd(){
  I l=1,r=m;
  while(l<r){
    I t=l+(r-l)/2;
    chk(t)?r=t:l=t+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m>>s;
  for(I i=0;i<m;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>b_arr[i];
  for(I i=0;i<n;i++)cin>>c_arr[i];
  iota(inds1,inds1+m,0);
  sort(inds1,inds1+m,cmp1);
  iota(inds2,inds2+n,0);
  sort(inds2,inds2+n,cmp2);
  B vld=chk(fnd());
  if(!vld)printf("NO\n"),exit(0);
  printf("YES\n");
  for(I i=0;i<m;i++)printf("%i ",ress[i]+1);
}