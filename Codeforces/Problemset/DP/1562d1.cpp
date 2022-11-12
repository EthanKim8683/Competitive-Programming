#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;

const I N=3e5;

C syms[N+1];
I ps[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,q;cin>>n>>q;
    cin>>syms;
    fill_n(ps,n+1,0);
    for(I i=0;i<n;i++)ps[i+1]=1-2*((syms[i]=='+')^(i%2));
    for(I i=0;i<n;i++)ps[i+1]+=ps[i];
    while(q--){
      I l,r;cin>>l>>r;
      I sum=ps[r]-ps[l-1];
      if(sum%2)printf("1\n");
      else printf("%i\n",sum==0?0:2);
    }
  }
}