#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I N=52;
C bufs[2+1];
I crds[N+3];
B dp[N][N+1][N+1][N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(crds,n+3,N);
  for(I i=0;i<n;i++){
    cin>>bufs;
    crds[i]=0;
    if(bufs[0]>='2'&&bufs[0]<='9')crds[i]+=bufs[0]-'2';
    if(bufs[0]=='T')crds[i]+=8;
    if(bufs[0]=='J')crds[i]+=9;
    if(bufs[0]=='Q')crds[i]+=10;
    if(bufs[0]=='K')crds[i]+=11;
    if(bufs[0]=='A')crds[i]+=12;
    if(bufs[1]=='S')crds[i]+=0*13;
    if(bufs[1]=='D')crds[i]+=1*13;
    if(bufs[1]=='H')crds[i]+=2*13;
    if(bufs[1]=='C')crds[i]+=3*13;
  }
  reverse(crds,crds+n);
  dp[0][crds[0]][crds[1]][crds[2]]=1;
  for(I i=0;i+1<n;i++)for(I j=0;j<N;j++)for(I k=0;k<=N;k++)for(I l=0;l<=N;l++){
    I c=crds[i+3];
    if(k!=N&&(j/13==k/13||j%13==k%13))dp[i+1][j][l][c]|=dp[i][j][k][l];
    if(c!=N&&(j/13==c/13||j%13==c%13))dp[i+1][k][l][j]|=dp[i][j][k][l];
  }
  B res=0;
  for(I i=0;i<N;i++)res|=dp[n-1][i][N][N];
  printf("%s\n",res?"YES":"NO");
}