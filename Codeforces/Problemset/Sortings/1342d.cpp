#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I K=2e5;
I m_arr[N];
I c_arr[K];
vector<I>ress[N];
I n;
B chk(I x){
  for(I i=0;i<x;i++)ress[i].clear();
  for(I i=0;i<n;i++){
    I j=i%x,m=m_arr[i];
    if(ress[j].size()>=c_arr[m-1])return 0;
    ress[j].push_back(m);
  }
  return 1;
}
I fnd(){
  I l=1,r=n;
  while(l<r){
    I m=l+(r-l)/2;
    chk(m)?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>m_arr[i];
  for(I i=0;i<k;i++)cin>>c_arr[i];
  sort(m_arr,m_arr+n);
  reverse(m_arr,m_arr+n);
  I res=fnd();
  chk(res);
  printf("%i\n",res);
  for(I i=0;i<res;i++){
    printf("%i ",ress[i].size());
    for(auto j:ress[i])printf("%i ",j);
    printf("\n");
  }
}