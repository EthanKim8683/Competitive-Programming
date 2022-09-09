#include<iostream>
#include<cstdio>
#include<map>
#include<vector>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

I b_arr[N];
map<I,vector<I>>jous;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>b_arr[i];
  for(I i=0;i<n;i++)jous[i-b_arr[i]].push_back(i);
  Lli res=0;
  for(auto&[i,jou]:jous){
    Lli sum=0;
    for(auto j:jou)sum+=b_arr[j];
    res=max(res,sum);
  }
  printf("%lli\n",res);
  return 0;
}