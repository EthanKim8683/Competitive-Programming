#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

I a_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    Lli sum=0;
    for(I i=0;i<n;i++)sum+=a_arr[i];
    Lli rem=sum%n;
    printf("%lli\n",rem*(n-rem));
  }
}