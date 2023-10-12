#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100000;
const I A=100000;
const Lli MOD=1e9+7;
I a_arr[N];
Lli pows[N+1];
I cnts[A+1];
Lli dp[A+1];
I facs[A+1];
map<I,I>cnts1;
vector<pair<I,I>>cnts2;
void dfs(I i=0,I val=1){
  if(i==cnts2.size()){
    cnts[val]++;
    return;
  }
  auto[prm,cnt]=cnts2[i];
  for(I j=0;j<=cnt;j++)dfs(i+1,val),val*=prm;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  iota(facs,facs+A+1,0);
  for(I i=2;i*i<=A;i++)for(I j=i*i;j<=A;j+=i)facs[j]=facs[i];
  pows[0]=1;
  for(I i=1;i<=N;i++)pows[i]=pows[i-1]*2%MOD;
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++){
    cnts1.clear();
    for(I j=a_arr[i];j>1;j/=facs[j])cnts1[facs[j]]++;
    cnts2.assign(cnts1.begin(),cnts1.end());
    dfs();
  }
  for(I i=A;i>=1;i--){
    dp[i]=pows[cnts[i]]-1;
    for(I j=2*i;j<=A;j+=i)(dp[i]-=dp[j])%=MOD;
  }
  printf("%lli\n",(dp[1]+MOD)%MOD);
}
/*
we can count how many times each divisor is represented among all elements
and then use dynamic programming to count the subsequences for which a divisor
is the greatest common divisor

the number of ways dp[d] a divisor d is the greatest common divisor of a
subsequence is 2 ^ cnts[d] - 1, the number of non-empty subsequences whose
greatest common divisor is a multiple of d, minus dp[m * d] for all m > 1,
representing the number subsequences for which the greatest common divisor is a
multiple of d greater than d
*/