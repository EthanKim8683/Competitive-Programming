#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;
const I M=1e5;

I a_arr[N];
I ps[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)ps[i+1]=a_arr[i];
  for(I i=0;i<n;i++)ps[i+1]+=ps[i];
  I m;cin>>m;
  while(m--){
    I q;cin>>q;
    printf("%i\n",upper_bound(ps,ps+n,q-1)-1-ps+1);
  }
}