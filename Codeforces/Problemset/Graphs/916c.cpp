#include<iostream>
#include<cstdio>
#include<vector>
#include<tuple>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I MAX=1e9;

B coms[2*N+1];
vector<tuple<I,I,I>>ress;

I main(){
  coms[0]=coms[1]=true;
  for(I i=2;i*i<=2*N;i++)
    if(!coms[i])for(I j=i*i;j<=2*N;j+=i)
      coms[j]=true;
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  I prm;
  for(I i=n;i<=2*n;i++)
    if(!coms[i]){prm=i;break;}
  I cur=prm-(n-1);
  for(I i=1;i<n;i++){
    I len;
    if(i==n-1)len=2;
    else len=cur,cur=1;
    ress.push_back({0,i,len});
  }
  for(I i=1;i<n&&ress.size()<m;i++)
    for(I j=i+1;j<n&&ress.size()<m;j++)
      ress.push_back({i,j,MAX});
  printf("%i %i\n",2,prm);
  for(auto[i,j,d]:ress)
    printf("%i %i %i\n",i+1,j+1,d);
  return 0;
}