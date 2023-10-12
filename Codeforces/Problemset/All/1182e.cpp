#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
template<I N>
using Mat=array<array<Lli,N>,N>;
template<I N>
using Vec=array<Lli,N>;
const Lli MOD=1e9+7;
Mat<3>mat1{{{{0,1,0}},{{0,0,1}},{{1,1,1}}}};
Mat<5>mat2{{{{0,1,0,0,0}},{{0,0,1,0,0}},{{1,1,1,1,0}},{{0,0,0,1,2}},{{0,0,0,0,1}}}};
template<I N>
Mat<N>mul(Mat<N>a,Mat<N>b){
  Mat<N>res={0};
  for(I i=0;i<N;i++)for(I j=0;j<N;j++)for(I k=0;k<N;k++)(res[i][j]+=a[i][k]*b[k][j])%=MOD-1;
  return res;
}
template<I N>
Vec<N>mul(Mat<N>a,Vec<N>b){
  Vec<N>res={0};
  for(I i=0;i<N;i++)for(I j=0;j<N;j++)(res[i]+=a[i][j]*b[j])%=MOD-1;
  return res;
}
template<I N>
Mat<N>mpw(Mat<N>x,Lli y){
  Mat<N>res={0};
  for(I i=0;i<N;i++)res[i][i]=1;
  for(;y;y>>=1,x=mul<N>(x,x))if(y&1)res=mul<N>(x,res);
  return res;
}
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
I main(){
  Lli n;I f1,f2,f3,c;cin>>n>>f1>>f2>>f3>>c;
  mat1=mpw<3>(mat1,n-3),mat2=mpw<5>(mat2,n-3);
  Vec<3>vec1={{1,0,0}},vec2={{0,1,0}},vec3={{0,0,1}};
  Vec<5>vec4={{0,0,0,2,1}};
  vec1=mul<3>(mat1,vec1),vec2=mul<3>(mat1,vec2),vec3=mul<3>(mat1,vec3),vec4=mul<5>(mat2,vec4);
  printf("%lli\n",mpw(f1,vec1[2])*mpw(f2,vec2[2])%MOD*mpw(f3,vec3[2])%MOD*mpw(c,vec4[2])%MOD);
}
/*
we can keep track of each term as the products of the contribution of f1, f2,
f3 and c, where contribution is the exponent of each factor

this can be done using matrix exponentiation
*/