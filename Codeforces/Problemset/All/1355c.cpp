#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli a,b,c,d;cin>>a>>b>>c>>d;
  Lli res=0;
  for(Lli i=c;i<=d;i++){
    /*
    y=[min(max(i+1-x,b),c+1),c+1)
    i+1-x<b&&i+1-x<c+1   -> x=[max(max(i+1-b,i+1-(c+1))+1,a),b+1)   y=[b,c+1)
    i+1-x>=b&&i+1-x<c+1  -> x=[max(i+1-(c+1)+1,a),min(i+1-b+1,b+1)) y=[i+1-x,c+1)
    i+1-x>=b&&i+1-x>=c+1 -> x=[a,min(min(i+1-b,i+1-(c+1))+1,b+1))   y=[c+1,c+1)
    */
    Lli x0l=max(max(i+1-b,i+1-(c+1))+1,a),x0u=b+1;
    Lli y0l=(c+1)-b,y0u=(c+1)-b;
    Lli x1l=max(i+1-(c+1)+1,a),x1u=min(i+1-b+1,b+1);
    Lli y1l=(c+1)-(i+1-x1l),y1u=(c+1)-(i+1-(x1u-1));
    Lli x2l=a,x2u=min(min(i+1-b,i+1-(c+1))+1,b+1);
    Lli y2l=(c+1)-(c+1),y2u=(c+1)-(c+1);
    res+=max(x0u-x0l,0ll)*(y0l+y0u)/2;
    res+=max(x1u-x1l,0ll)*(y1l+y1u)/2;
    res+=max(x2u-x2l,0ll)*(y2l+y2u)/2;
  }
  printf("%lli\n",res);
}