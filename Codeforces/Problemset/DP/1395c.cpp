#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=200;
const I M=200;
const I L=9;

I a_arr[N];
I b_arr[M];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<m;i++)cin>>b_arr[i];
  I res=(1<<L)-1;
  for(I i=L-1;i>=0;i--){
    res&=~(1<<i);
    for(I j=0;j<n;j++){
      B cur=0;
      for(I k=0;k<m;k++){
        I msk=a_arr[j]&b_arr[k];
        cur|=(res&msk)==msk;
      }
      if(!cur)res|=1<<i;
    }
  }
  printf("%i\n",res);
}