#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=50;
I ress[N][N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    I cur=1,dif=n*n-1;
    for(I i=0;i<n*n;i++){
      I x=i/n,y=i%n;
      if(x%2)y=n-1-y;
      ress[x][y]=cur;
      i%2?cur-=dif:cur+=dif;
      dif--;
    }
    for(I i=0;i<n;i++){
      for(I j=0;j<n;j++)printf("%i ",ress[i][j]);
      printf("\n");
    }
  }
}