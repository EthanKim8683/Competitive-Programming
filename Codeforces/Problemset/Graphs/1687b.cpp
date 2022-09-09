#include<iostream>
#include<cstdio>
#include<numeric>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;
using C=char;

const I M=500;

I edgs[M];
I inds[M];
C ress[M];
I m;

I qry(I x){
  C t=ress[x];
  ress[x]='1';
  printf("? %s\n",ress);
  fflush(stdout);
  ress[x]=t;
  I res;cin>>res;
  return res;
}

B cmp(I a,I b){
  return edgs[a]<edgs[b];
}

I main(){
  I n;cin>>n>>m;
  for(I i=0;i<m;i++)ress[i]='0';
  for(I i=0;i<m;i++)edgs[i]=qry(i);
  iota(inds,inds+m,0);
  sort(inds,inds+m,cmp);
  I las=0;
  for(I i=0;i<m;i++){
    I a=inds[i];
    I cur=qry(a);
    if(cur-las==edgs[a])
      ress[a]='1',las=cur;
  }
  printf("! %i\n",las);
  return 0;
}