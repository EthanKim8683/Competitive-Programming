#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
const I N=1<<16;
I xors[N];
I invs[N];
I ress[N];
I n;
I ask(S s,I i,I j){
  printf("%s %i %i\n",s.c_str(),i+1,j+1),fflush(stdout);
  I res;cin>>res;
  if(res==-1)exit(0);
  return res;
}
void ans(){
  printf("! ");
  for(I i=0;i<n;i++)printf("%i ",ress[i]);
  printf("\n"),fflush(stdout);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=1;i<n;i++)xors[i]=ask("XOR",0,i);
  fill_n(invs,n,-1);
  B fnd=0;
  for(I i=0;i<n&&!fnd;i++){
    I b=xors[i],j=invs[b];
    if(j!=-1)ress[0]=ask("AND",i,j)^xors[i],fnd=1;
    invs[b]=i;
  }
  if(!fnd){
    I i=find(xors,xors+n,n-1)-xors,j=1+(i==1);
    ress[0]=xors[j]^(ask("AND",0,j)|ask("AND",i,j));
  }
  for(I i=1;i<n;i++)ress[i]=ress[0]^xors[i];
  ans();
}
/*
after xor querying all a[0] ^ a[i], where i in [1, n - 1], the results can
be split into one of two possibilites:

two or more query results are equal or a query results in 0, meaning two of
such indices can be and queried to get their exact value, which can then be
used to find the remaining values

no query results are equal, meaning all values are distinct, exactly one
index i's query result will equal n - 1, representing the inverse of a[0]

if we and query pairs i, j and 0, j, we get disjoint pieces of a[j], which
can be or'ed to produce the exact value of a[j], upon which we can solve the
remaining values
*/