#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=200000;

I w_arr[N];
I ps1[N],ps2[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  I sum=0;
  for(I i=0;i<n;i++){
    I w,h;cin>>w>>h;
    w_arr[i]=w;
    ps1[i]=h;
    ps2[i]=h;
    sum+=w;
  }
  for(I i=0;i+1<n;i++)ps1[i+1]=max(ps1[i+1],ps1[i]);
  for(I i=n-1;i>0;i--)ps2[i-1]=max(ps2[i-1],ps2[i]);
  for(I i=0;i<n;i++){
    I res=0;
    if(i-1>=0)res=max(res,ps1[i-1]);
    if(i+1<n)res=max(res,ps2[i+1]);
    printf("%lli ",(Lli)(sum-w_arr[i])*res);
  }
}