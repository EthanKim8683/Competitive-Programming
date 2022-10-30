#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

I a_arr[N];
Lli csts[N/2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    Lli res=0;
    for(I i=0;i<n;i+=2)res+=a_arr[i];
    for(I i=0;2*i+1<n;i++)csts[i]=a_arr[2*i+1]-a_arr[2*i+0];
    Lli sum=0,bst=0;
    for(I i=0;2*i+1<n;i++){
      sum=max(sum,(Lli)0)+csts[i];
      bst=max(bst,sum);
    }
    for(I i=0;2*i+2<n;i++)csts[i]=a_arr[2*i+1]-a_arr[2*i+2];
    sum=0;
    for(I i=0;2*i+2<n;i++){
      sum=max(sum,(Lli)0)+csts[i];
      bst=max(bst,sum);
    }
    printf("%lli\n",res+bst);
  }
}