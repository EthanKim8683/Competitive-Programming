#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;

I a_arr[N];
Lli ps1[N],ps2[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i+1<n;i++)ps1[i+1]+=max(a_arr[i]-a_arr[i+1],0);
  for(I i=n-1;i>0;i--)ps2[i-1]+=max(a_arr[i]-a_arr[i-1],0);
  for(I i=0;i+1<n;i++)ps1[i+1]+=ps1[i];
  for(I i=n-1;i>0;i--)ps2[i-1]+=ps2[i];
  while(m--){
    I s,t;cin>>s>>t,s--,t--;
    if(s<t)printf("%lli\n",ps1[t]-ps1[s]);
    else printf("%lli\n",ps2[t]-ps2[s]);
  }
}