#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lf=long double;
using B=bool;

const I N=1e5;
const I X=2e8;

I x_arr[N];
I t_arr[N];
I n;

B chk(Lf m){
  Lf low=0,upp=X;
  for(I i=0;i<n;i++){
    I t=t_arr[i],x=x_arr[i];
    Lf rng=m-t;
    if(m<t)return 0;
    if(x-rng>upp)return 0;
    if(x+rng<low)return 0;
    low=max(low,x-rng);
    upp=min(upp,x+rng);
  }
  return 1;
}

Lf bld(Lf m){
  Lf low=0,upp=X;
  for(I i=0;i<n;i++){
    I t=t_arr[i],x=x_arr[i];
    Lf rng=m-t;
    low=max(low,x-rng);
    upp=min(upp,x+rng);
  }
  return low;
}

Lf fnd(){
  Lf l=0,r=X;
  for(I i=0;i<100;i++){
    Lf m=(l+r)/2;
    if(chk(m))r=m;
    else l=m;
  }
  return (l+r)/2;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)cin>>x_arr[i];
    for(I i=0;i<n;i++)cin>>t_arr[i];
    printf("%.7Lf\n",bld(fnd()));
  }
}