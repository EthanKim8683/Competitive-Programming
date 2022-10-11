#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

I a_arr[N];
I ps[N+1];
I cnts[2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)ps[i+1]=a_arr[i]<0;
  for(I i=0;i<n;i++)ps[i+1]+=ps[i];
  Lli res0=0,res1=0;
  for(I i=0;i<n;i++){
    I t=ps[i+1]%2;
    cnts[ps[i]%2]++;
    res0+=cnts[!t];
    res1+=cnts[t];
  }
  printf("%lli %lli\n",res0,res1);
}