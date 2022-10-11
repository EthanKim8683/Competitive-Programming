#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=2e5;

I a_arr[N];
I ps[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i+1<n;i++)ps[i+1+1]=a_arr[i]>=a_arr[i+1]*2;
    for(I i=0;i<n;i++)ps[i+1]+=ps[i];
    I res=0;
    for(I i=0;i+k+1<=n;i++)res+=!(ps[i+k+1]-ps[i+1]);
    printf("%i\n",res);
  }
}