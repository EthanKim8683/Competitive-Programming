#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200000;
const Lli MOD=998244353;
I p_arr[N];
I invs[N+1];
vector<I>inds;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>p_arr[i];
  for(I i=0;i<n;i++)invs[p_arr[i]]=i;
  for(I i=n;i>n-k;i--)inds.push_back(invs[i]);
  sort(inds.begin(),inds.end());
  Lli res=1;
  for(I i=0;i+1<inds.size();i++)(res*=inds[i+1]-inds[i])%=MOD;
  printf("%lli %lli\n",(Lli)n*(n+1)/2-(Lli)(n-k)*(n-k+1)/2,res);
}
/*
each of the k segments must contain the k greatest values (n - k, n]

therefore, we can find the number of ways to divide between the indices of
each of the k greatest values
*/