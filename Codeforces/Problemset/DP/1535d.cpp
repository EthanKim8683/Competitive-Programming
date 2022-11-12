#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using C=char;

const I K=18;

I dp[1<<K][2];
S s;

void upd(I i){
  for(;i>0;i>>=1){
    C c=s[i-1];
    if(c=='0')dp[i>>1][i&1]=dp[i][1];
    if(c=='1')dp[i>>1][i&1]=dp[i][0];
    if(c=='?')dp[i>>1][i&1]=dp[i][1]+dp[i][0];
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>k;
  cin>>s;
  I n=s.size();
  reverse(s.begin(),s.end());
  for(I i=(1<<(k-1));i<(1<<k);i++)dp[i][0]=dp[i][1]=1;
  for(I i=(1<<k)-1;i>0;i--)upd(i);
  I q;cin>>q;
  while(q--){
    I p;C c;cin>>p>>c,p=n-p;
    s[p]=c,upd(p+1);
    printf("%i\n",dp[0][1]);
  }
}