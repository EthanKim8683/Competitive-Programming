#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=50;
const I M=50;
I a_arr[N];
I b_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<m;i++)cin>>b_arr[i];
    Lli sum1=accumulate(a_arr,a_arr+n,0ll);
    Lli sum2=accumulate(b_arr,b_arr+m,0ll);
    printf("%s\n",sum1>sum2?"Tsondu":sum1<sum2?"Tenzing":"Draw");
  }
}