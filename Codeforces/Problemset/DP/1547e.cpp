#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=3e5;
const I K=N;
const Lli MAX=1e18;

I a_arr[K];
I t_arr[K];
Lli ress[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    I n,k;cin>>n>>k;
    fill_n(ress,n,MAX);
    for(I i=0;i<k;i++)cin>>a_arr[i];
    for(I i=0;i<k;i++)cin>>t_arr[i];
    for(I i=0;i<k;i++)ress[a_arr[i]-1]=t_arr[i];
    for(I i=0;i+1<n;i++)ress[i+1]=min(ress[i+1],ress[i]+1);
    for(I i=n-1;i>0;i--)ress[i-1]=min(ress[i-1],ress[i]+1);
    for(I i=0;i<n;i++)printf("%lli ",ress[i]);
    printf("\n");
  }
}