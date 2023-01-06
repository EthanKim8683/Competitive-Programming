#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I X=1000;
B coms[X+1];
vector<I>ress;
B prm(I x){
  for(I i=2;i*i<=x;i++)if(x%i==0)return 0;
  return 1;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  coms[0]=coms[1]=1;
  for(I i=2;i*i<=X;i++)if(!coms[i])for(I j=i*i;j<=X;j+=i)coms[j]=1;
  I n;cin>>n;
  if(prm(n))printf("1\n%i",n),exit(0);
  I m=n-3;
  for(;m>2;m--)if(prm(m))break;
  ress.push_back(m);
  n-=m;
  for(I i=0;i<=n;i++)if(!coms[i]&&!coms[n-i]){
    ress.push_back(i);
    ress.push_back(n-i);
    break;
  }
  printf("%i\n",ress.size());
  for(auto res:ress)printf("%i ",res);
}