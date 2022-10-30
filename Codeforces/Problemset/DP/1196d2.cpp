#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using C=char;

const I N=2e5;
const I MAX=1e9;

C chrs[]="RGB";
I ps[3][3][N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    I n,k;cin>>n>>k;
    S s;cin>>s;
    for(I i=0;i<3;i++)for(I j=0;j<3;j++)for(I l=0;l<=n;l++)ps[i][j][l]=0;
    for(I i=0;i<n;i++)for(I j=0;j<3;j++)if(find(chrs,chrs+3,s[i])-chrs!=j)ps[j][i%3][i+1]=1;
    for(I i=0;i<3;i++)for(I j=0;j<3;j++)for(I l=0;l<n;l++)ps[i][j][l+1]+=ps[i][j][l];
    I res=MAX;
    for(I i=0;i+k<=n;i++)for(I j=0;j<3;j++){
      I cur=0;
      for(I l=0;l<3;l++)cur+=ps[l][(j+l)%3][i+k]-ps[l][(j+l)%3][i];
      res=min(res,cur);
    }
    printf("%i\n",res);
  }
}