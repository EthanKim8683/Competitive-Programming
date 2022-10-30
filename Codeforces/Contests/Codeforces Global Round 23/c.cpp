#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

I a_arr[N];
I ress[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)ress[n-a_arr[i]]=i;
    for(I i=0;i<n;i++)printf("%i ",ress[i]+1);
    printf("\n");
  }
}