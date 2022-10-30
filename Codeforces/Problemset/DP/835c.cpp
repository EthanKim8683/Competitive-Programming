#include<bits/stdc++.h>

using namespace std;

using I=int;

const I X=100;
const I Y=100;
const I C=10;

I ps[C+1][X+1][Y+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q,c;cin>>n>>q>>c,c++;
  for(I i=0;i<n;i++){
    I x,y,s;cin>>x>>y>>s,x--,y--;
    for(I j=0;j<c;j++)ps[j][x+1][y+1]+=(s+j)%c;
  }
  for(I i=0;i<c;i++)for(I j=1;j<=X;j++)for(I k=1;k<=Y;k++)
    ps[i][j][k]+=ps[i][j-1][k]+ps[i][j][k-1]-ps[i][j-1][k-1];
  while(q--){
    I t,x1,y1,x2,y2;cin>>t>>x1>>y1>>x2>>y2,t%=c,x1--,y1--;
    printf("%i\n",ps[t][x2][y2]-ps[t][x2][y1]-ps[t][x1][y2]+ps[t][x1][y1]);
  }
}