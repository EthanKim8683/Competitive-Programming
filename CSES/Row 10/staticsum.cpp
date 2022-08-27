#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

I x_arr[N];
Lli ps[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  for(I i=0;i<n;i++)ps[i+1]=ps[i]+x_arr[i];
  while(q--){
    I a,b;cin>>a>>b;
    printf("%lli\n",ps[b]-ps[a-1]);
  }
  return 0;
}