#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
const I Q=200000;
const I L=31;
I nods[Q*L+1][2];
I cnts[Q*L+1];
I cur=0;
void add(I x){
  for(I i=L-1,j=0;i>=0;i--){
    I c=x>>i&1;
    if(nods[j][c]==-1)j=nods[j][c]=++cur;
    else j=nods[j][c];
    cnts[j]++;
  }
}
void rem(I x){
  for(I i=L-1,j=0;i>=0;i--){
    I c=x>>i&1;
    j=nods[j][c];
    cnts[j]--;
  }
}
I qry(I x){
  I res=0;
  for(I i=L-1,j=0;i>=0;i--){
    I c=x>>i&1;
    if(nods[j][!c]!=-1&&cnts[nods[j][!c]]>0)j=nods[j][!c],res|=1<<i;
    else j=nods[j][c];
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&nods[0][0],&nods[0][0]+(Q*L+1)*2,-1);
  add(0);
  I q;cin>>q;
  while(q--){
    C c;I x;cin>>c>>x;
    if(c=='+')add(x);
    if(c=='-')rem(x);
    if(c=='?')printf("%i\n",qry(x));
  }
}