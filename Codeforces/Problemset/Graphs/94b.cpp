#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using B=bool;

const I N=5;

I inds[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b;
    inds[a-1]++,inds[b-1]++;
  }
  B res=false;
  for(I i=0;i<N;i++)
    res|=inds[i]!=2;
  if(res)printf("WIN\n");
  else printf("FAIL\n");
  return 0;
}