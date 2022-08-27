#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1e3;

I excs[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    excs[a]++,excs[b]++;
  }
  for(I i=0;i<n;i++){
    if(excs[i]==0){
      printf("%i\n",n-1);
      for(I j=0;j<n;j++)
        if(i!=j)printf("%i %i\n",i+1,j+1);
      break;
    }
  }
  return 0;
}