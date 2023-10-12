#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e5;
I a_arr[N];
I b_arr[N];
Lli csts[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I a,b,n;cin>>a>>b>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)cin>>b_arr[i];
    for(I i=0;i<n;i++)csts[i]=(Lli)(b_arr[i]+a-1)/a*a_arr[i];
    Lli tot=accumulate(csts,csts+n,0ll);
    B res=0;
    for(I i=0;i<n;i++)res|=b-(tot-csts[i]+(Lli)((b_arr[i]+a-1)/a-1)*a_arr[i])>0;
    printf("%s\n",res?"YES":"NO");
  }
}