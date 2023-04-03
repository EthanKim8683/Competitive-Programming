#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
const I A=300;
I a_arr[N];
vector<I>dp;
I cnts[A+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,t;cin>>n>>t;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cnts[a_arr[i]]++;
  for(I i=0;i<min(n,t)*n;i++){
    I a=a_arr[i%n];
    auto it=upper_bound(dp.begin(),dp.end(),a);
    if(it==dp.end())dp.push_back(a);
    else*it=a;
  }
  printf("%i\n",dp.size()+(t-min(n,t))**max_element(cnts,cnts+A+1));
}