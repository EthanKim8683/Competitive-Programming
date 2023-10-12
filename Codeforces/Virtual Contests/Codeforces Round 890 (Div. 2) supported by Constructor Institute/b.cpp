#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    Lli sum=accumulate(a_arr,a_arr+n,0ll)-n;
    for(I i=0;i<n;i++)sum-=a_arr[i]==1;
    printf("%s\n",n>1&&sum>=0?"YES":"NO");
  }
}