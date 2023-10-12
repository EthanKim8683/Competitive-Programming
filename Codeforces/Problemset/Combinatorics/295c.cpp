#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=50;
const Lli MOD=1e9+7;
const I MAX=1e9;
I wgts[N];
Lli facs[N+1];
pair<I,Lli>dp[N+1][N+1][2];
queue<tuple<I,I,I>>ques;
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  return facs[n]*inv(facs[k]*facs[n-k])%MOD;
}
B cmb(pair<I,Lli>&a,pair<I,Lli>b){
  if(b.first<a.first){a=b;return 1;}
  if(b.first==a.first)(a.second+=b.second)%=MOD;
  return 0;
};
void add(I x,I y,I z,I len,Lli cnt){
  if(cmb(dp[x][y][z],{len,cnt}))ques.push({x,y,z});
};
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*(N+1)*2,pair<I,Lli>{MAX,0});
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>wgts[i];
  I fif=0;
  for(I i=0;i<n;i++)fif+=wgts[i]==50;
  add(fif,n-fif,0,0,1);
  while(ques.size()){
    auto[x,y,z]=ques.front();ques.pop();
    auto[len,cnt]=dp[x][y][z];
    for(I i=0;i<=x;i++)for(I j=0;j<=y;j++)if(i+j>0){
      if(i*50+j*100>k)continue;
      add(fif-(x-i),n-fif-(y-j),!z,len+1,cnt*bin(x,i)%MOD*bin(y,j)%MOD);
    }
  }
  auto[len,cnt]=dp[fif][n-fif][1];
  printf("%i\n%lli",len==MAX?-1:len,cnt);
}
/*
we can use dynamic programming (with breadth-first search, since direction is
not always linear) storing by remaining number of 50 kilo people, 100 kilo
people and position of boat
*/