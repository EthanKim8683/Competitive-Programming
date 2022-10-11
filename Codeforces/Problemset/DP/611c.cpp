#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;

const I H=500;
const I W=500;

C cels[H][W+1];
I ps1[H+1][W+1];
I ps2[H+1][W+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I h,w;cin>>h>>w;
  for(I i=0;i<h;i++)cin>>cels[i];
  for(I i=0;i<h;i++)for(I j=0;j<w;j++){
    if(i+1<h)ps1[i+1][j+1]+=cels[i][j]=='.'&&cels[i+1][j]=='.';
    if(j+1<w)ps2[i+1][j+1]+=cels[i][j]=='.'&&cels[i][j+1]=='.';
  }
  for(I i=1;i<=h;i++)for(I j=1;j<=w;j++){
    ps1[i][j]+=ps1[i-1][j]+ps1[i][j-1]-ps1[i-1][j-1];
    ps2[i][j]+=ps2[i-1][j]+ps2[i][j-1]-ps2[i-1][j-1];
  }
  I q;cin>>q;
  while(q--){
    I r1,c1,r2,c2;cin>>r1>>c1>>r2>>c2,r1--,c1--;
    I res=0;
    res+=ps1[r2-1][c2]-ps1[r1][c2]-ps1[r2-1][c1]+ps1[r1][c1];
    res+=ps2[r2][c2-1]-ps2[r1][c2-1]-ps2[r2][c1]+ps2[r1][c1];
    printf("%i\n",res);
  }
}