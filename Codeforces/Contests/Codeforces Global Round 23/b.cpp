#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;
const I MAX=1e9;

I a_arr[N];
I ps1[N+1],ps2[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)ps1[i+1]=a_arr[i]==1;
    for(I i=0;i<n;i++)ps2[i+1]=a_arr[i]==0;
    for(I i=0;i<n;i++)ps1[i+1]+=ps1[i];
    for(I i=0;i<n;i++)ps2[i+1]+=ps2[i];
    I res=MAX;
    for(I i=0;i<=n;i++)if(ps1[i]-ps1[0]>=ps2[n]-ps2[i])
      res=min(res,ps1[i]-ps1[0]);
    printf("%i\n",res);
  }
}