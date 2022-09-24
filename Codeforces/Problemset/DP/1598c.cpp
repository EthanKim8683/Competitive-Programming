#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

I a_arr[N];
map<I,I>dp;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    Lli tot=0;
    for(I i=0;i<n;i++)tot+=a_arr[i];
    tot*=2;
    if(tot%n){printf("0\n");continue;}
    tot/=n;
    dp.clear();
    Lli res=0;
    for(I i=0;i<n;i++){
      I a=a_arr[i];
      res+=dp[tot-a];
      dp[a]++;
    }
    printf("%lli\n",res);
  }
}