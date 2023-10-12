#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I LOGD=30;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I a,b,d;cin>>a>>b>>d;
    Lli shf=__builtin_ctz(d),t=d>>shf,res=0;
    for(I i=0;i<LOGD-shf;i++)if(~res>>i&1)res+=t<<i;
    res<<=shf;
    printf("%lli\n",(a|res)%d==0&&(b|res)%d==0?res:-1);
  }
}
/*
if we find the least multiple of d x such that all bits in [ctz(d), 30) are
positive, a | x and b | x will always be multiples of d as long as ctz(a) >=
ctz(d) and ctz(b) >= ctz(d) (there will be no solution in this case)
*/