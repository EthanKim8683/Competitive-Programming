#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=2e5;
const I A=1e7;

I a_arr[N];
I dp1[A+1];
set<I>dp2;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill_n(dp1,A+1,-1);
  for(Lli i=1;i<=A;i++){
    if(dp1[i]!=-1)continue;
    for(Lli j=1;i*j*j<=A;j++)dp1[i*j*j]=i;
  }
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I res=1;
    dp2.clear();
    for(I i=0;i<n;i++){
      I a=dp1[a_arr[i]];
      if(dp2.count(a))dp2.clear(),res++;
      dp2.insert(a);
    }
    printf("%i\n",res);
  }
}