#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I M=2e5;
const I K=2e5;
const Lli MAX=9e18;

Lli a_arr[M+1];
Lli b_arr[M+1];
Lli c_arr[K+1];
Lli d_arr[K+1];
I inds[M+1];

B cmp(I a,I b){
  return b_arr[a]<b_arr[b];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli n;I m,k;cin>>n>>m>>k;
  Lli x,s;cin>>x>>s;
  for(I i=1;i<=m;i++)cin>>a_arr[i];
  for(I i=1;i<=m;i++)cin>>b_arr[i];
  for(I i=1;i<=k;i++)cin>>c_arr[i];
  for(I i=1;i<=k;i++)cin>>d_arr[i];
  a_arr[0]=x,b_arr[0]=0;
  c_arr[0]=0,d_arr[0]=0;
  iota(inds,inds+m+1,0);
  sort(inds,inds+m+1,cmp);
  Lli res=MAX;
  for(I i=0;i<=m;i++){
    Lli a=a_arr[i],b=b_arr[i];
    I j=upper_bound(d_arr,d_arr+k+1,s-b)-d_arr-1;
    if(j<0)continue;
    res=min(res,(n-c_arr[j])*a);
  }
  printf("%lli\n",res);
}