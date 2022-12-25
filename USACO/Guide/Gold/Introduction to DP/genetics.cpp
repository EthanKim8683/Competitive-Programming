#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;
using C=char;

const I N=1000;
const Lli MOD=1e9+7;

C chrs[]="GCAT?";
Lli dp1[N][N][4][4];
Lli dp2[N];

I tod(C c){
  return find(chrs,chrs+5,c)-chrs;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  for(I i=0;i<n;i++){
    I c=tod(s[i]);
    if(c==4){for(I j=0;j<4;j++)
      dp1[i][i][j][j]+=1;
    }else
      dp1[i][i][c][c]+=1;
    for(I j=i+1;j<n;j++){
      I c=tod(s[j]);
      for(I k=0;k<4;k++){
        for(I l=0;l<4;l++){
          if(c==4){for(I m=0;m<4;m++)
            if(m!=k)dp1[i][j][k][m]+=dp1[i][j-1][k][l];
          }else
            if(c!=k)dp1[i][j][k][c]+=dp1[i][j-1][k][l];
        }
      }
    }
  }
  /*
  The USACO explanation is so fucking hard to understand
  it's been like 4 hours and I still haven't figured out
  what the fuck they're trying to tell me to do.
  */
  return 0;
}