#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=100;
Lli dp[N][3][3];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  if(s[0]=='A'){
    dp[0][1][1]=1;
    dp[0][0][0]=1;
  }
  if(s[0]=='B'){
    dp[0][2][2]=1;
    dp[0][1][1]=1;
  }
  for(I i=1;i<n;i++)for(I j=0;j<3;j++){
    if(s[i]=='A'){
      dp[i][j][1]+=dp[i-1][j][2];
      dp[i][j][0]+=dp[i-1][j][0];
      dp[i][j][0]+=dp[i-1][j][1];
    }
    if(s[i]=='B'){
      dp[i][j][2]+=dp[i-1][j][0];
      dp[i][j][2]+=dp[i-1][j][1];
      dp[i][j][1]+=dp[i-1][j][1];
    }
  }
  Lli res=0;
  if(s[0]=='A'){
    res+=dp[n-1][1][2];
    res+=dp[n-1][0][0];
    res+=dp[n-1][0][1];
  }
  if(s[0]=='B'){
    res+=dp[n-1][2][0];
    res+=dp[n-1][2][1];
    res+=dp[n-1][1][1];
  }
  printf("%lli\n",res);
}
/*
all (disjoint) AB in the original string become BA in the transformed string

this means that we can use dynamic programming to find the number of original
strings such that no AB remain untransformed

the following transitions will allow us to handle the cyclicity by keeping
track of the starting and ending state to only add valid transitions between
the two

if s[i] == A:
  At -> B
  A -> A
  B -> A
if s[i] == B:
  A -> At
  B -> At
  B -> B
*/