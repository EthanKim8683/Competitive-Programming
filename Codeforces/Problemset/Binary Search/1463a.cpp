#include<bits/stdc++.h>

using namespace std;

using I=int;

const I A=1e8;
const I MAX=1e9;

I sum;

I fnd(){
  I l=0,r=A;
  while(l<=r){
    I m=l+(r-l)/2;
    I tot=9*m;
    if(tot==sum)return m;
    if(tot<sum)l=m+1;
    if(tot>sum)r=m-1;
  }
  return MAX;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I a,b,c;cin>>a>>b>>c;
    sum=a+b+c;
    printf("%s\n",fnd()>min(a,min(b,c))?"NO":"YES");
  }
}