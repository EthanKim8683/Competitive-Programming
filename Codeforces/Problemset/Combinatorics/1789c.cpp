#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I M=2e5;
I a_arr[N];
I cnts[N+M+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    fill_n(cnts,n+m+1,0);
    for(I i=0;i<n;i++)cnts[a_arr[i]]+=m+1;
    for(I i=0;i<m;i++){
      I p,v;cin>>p>>v,p--;
      cnts[a_arr[p]]-=m-i;
      cnts[v]+=m-i;
      a_arr[p]=v;
    }
    Lli res=0;
    for(I i=1;i<=n+m;i++){
      I k=cnts[i];
      res+=(Lli)(m+1)*m/2-(Lli)(m+1-k)*(m-k)/2;
    }
    printf("%lli\n",res);
  }
}
/*
if a number is present in k of m + 1 arrays, then (m + 1 - k) * (m - k) / 2
pairs don't have the number

this means the contribution of a number x is (m + 1) * m / 2 - (m + 1 - k) *
(m - k) / 2
*/