#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using B=bool;

const I N=1000;

B cons[N][N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  if(2*k>n-1){printf("-1\n");return 0;}
  printf("%i\n",n*k);
  for(I i=0;i<n;i++)for(I j=0,c=k;j<n&&c;j++)
    if(i!=j&&!cons[i][j]&&!cons[j][i]){
      cons[i][j]=cons[j][i]=true;
      printf("%i %i\n",i+1,j+1);
      c--;
    }
  return 0;
}