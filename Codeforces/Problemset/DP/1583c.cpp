#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I M=1e6;

vector<S>cels;
I ps[M+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  cels.resize(n);
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    I cnt=0;
    if(i-1>=0)cnt+=cels[i-1][j]=='X';
    if(j-1>=0)cnt+=cels[i][j-1]=='X';
    ps[j+1]+=cnt==2;
  }
  for(I i=0;i<m;i++)ps[i+1]+=ps[i];
  I q;cin>>q;
  while(q--){
    I x1,x2;cin>>x1>>x2;
    printf("%s\n",ps[x2]-ps[x1]?"NO":"YES");
  }
}