#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=3e5;

I a_arr[N];
I ps[N+1];
map<I,I>pres[2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)ps[i+1]=a_arr[i];
  for(I i=0;i<n;i++)ps[i+1]^=ps[i];
  Lli res=0;
  for(I i=0;i<n;i++){
    res+=pres[(i+1)%2][ps[i+1]];
    pres[i%2][ps[i]]++;
  }
  printf("%lli\n",res);
}