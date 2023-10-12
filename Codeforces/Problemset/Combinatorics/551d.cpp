#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using Mat=array<array<Lli,2>,2>;
using Vec=array<Lli,2>;
Lli m;
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=m;y;y>>=1,(x*=x)%=m)if(y&1)(res*=x)%=m;
  return res;
}
Mat mul(Mat a,Mat b){
  Mat res{0};
  for(I i=0;i<2;i++)for(I j=0;j<2;j++)for(I k=0;k<2;k++)(res[i][j]+=a[i][k]*b[k][j])%=m;
  return res;
}
Mat mpw(Mat x,Lli y){
  Mat res{{{1,0},{0,1}}};
  for(;y;y>>=1,x=mul(x,x))if(y&1)res=mul(res,x);
  return res;
}
Vec mul(Mat a,Vec b){
  Vec res{0};
  for(I i=0;i<2;i++)for(I j=0;j<2;j++)(res[i]+=a[i][j]*b[j])%=m;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli n,k;I l;cin>>n>>k>>l>>m;
  if(l<64&&(k>>l)>=1)printf("0"),exit(0);
  Mat mat{{{1,1},{1,0}}};
  Vec vec{1,0};
  mat=mpw(mat,n),vec=mul(mat,vec);
  Lli y=(vec[0]+vec[1])%m,x=(mpw(2,n)-y)%m,z=__builtin_popcountll(k),w=l-z;
  printf("%lli\n",(mpw(x,z)*mpw(y,w)%m+m)%m);
}
/*
observe that the bits are independent, meaning we can use matrix exponentiation
dynamic programming to count the number of ways a bit in the expression will
be high or low

for a bit to be low, for any a[i], a[i + 1] must not share the bit with a[i],
so we can keep track of whether the previous bit is high or low and transition
from that

for x and y ways for high and low bits respectively and z and w high and low
bits in k, the number of arrays is x ^ z * y ^ w
*/