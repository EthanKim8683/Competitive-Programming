#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I N=100000;
Lf prbs[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,p;cin>>n>>p;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r;
    prbs[i]=(Lf)(r/p-(l-1)/p)/(r-l+1);
  }
  Lf res=0;
  for(I i=0;i<n;i++){
    Lf prb1=prbs[i],prb2=prbs[(i+1)%n];
    res+=prb1+prb2-prb1*prb2;
  }
  printf("%.7Lf\n",res*2000);
}