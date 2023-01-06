#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
vector<Lli>facs;
Lli gcd(Lli a,Lli b){
  return b?gcd(b,a%b):a;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    Lli a,m;cin>>a>>m;
    Lli div=gcd(a,m);
    a/=div,m/=div;
    facs.clear();
    Lli t=m;
    for(Lli i=2;i*i<=t;i++){
      if(t%i==0){
        facs.push_back(i);
        while(t%i==0)t/=i;
      }
    }
    if(t>1)facs.push_back(t);
    I n=facs.size();
    Lli res=0;
    for(I i=0;i<(1<<n);i++){
      Lli mul=1;
      for(I j=0;j<n;j++)if(i>>j&1)mul*=facs[j];
      Lli cur=(a+m-1)/mul-(a-1)/mul;
      __builtin_popcount(i)%2?res-=cur:res+=cur;
    }
    printf("%lli\n",res);
  }
}