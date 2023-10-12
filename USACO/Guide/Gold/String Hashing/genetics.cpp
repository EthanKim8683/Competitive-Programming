#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using Lli=long long int;
const I N=4100;
const I M=4100;
const Lli MOD=(1ll<<31)-1;
const Lli BAS=(1ll<<17)-1;
C cpss[]="ACGT";
C seqs[N][M+1];
Lli hshs[4];
Lli cnts[N];
Lli pows[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  for(I i=0;i<n;i++)cin>>seqs[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)seqs[i][j]=lower_bound(cpss,cpss+4,seqs[i][j])-cpss;
  for(I i=0;i<m;i++){
    for(I j=0;j<4;j++){
      hshs[j]=0;
      for(I k=0;k<n;k++)hshs[j]=(hshs[j]*BAS+(seqs[k][i]==j))%MOD;
    }
    for(I j=0;j<n;j++)for(I k=0;k<4;k++)if(seqs[j][i]!=k)(cnts[j]+=hshs[k])%=MOD;
  }
  pows[0]=1;
  for(I i=1;i<n;i++)pows[i]=pows[i-1]*BAS%MOD;
  Lli tot=0;
  for(I i=0;i<n;i++)(tot+=pows[i])%=MOD;
  for(I i=0;i<n;i++)if(cnts[i]==(k*(tot-pows[n-1-i])%MOD+MOD)%MOD)printf("%i\n",i+1),exit(0);
}