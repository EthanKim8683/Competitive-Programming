#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2e5;
const I M=2e5;
const I LOGN=18;
const I MIN=-1e9;
I a_arr[N];
I b_arr[M];
vector<pair<I,I>>rngs;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  I x,k,y;cin>>x>>k>>y;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<m;i++)cin>>b_arr[i];
  I j=0;
  for(I i=0;i<m;i++,j++){
    I l=j;
    for(;j<n;j++)if(a_arr[j]==b_arr[i])break;
    if(j>=n||a_arr[j]!=b_arr[i])printf("-1"),exit(0);
    if(l<j)rngs.push_back({l,j});
  }
  if(j<n)rngs.push_back({j,n});
  Lli res=0;
  for(auto[l,r]:rngs){
    I upp=MIN;
    if(l>0)upp=max(upp,a_arr[l-1]);
    if(r<n)upp=max(upp,a_arr[r]);
    if(r-l>=k){
      if(x>(Lli)y*k){
        B fnd=0;
        for(I i=l;i<r;i++)fnd|=a_arr[i]>upp;
        res+=fnd?x+(Lli)(r-l-k)*y:(Lli)(r-l)*y;
      }else{
        I cnt=(r-l)/k,rem=r-l-cnt*k;
        res+=(Lli)cnt*x+(Lli)rem*y;
      }
    }else{
      B fnd=0;
      for(I i=l;i<r;i++)fnd|=a_arr[i]>upp;
      if(fnd)printf("-1"),exit(0);
      res+=(Lli)y*(r-l);
    }
  }
  printf("%lli\n",res);
}