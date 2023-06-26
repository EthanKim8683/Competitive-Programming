#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=2e5;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    Lli sum1=a_arr[0],sum2=0;
    B res=0;
    for(I l=1,r=n-1;l<r;l++,r--){
      sum1+=a_arr[l],sum2+=a_arr[r];
      res|=sum1<sum2;
    }
    printf("%s\n",res?"YES":"NO");
  }
}