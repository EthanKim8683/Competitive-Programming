#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e5;
const Lli MOD=1e9+7;
const I MAX=1e9;
const I MIN=-MAX;
I a_arr[N];
I inds[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)inds[a_arr[i]]=i;
    Lli res=1;
    I l=MAX,r=MIN;
    for(I i=0;i<n;i++){
      I j=inds[i];
      B end=0;
      if(j>r)r=j,end=1;
      if(j<l)l=j,end=1;
      if(end)continue;
      (res*=r-l+1-i)%=MOD;
    }
    printf("%lli\n",res);
  }
}