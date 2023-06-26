#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e4;
I a_arr[N];
I upps[N],lows[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    copy_n(a_arr,n,upps);
    copy_n(a_arr,n,lows);
    for(I i=0;i+1<n;i++)upps[i+1]=max(upps[i+1],upps[i]);
    for(I i=n-1;i>0;i--)lows[i-1]=min(lows[i-1],lows[i]);
    B res=0;
    for(I i=0;i+1<n;i++)res|=upps[i]>lows[i];
    printf("%s\n",res?"YES":"NO");
  }
}