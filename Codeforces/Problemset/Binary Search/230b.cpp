#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I X=1e6;

B coms[X+1];
vector<I>prms;

I fnd(Lli x){
  I l=0,r=prms.size()-1;
  while(l<=r){
    I m=l+(r-l)/2;
    Lli prm=prms[m],sqr=prm*prm;
    if(sqr==x)return m;
    if(sqr>x)r=m-1;
    if(sqr<x)l=m+1;
  }
  return -1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  coms[0]=coms[1]=1;
  for(I i=2;i*i<=X;i++)if(!coms[i])for(I j=i*i;j<=X;j+=i)coms[j]=1;
  for(I i=0;i<=X;i++)if(!coms[i])prms.push_back(i);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    Lli x;cin>>x;
    printf("%s\n",fnd(x)==-1?"NO":"YES");
  }
}