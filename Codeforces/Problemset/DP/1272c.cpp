#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using C=char;
using Lli=long long int;
using B=bool;

const I N=2e5;
const I K=26;

C c_arr[K];
Lli dp[N];
I k;

B vld(C c){
  return find(c_arr,c_arr+k,c)!=c_arr+k;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>k;
  S s;cin>>s;
  for(I i=0;i<k;i++)cin>>c_arr[i];
  for(I i=0;i<n;i++)dp[i]=vld(s[i]);
  Lli res=0;
  for(I i=0;i<n;i++){
    res+=dp[i];
    if(i+1<n&&vld(s[i+1]))dp[i+1]+=dp[i];
  }
  printf("%lli\n",res);
}