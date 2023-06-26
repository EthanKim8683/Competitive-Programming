#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using Mat=array<array<Lli,100>,100>;
const I N=50000;
const I X=100;
const Lli MOD=1e9+7;
I a_arr[N];
I cnts[10];
Mat mul(Mat a,Mat b){
  Mat res={0};
  for(I i=0;i<X;i++)for(I j=0;j<X;j++)for(I k=0;k<X;k++)(res[i][j]+=a[i][k]*b[k][j])%=MOD;
  return res;
}
Mat mpw(Mat x,Lli y){
  Mat res={0};
  for(I i=0;i<X;i++)res[i][i]=1;
  for(;y;y>>=1,x=mul(x,x))if(y&1)res=mul(res,x);
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,b,k,x;cin>>n>>b>>k>>x;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cnts[a_arr[i]]++;
  Mat mat={0};
  for(I i=0;i<x;i++)for(I j=1;j<=9;j++)(mat[i][(i*10+j)%x]+=cnts[j])%=MOD;
  mat=mpw(mat,b);
  printf("%lli\n",mat[0][k]);
}