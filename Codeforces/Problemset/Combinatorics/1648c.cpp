#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200000;
const I M=200000;
const I S=200000;
const Lli MOD=998244353;
Lli facs[N+1];
I s_arr[N];
I t_arr[M];
I cnts[S+1];
Lli fens[S+2];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
void upd(I i,Lli val){
  for(;i<=S+1;i+=i&-i)(fens[i]+=val)%=MOD;
}
Lli qry(I i){
  Lli res=0;
  for(;i>0;i-=i&-i)(res+=fens[i])%=MOD;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>s_arr[i];
  for(I i=0;i<m;i++)cin>>t_arr[i];
  for(I i=0;i<n;i++)cnts[s_arr[i]]++;
  Lli cur=1;
  for(I i=1;i<=S;i++)(cur*=inv(facs[cnts[i]]))%=MOD;
  for(I i=1;i<=S;i++)upd(i+1,cnts[i]);
  Lli res=n<m;
  for(I i=0;i<min(n,m);i++){
    I t=t_arr[i];
    (res+=facs[n-i-1]*cur%MOD*qry(t))%=MOD;
    if(cnts[t]==0){res-=n<m;break;}
    (cur*=cnts[t])%=MOD,upd(t+1,-1),cnts[t]--;
  }
  printf("%lli\n",(res+MOD)%MOD);
}
/*
at each index i we can count the number of ways to choose a letter in s smaller
than t[i] such that t[j] = s[j] for all j in [0, i)
*/