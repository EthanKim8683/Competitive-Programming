#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using C=char;

const I N=100;
const I MIN=-1e9;

I dp[N+1][N+1][N+1];
C pars[N+1][N+1][N+1];

I net(C a,C b){
  I res=0;
  res+=a=='R'&&b=='S';
  res+=a=='P'&&b=='R';
  res+=a=='S'&&b=='P';
  return res;
}

void add(I i,I j,I k,C a,C b){
  I l=j+(a=='R'),m=k+(a=='P');
  I res=dp[i][j][k]+net(a,b);
  if(res>dp[i+1][l][m]){
    dp[i+1][l][m]=res;
    pars[i+1][l][m]=a;
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    I a,b,c;cin>>a>>b>>c;
    S s;cin>>s;
    for(I i=0;i<=n;i++)for(I j=0;j<=i;j++)for(I k=0;k<=i-j;k++)
      dp[i][j][k]=MIN;
    dp[0][0][0]=0;
    for(I i=0;i<n;i++){
      C c=s[i];
      for(I j=0;j<=i;j++)for(I k=0;k<=i-j;k++)
        add(i,j,k,'R',c),add(i,j,k,'P',c),add(i,j,k,'S',c);
    }
    if(dp[n][a][b]<n/2+n%2){printf("NO\n");continue;}
    printf("YES\n");
    S res="";
    for(I i=n;i>0;i--){
      C p=pars[i][a][b];
      res=p+res,a-=p=='R',b-=p=='P';
    }
    printf("%s\n",res.c_str());
  }
}