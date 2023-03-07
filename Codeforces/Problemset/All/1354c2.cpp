#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I X=32;
const Lf PI=3.141592653589793238462643383279l;
I n;
Lf wdt(Lf r){
  Lf res=0;
  for(I i=0;i<n;i++)res+=abs(cos(PI*(i+r)/n));
  return res;
}
Lf hgt(Lf r){
  Lf res=0;
  for(I i=0;i<n;i++)res+=abs(sin(PI*(i+r)/n));
  return res;
}
Lf fnd(){
  Lf l=0,r=1;
  for(I i=0;i<X;i++){
    Lf m=(l+r)/2;
    wdt(m)>hgt(m)?l=m:r=m;
  }
  return(l+r)/2;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    Lf res=fnd();
    printf("%.9Lf\n",max(wdt(res),hgt(res)));
  }
}