#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using Mat=array<array<Lli,2>,2>;
const Lli MOD=1e9+7;
Mat mul(Mat a,Mat b){
  Mat res={0};
  for(I i=0;i<2;i++)for(I j=0;j<2;j++)for(I k=0;k<2;k++)(res[i][j]+=a[i][k]*b[k][j])%=MOD;
  return res;
}
Mat mpw(Mat x,Lli y){
  Mat res={0};
  for(I i=0;i<2;i++)res[i][i]=1;
  for(;y;y>>=1,x=mul(x,x))if(y&1)res=mul(res,x);
  return res;
}
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>k;
  Mat num={array<Lli,2>{0,2},{1,1}};
  Lli den=2;
  for(I i=0;i<k;i++){
    Lli a;cin>>a;
    num=mpw(num,a),den=mpw(den,a);
  }
  Lli div=inv(2);
  printf("%lli/%lli",(num[0][0]*div)%MOD,(den*div)%MOD);
}