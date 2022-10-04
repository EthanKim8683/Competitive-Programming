#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I X=20011;

B coms[X+1];
vector<I>prms;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  coms[0]=coms[1]=1;
  for(I i=2;i*i<=X;i++)if(!coms[i])
    for(I j=i*i;j<=X;j+=i)coms[j]=1;
  for(I i=0;i<=X;i++)if(!coms[i])
    prms.push_back(i);
  I t;cin>>t;
  while(t--){
    I d;cin>>d;
    I a=*lower_bound(prms.begin(),prms.end(),1+d);
    I b=*lower_bound(prms.begin(),prms.end(),a+d);
    printf("%lli\n",(Lli)a*b);
  }
}