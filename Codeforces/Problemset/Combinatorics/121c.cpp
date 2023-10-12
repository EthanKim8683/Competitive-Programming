#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I M=13;
const I L=10;
Lli facs[M+1];
set<I>rems;
vector<I>prms;
vector<I>dgts;
Lli dp[L+1][2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=M;i++)facs[i]=facs[i-1]*i;
  I n,k;cin>>n>>k,k--;
  if(n<=M&&k>=facs[n])printf("-1"),exit(0);
  for(I i=1;i<=M;i++)rems.insert(i+n-M);
  Lli cur=0;
  for(I i=0;i<M;i++)for(auto it=rems.begin();it!=rems.end();it++){
    if(cur+facs[M-1-i]>k){
      prms.push_back(*it);
      rems.erase(it);
      break;
    }
    cur+=facs[M-1-i];
  }
  Lli res=0;
  for(I i=n-M+1;i<=n;i++){
    I p=prms[i-(n-M+1)];
    if(p<=0)continue;
    B vld=1;
    for(I t=p;t;t/=10)vld&=t%10==4||t%10==7;
    for(I t=i;t;t/=10)vld&=t%10==4||t%10==7;
    res+=vld;
  }
  if(n-M>0){
    for(I t=n-M;t;t/=10)dgts.push_back(t%10);
    reverse(dgts.begin(),dgts.end());
    dp[0][1]=1;
    for(I i=0;i<dgts.size();i++){
      I upp=dgts[i];
      dp[i+1][0]+=2*dp[i][0];
      if(4<=upp)dp[i+1][4==upp]+=dp[i][1];
      if(7<=upp)dp[i+1][7==upp]+=dp[i][1];
      if(i>0)dp[i+1][0]+=2;
    }
    res+=dp[dgts.size()][0]+dp[dgts.size()][1];
  }
  printf("%lli\n",res);
}
/*
for each lucky position in [1, n], we can check if its value is also lucky

in addition, only up to the final 13 elements of the permutation will not equal
its index, since 12! is the greatest integer not exceeding 1e9

this means, we can find the final 13 elements of the kth permutation greedily
and do a complete search for lucky numbers in lucky positions

then, we can find all lucky numbers in [1, n - 13]
*/