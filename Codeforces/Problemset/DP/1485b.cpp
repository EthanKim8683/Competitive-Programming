#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;

I a_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q,k;cin>>n>>q>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  while(q--){
    I l,r;cin>>l>>r,l--,r--;
    printf("%i\n",k+a_arr[r]-a_arr[l]-2*(r-l)-1);
  }
}