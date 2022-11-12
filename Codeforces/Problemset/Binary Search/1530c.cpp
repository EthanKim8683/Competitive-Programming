#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I N=1e5;

I a_arr[N];
I b_arr[N];
Lli ps1[N+1];
Lli ps2[N+1];
I n;

B chk(I k){
  I x=k-k/4,y=min(k-n,x);
  return 100*y+ps1[x-y]>=ps2[min(x,n)];
}

I fnd(){
  I l=n,r=2*n;
  while(l<r){
    I m=l+(r-l)/2;
    if(chk(m))r=m;
    else l=m+1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)cin>>b_arr[i];
    sort(a_arr,a_arr+n,greater<I>());
    sort(b_arr,b_arr+n,greater<I>());
    for(I i=0;i<n;i++)ps1[i+1]=a_arr[i];
    for(I i=0;i<n;i++)ps2[i+1]=b_arr[i];
    for(I i=0;i<n;i++)ps1[i+1]+=ps1[i];
    for(I i=0;i<n;i++)ps2[i+1]+=ps2[i];
    printf("%i\n",fnd()-n);
  }
}