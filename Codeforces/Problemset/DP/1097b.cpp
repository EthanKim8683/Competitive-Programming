#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=15;

I a_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<(1<<n);i++){
    I tot=0;
    for(I j=0;j<n;j++)tot+=a_arr[j]*(i>>j&1?1:-1);
    if(tot%360==0)printf("YES"),exit(0);
  }
  printf("NO\n");
}