#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  I k;cin>>k;
  I a;cin>>a;
  I b;cin>>b;
  if(k==1)printf("%lli\n",(Lli)(n-1)*a),exit(0);
  Lli res=0;
  while(n!=1){
    if(n%k){
      I m=max(n-n%k,1);
      res+=(Lli)(n-m)*a;
      n=m;
    }else{
      I m=n/k;
      res+=min((Lli)(n-m)*a,(Lli)b);
      n=m;
    }
  }
  printf("%lli\n",res);
}