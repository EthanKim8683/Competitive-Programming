#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=100;
Lli dp[N][N+1];
vector<I>inds[26];
Lli cnts[N+1];
Lli k;
void cmb(Lli&a,Lli b){
  a=min(a+b,k);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>k;
  S s;cin>>s;
  for(I i=0;i<n;i++)inds[s[i]-'a'].push_back(i);
  for(I i=0;i<26;i++)if(inds[i].size())dp[inds[i][0]][1]++;
  cnts[0]=1;
  for(I i=0;i<n;i++)for(I j=1;j<=n;j++){
    for(I k=0;k<26;k++){
      auto it=upper_bound(inds[k].begin(),inds[k].end(),i);
      if(it!=inds[k].end()&&j+1<=n)cmb(dp[*it][j+1],dp[i][j]);
    }
    cmb(cnts[j],dp[i][j]);
  }
  Lli rem=k,res=0;
  for(I i=n;i>=0;i--){
    Lli dif=min(rem,cnts[i]);
    rem-=dif,res+=dif*(n-i);
  }
  printf("%lli\n",rem?-1:res);
}