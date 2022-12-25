#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
using Lli=long long int;
const Lli MAX=1e18;
Lf clc(Lli h,Lli c,I x){
  return(Lf)(x/2*(h+c)+x%2*h)/x;
}
Lli fnd1(Lli h,Lli c,Lf t){
  Lli l=0,r=MAX;
  while(l<r){
    Lli m=l+(r-l+1)/2;
    if(clc(h,c,2*m+1)>=t)l=m;
    else r=m-1;
  }
  return 2*l+1;
}
Lli fnd2(Lli h,Lli c,Lf t){
  Lli l=0,r=MAX;
  while(l<r){
    Lli m=l+(r-l)/2;
    if(clc(h,c,2*m+1)<=t)r=m;
    else l=m+1;
  }
  return 2*l+1;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    Lli h,c;Lf t;cin>>h>>c>>t;
    Lli a=fnd1(h,c,t),b=fnd2(h,c,t);
    pair<Lf,Lli>res={abs(t-(Lf)(h+c)/2),2};
    res=min(res,{abs(t-clc(h,c,a)),a});
    res=min(res,{abs(t-clc(h,c,b)),b});
    printf("%lli\n",res.second);
  }
}