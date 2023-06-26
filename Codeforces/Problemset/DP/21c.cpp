#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I nums[N];
Lli pres[N];
map<Lli,I>cnts;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>nums[i];
  copy_n(nums,n,pres);
  for(I i=0;i+1<n;i++)pres[i+1]+=pres[i];
  if(pres[n-1]%3)printf("0\n"),exit(0);
  Lli sum=pres[n-1]/3;
  for(I i=0;i<n-1;i++)cnts[pres[i]]++;
  Lli res=0,pre=0;
  for(I i=n-1;i>0;i--){
    cnts[pres[i-1]]--,pre+=nums[i];
    if(pre==sum)res+=cnts[sum];
  }
  printf("%lli\n",res);
}