#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I L=63;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    Lli n,x;cin>>n>>x;
    Lli m=n;
    for(I i=0;i<L;i++){
      I a=n>>i&1,b=x>>i&1;
      if(a!=b)m=max(m,((n>>i)+1)<<i);
    }
    B zer=0,vld=1;
    for(I i=L-1;i>=0;i--){
      I a=n>>i&1,b=m>>i&1,c=x>>i&1;
      if(a!=b)zer=1;
      if(zer)a=0;
      vld&=a==c;
    }
    if(!vld){printf("-1\n");continue;}
    printf("%lli\n",m);
  }
}