#include<iostream>
#include<cstdio>
 
using namespace std;
 
using I=int;
using S=string;
using B=bool;
 
const I N=300000;
const I MAX=1e9;

B cons[N];
 
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S s;cin>>s;
    fill_n(cons,n,false);
    B l=true,r=true;
    for(auto c:s){
      l&=c=='-'||c=='>';
      r&=c=='-'||c=='<';
    }
    if(l||r){printf("%i\n",n);continue;}
    for(I i=0;i<n;i++){
      I a=i,b=(i+1)%n;
      if((s[a]=='-'&&s[b]=='<')||s[a]=='-')
        cons[a]=cons[b]=true;
    }
    I t=0;
    for(I i=0;i<n;i++)t+=cons[i];
    printf("%i\n",t);
  }
  return 0;
}