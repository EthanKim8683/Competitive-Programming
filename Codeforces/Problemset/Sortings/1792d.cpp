#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=5e4;
const I M=10;
I a_arr[N][M];
I nods[N*M][M];
I invs[M];
I len;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>a_arr[i][j];
    for(I i=0;i<n*m;i++)for(I j=0;j<m;j++)nods[i][j]=-1;
    len=0;
    for(I i=0;i<n;i++){
      for(I j=0;j<m;j++)invs[a_arr[i][j]-1]=j;
      I t=0;
      for(I j=0;j<m;j++){
        I a=invs[j];
        if(nods[t][a]==-1)nods[t][a]=++len;
        t=nods[t][a];
      }
    }
    for(I i=0;i<n;i++){
      I cur=0,t=0;
      for(I j=0;j<m;j++){
        I a=a_arr[i][j]-1;
        if(nods[t][a]==-1)break;
        cur=j+1;
        t=nods[t][a];
      }
      printf("%i ",cur);
    }
    printf("\n");
  }
}