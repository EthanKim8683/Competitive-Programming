#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
using S=string;
const I N=1e5;
const Lli MAX=1e18;
I x,y;
B chk(I a,Lli m){
  return m/x+m/y>=a;
}
Lli fnd(I a){
  Lli l=0,r=MAX;
  while(l<r){
    Lli m=l+(r-l)/2;
    chk(a,m)?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>x>>y;
  for(I i=0;i<n;i++){
    I a;cin>>a;
    Lli m=fnd(a);
    printf("%s\n",(S[]){"","Vanya","Vova","Both"}[(m%y==0)+(m%x==0)*2].c_str());
  }
}