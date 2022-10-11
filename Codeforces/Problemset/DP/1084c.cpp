#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const I N=1e5;
const Lli MOD=1e9+7;

vector<I>grps;
Lli dp[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  for(I i=0;i<n;i++)if(s[i]=='a'){
    I cnt=1;
    while(++i<n&&s[i]!='b')cnt+=s[i]=='a';
    grps.push_back(cnt);
  }
  I m=grps.size();
  dp[0]=1;
  for(I i=0;i<m;i++)(dp[i+1]+=dp[i]*(grps[i]+1))%=MOD;
  printf("%lli\n",dp[m]-1);
}