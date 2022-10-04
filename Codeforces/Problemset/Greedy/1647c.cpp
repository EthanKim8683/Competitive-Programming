#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;

const I N=100;
const I M=100;

C cels[N][M];
vector<tuple<I,I,I,I>>ress;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>cels[i];
    if(cels[0][0]!='0'){printf("-1\n");continue;}
    ress.clear();
    for(I i=0;i<n;i++)for(I j=0;j<m;j++)cels[i][j]=cels[i][j]=='1';
    for(I i=0;i<n;i++)for(I j=m-1;j-1>=0;j--)if(cels[i][j])
      ress.push_back({i,j-1,i,j});
    for(I i=n-1;i-1>=0;i--)if(cels[i][0])
      ress.push_back({i-1,0,i,0});
    printf("%i\n",ress.size());
    for(auto[i,j,k,l]:ress)printf("%i %i %i %i\n",i+1,j+1,k+1,l+1);
  }
}