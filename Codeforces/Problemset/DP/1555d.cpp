#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=2e5;
const I MAX=1e9;

I ps[3][3][N+1];
I prms[3];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  S s;cin>>s;
  for(I i=0;i<n;i++)for(I j=0;j<3;j++)if(j!=s[i]-'a')ps[j][i%3][i+1]++;
  for(I i=0;i<3;i++)for(I j=0;j<3;j++)for(I k=0;k<n;k++)ps[i][j][k+1]+=ps[i][j][k];
  while(m--){
    I l,r;cin>>l>>r,l--;
    I res=MAX;
    iota(prms,prms+3,0);
    do{
      I cur=0;
      for(I i=0;i<3;i++)cur+=ps[i][prms[i]][r]-ps[i][prms[i]][l];
      res=min(res,cur);
    }while(next_permutation(prms,prms+3));
    printf("%i\n",res);
  }
}