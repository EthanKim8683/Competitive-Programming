#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I K=1e5;
const I N=100;

B adjs[N][N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>k;
  I tot=0;
  for(I i=0;i<N;i++){
    for(I j=0;j<i;j++){
      I cur=0;
      for(I k=0;k<N;k++){
        if(k==i||k==j)continue;
        cur+=adjs[i][k]&&adjs[j][k];
      }
      if(tot+cur<=k){
        adjs[i][j]=adjs[j][i]=true;
        tot+=cur;
      }
    }
  }
  printf("%i\n",N);
  for(I i=0;i<N;i++){
    for(I j=0;j<N;j++)
      printf("%i",adjs[i][j]);
    printf("\n");
  }
  return 0;
}