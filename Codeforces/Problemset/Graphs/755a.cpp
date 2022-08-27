#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using B=bool;

const I N=1e3;
const I M=1e3;

B coms[N*M+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  coms[0]=coms[1]=true;
  for(I i=2;i*i<=N*M;i++)
    if(!coms[i])for(I j=i*i;j<=N*M;j+=i)
      coms[j]=true;
  I n;cin>>n;
  for(I i=1;i<=M;i++)if(coms[n*i+1]){
    printf("%i\n",i);
    break;
  }
  return 0;
}