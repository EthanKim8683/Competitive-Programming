#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using Mat=array<array<Lli,100>,100>;
const I N=1e6;
const I M=100;
const Lli MOD=1e9+7;
I csts[3][N];
I maps[2][M];
Mat trns[2];
I m;
Mat mul(Mat a,Mat b){
  Mat res={0};
  for(I i=0;i<m;i++)for(I j=0;j<m;j++)for(I k=0;k<m;k++)(res[i][j]+=a[i][k]*b[k][j])%=MOD;
  return res;
}
Mat mpw(Mat x,I y){
  Mat res={0};
  for(I i=0;i<m;i++)res[i][i]=1;
  for(;y;y>>=1,x=mul(x,x))if(y&1)res=mul(res,x);
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,l;cin>>n>>l>>m;
  for(I i=0;i<3;i++)for(I j=0;j<n;j++)cin>>csts[i][j];
  for(I i=0;i<2;i++)for(I j=0;j<n;j++)maps[i][csts[i][j]%m]++;
  for(I i=0;i<m;i++)(trns[0][0][i]+=maps[0][i])%=MOD;
  for(I i=0;i<m;i++)for(I j=0;j<m;j++)(trns[1][i][(i+j)%m]+=maps[1][j])%=MOD;
  Mat trn={0};
  for(I i=0;i<m;i++)trn[i][i]=1;
  trn=mul(trn,trns[0]);
  trn=mul(trn,mpw(trns[1],l-2));
  Lli res=0;
  for(I i=0;i<n;i++)(res+=trn[0][((-csts[1][i]-csts[2][i])%m+m)%m])%=MOD;
  printf("%lli\n",res);
}