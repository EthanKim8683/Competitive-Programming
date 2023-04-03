#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
const I L=20;
I dp[3][1<<L];
vector<I>dgts;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I l,q;cin>>l>>q;
  S s;cin>>s;
  for(I i=0;i<(1<<l);i++)for(I j=0;j<3;j++)dp[j][i]=s[i]-'0';
  for(I i=1;i<=l;i++)for(I j=0;j<(1<<l);j+=1<<i)for(I k=0;k<(1<<(i-1));k++){
    dp[0][j+k+(1<<(i-1))]+=dp[0][j+k];
    dp[1][j+k]+=dp[1][j+k+(1<<(i-1))];
  }
  for(I i=0;i<q;i++){
    S t;cin>>t;
    I cnt1=0,cnt2=0,cnt3=0;
    for(auto c:t)cnt1+=c=='1',cnt2+=c=='0',cnt3+=c=='?';
    C x,y,z;I typ;
    if(cnt1<=cnt2&&cnt1<=cnt3)x='1',y='0',z='?',typ=0;
    if(cnt2<=cnt1&&cnt2<=cnt3)x='0',y='?',z='1',typ=1;
    if(cnt3<=cnt1&&cnt3<=cnt2)x='?',y='0',z='1',typ=2;
    dgts.clear();
    I res=0,idx=0;
    for(I j=0;j<l;j++){
      if(t[l-1-j]==x)dgts.push_back(1<<j);
      if(t[l-1-j]==y)idx|=0<<j;
      if(t[l-1-j]==z)idx|=1<<j;
    }
    res+=dp[typ][idx];
    for(I j=1;j<(1<<dgts.size());j++){
      for(I k=(j-1)^j;k;k-=k&-k)idx^=dgts[__builtin_ctz(k)];
      res+=dp[typ][idx]*(typ==2?1:1-__builtin_popcount(j)%2*2);
    }
    printf("%i\n",abs(res));
  }
}