#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I LOGK=30;
I ancs[N][LOGK];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=0;i<n;i++){
    I t;cin>>t,t--;
    ancs[i][0]=t;
  }
  for(I i=1;i<LOGK;i++)for(I j=0;j<n;j++)ancs[j][i]=ancs[ancs[j][i-1]][i-1];
  while(q--){
    I x,k;cin>>x>>k,x--;
    for(I i=0;i<LOGK;i++)if(k>>i&1)x=ancs[x][i];
    printf("%i\n",x+1);
  }
}