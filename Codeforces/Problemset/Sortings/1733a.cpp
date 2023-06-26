#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100;
const I K=100;
I a_arr[N];
I upps[K];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    fill_n(upps,k,0);
    for(I i=0;i<n;i++)upps[i%k]=max(upps[i%k],a_arr[i]);
    Lli res=0;
    for(I i=0;i<k;i++)res+=upps[i];
    printf("%lli\n",res);
  }
}