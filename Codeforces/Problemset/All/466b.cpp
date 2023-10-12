#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const Lli MAX=2e18;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli n,a,b;cin>>n>>a>>b;
  tuple<Lli,Lli,Lli>res={MAX,-1,-1};
  if(a*b>=6*n)res=min(res,{a*b,a,b});
  for(Lli i=a;i<=sqrt(6*n-1)+1;i++){
    Lli j=max((6*n+i-1)/i,b);
    res=min(res,{i*j,i,j});
  }
  for(Lli i=b;i<=sqrt(6*n-1)+1;i++){
    Lli j=max((6*n+i-1)/i,a);
    res=min(res,{i*j,j,i});
  }
  auto[s,x,y]=res;;
  printf("%lli\n%lli %lli",s,x,y);
}