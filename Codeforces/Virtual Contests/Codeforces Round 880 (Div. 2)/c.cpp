#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I A=6;
I pows[A+2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[1]=1;
  for(I i=2;i<=A+1;i++)pows[i]=pows[i-1]*10;
  I t;cin>>t;
  while(t--){
    I a,b,c;Lli k;cin>>a>>b>>c>>k,k--;
    if(c<max(a,b)||c>max(a,b)+1){printf("-1\n");continue;}
    Lli tot=0;B fnd=0;
    for(I i=pows[a];i<pows[a+1];i++){
      I low=max(pows[c],i+pows[b]),upp=min(pows[c+1],i+pows[b+1]),cur=upp-low;
      if(cur<=0)continue;
      if(tot+cur<=k){tot+=cur;continue;}
      I fin=low+k-tot;
      printf("%i + %i = %i\n",i,fin-i,fin),fnd=1;
      break;
    }
    if(!fnd)printf("-1\n");
  }
}