#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using S=string;

const I L=1e5;
const Lli MOD=1e9+7;

Lli dp1[L+1][3];
Lli dp2[L+1][3];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S n;cin>>n;
  I l=n.size();
  dp1[0][0]=1;
  for(I i=0;i<l;i++){
    (dp1[i+1][0]+=dp1[i][0])%=MOD;
    (dp1[i+1][1]+=dp1[i][1])%=MOD;
    (dp1[i+1][2]+=dp1[i][2])%=MOD;
    (dp1[i+1][1]+=dp1[i][0])%=MOD;
    (dp1[i+1][2]+=dp1[i][1])%=MOD;
  }
  for(I i=0;i<l;i++){
    Lli d=n[i]-'0';
    (dp2[i+1][0]+=dp2[i][0]*10+d*dp1[i][0])%=MOD;
    (dp2[i+1][1]+=dp2[i][1])%=MOD;
    (dp2[i+1][2]+=dp2[i][2]*10+d*dp1[i][2])%=MOD;
    (dp2[i+1][1]+=dp2[i][0])%=MOD;
    (dp2[i+1][2]+=dp2[i][1]*10+d*dp1[i][1])%=MOD;
  }
  printf("%lli\n",(dp2[l][2]+dp2[l][1])%MOD);
}