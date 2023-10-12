#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I L=3e5;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I a,b,c,l;cin>>a>>b>>c>>l;
  Lli res=(Lli)(l+1)*(l+2)*(l+3)/6;
  for(I i=0;i<=l;i++){
    auto exc=[&](I x,I y,I z){
      I low=x+y-z+i,cnt=i-max((low+(low>0))/2,0);
      if(cnt>=0)res-=(Lli)(cnt+1)*(cnt+2)/2;
    };
    exc(a,b,c),exc(a,c,b),exc(b,c,a);
  }
  printf("%lli\n",res);
}
/*
since, for a triangle to be degenerate, a >= b + c, b >= a + c or c >= a + b,
all mutually exclusive, need to be true

since they do not overlap, we can simply exclude those cases

for a + j >= b + c + i - j (and similar) to be true, where i denotes the total
centimeters used and j is the centimeters used by a, j >= (b + c - a + i) / 2
(and is, of course, bounded by i)
*/