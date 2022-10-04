#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I K=4e5;

Lli x_arr[K];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<k;i++)cin>>x_arr[i];
    for(I i=0;i<k;i++)x_arr[i]=n-x_arr[i];
    sort(x_arr,x_arr+k);
    for(I i=0;i+1<k;i++)x_arr[i+1]+=x_arr[i];
    printf("%i\n",lower_bound(x_arr,x_arr+k,n)-x_arr);
  }
}