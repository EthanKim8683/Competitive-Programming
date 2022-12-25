#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const Lli N=1e18;
Lli m;
Lli cnt(Lli x){
  Lli res=0;
  for(Lli i=2;i*i*i<=x;i++)res+=x/(i*i*i);
  return res;
}
Lli fnd(){
  Lli l=0,r=N;
  while(l<r){
    Lli t=l+(r-l)/2;
    cnt(t)>=m?r=t:l=t+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>m;
  Lli res=fnd();
  printf("%lli\n",cnt(res)==m?res:-1);
}