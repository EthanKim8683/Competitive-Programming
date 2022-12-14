#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using Lli=long long int;
const I N=1000;
const I M=1000;
C cels[N][M+1];
I cols[M];
I rows[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    if(cels[i][j]=='.')continue;
    cols[j]++,rows[i]++;
  }
  Lli res=0;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    if(cels[i][j]=='.')continue;
    res+=(cols[j]-1)*(rows[i]-1);
  }
  printf("%lli\n",res);
}