#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I SIZ=20;
I fens[N/SIZ+1];
I n;
void upd(I i,I val){
  for(;i<=(n+SIZ-1)/SIZ;i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
I ask(I l,I r){
  printf("? %i %i\n",l+1,r+1),fflush(stdout);
  I sum;cin>>sum;
  if(sum==-1)exit(0);
  return sum;
}
void ans(I x){
  printf("! %i\n",x+1),fflush(stdout);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>n>>t;
  I k;cin>>k,k--;
  for(I i=0;i<(n+SIZ-1)/SIZ;i++){
    I l=i*SIZ,r=min((i+1)*SIZ,n)-1;
    upd(i+1,r+1-l-ask(l,r));
  }
  for(I i=1;i<=t;i++){
    I l=0,r=(n+SIZ-1)/SIZ-1;
    while(l<r){
      I m=l+(r-l)/2;
      qry(m+1)>=k+1?r=m:l=m+1;
    }
    r=min((l+1)*SIZ,n)-1,l=l*SIZ;
    while(l<r){
      I m=l+(r-l)/2;
      m+1-ask(0,m)>=k+1?r=m:l=m+1;
    }
    ans(l),upd(l/SIZ+1,-1);
    if(i==t)break;
    cin>>k,k--;
  }
}