#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100000;
const Lli MOD=998244353;
I a_arr[N];
vector<I>dgts;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli res=0;
  for(I i=0;i<n;i++){
    dgts.clear();
    for(I j=a_arr[i];j;j/=10)dgts.push_back(j%10);
    reverse(dgts.begin(),dgts.end());
    Lli cur=0;
    for(auto j:dgts)cur=(cur*100+j)%MOD;
    (res+=cur*11*n)%=MOD;
  }
  printf("%lli\n",res);
}
/*
each element contributes to the sum independently
*/