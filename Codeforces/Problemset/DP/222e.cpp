#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using C=char;
const I M=52;
using Mat=array<array<Lli,M>,M>;
const Lli MOD=1e9+7;
C lins[2+1];
I m;
Mat mul(Mat a,Mat b){
  Mat res={0};
  for(I i=0;i<m;i++)for(I j=0;j<m;j++)for(I k=0;k<m;k++)(res[i][j]+=a[i][k]*b[k][j])%=MOD;
  return res;
}
Mat mpw(Mat x,Lli y){
  Mat res={0};
  for(I i=0;i<m;i++)res[i][i]=1;
  for(;y;y>>=1,x=mul(x,x))if(y&1)res=mul(res,x);
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli n;I k;cin>>n>>m>>k;
  Mat trn={0};
  for(I i=0;i<m;i++)for(I j=0;j<m;j++)trn[i][j]=1;
  for(I i=0;i<k;i++){
    cin>>lins;
    C a=lins[0],b=lins[1];
    trn[a>='a'?a-'a':a-'A'+26][b>='a'?b-'a':b-'A'+26]=0;
  }
  Mat mat=mpw(trn,n-1);
  Lli res=0;
  for(I i=0;i<m;i++)for(I j=0;j<m;j++)(res+=mat[i][j])%=MOD;
  printf("%lli\n",res);
}