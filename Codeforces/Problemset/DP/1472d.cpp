#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

I a_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n,greater<I>());
    Lli tot=0;
    for(I i=0;i<n;i++)if(a_arr[i]%2==i%2)tot+=a_arr[i]*(i%2?-1:1);
    if(tot==0)printf("Tie\n");
    if(tot>0)printf("Alice\n");
    if(tot<0)printf("Bob\n");
  }
}