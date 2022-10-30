#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

I knts[N];
vector<I>facs;
I dp[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>knts[i];
  I t=n;
  for(I i=3;i*i<=t;i++){
    if(t%i==0){
      facs.push_back(n/i);
      while(t%i==0)t/=i;
    }
  }
  if(t%4==0){
    facs.push_back(n/4);
    while(t%4==0)t/=4;
  }
  while(t%2==0)t/=2;
  if(t>2)facs.push_back(n/t);
  B res=0;
  for(auto i:facs){
    fill_n(dp,i,0);
    for(I j=0;j<n;j++)dp[j%i]+=!knts[j];
    res|=*min_element(dp,dp+i)==0;
  }
  printf("%s\n",res?"YES":"NO");
}