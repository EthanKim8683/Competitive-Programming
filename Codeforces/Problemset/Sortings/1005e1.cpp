#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
I p_arr[N];
Lli upps[2*N+1],lows[2*N+2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>p_arr[i];
  I j=find(p_arr,p_arr+n,m)-p_arr;
  I low=0;
  for(I i=j;i>=0;i--)low+=(p_arr[i]>m)-(p_arr[i]<m),lows[N+low]++;
  I upp=0;
  for(I i=j;i<n;i++)upp+=(p_arr[i]>m)-(p_arr[i]<m),upps[N+upp]++;
  Lli res=0;
  for(I i=-n;i<=n;i++)res+=upps[N+i]*(lows[N-i]+lows[N-i+1]);
  printf("%lli\n",res);
}