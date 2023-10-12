
#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I K=1e4;
const I LOGN=50;
const I P=13;
const Lli MOD=1e9+7;
vector<pair<Lli,I>>prms;
Lli invs[LOGN+2];
Lli dp[P][LOGN+1];
Lli res=0;
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
void dfs(I i=0,Lli con=1){
  if(i==prms.size()){(res+=con)%=MOD;return;}
  auto[prm,cnt]=prms[i];
  for(I j=0;j<=cnt;j++)dfs(i+1,con*dp[i][j]%MOD),(con*=prm)%=MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  for(I i=0;i<=LOGN+1;i++)invs[i]=inv(i);
  Lli n;I k;cin>>n>>k;
  for(Lli i=2;i*i<=n;i++)if(n%i==0){
    I cnt=0;
    for(;n%i==0;n/=i)cnt++;
    prms.push_back({i%MOD,cnt});
  }
  if(n>1)prms.push_back({n%MOD,1});
  for(I i=0;i<prms.size();i++){
    auto[prm,cnt]=prms[i];
    dp[i][cnt]=1;
    for(I j=0;j<k;j++){
      for(I l=0;l<=LOGN;l++)(dp[i][l]*=invs[l+1])%=MOD;
      for(I l=LOGN;l>0;l--)(dp[i][l-1]+=dp[i][l])%=MOD;
    }
  }
  dfs();
  printf("%lli\n",res);
}