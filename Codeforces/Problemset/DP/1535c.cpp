#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    I l=0,lst0=-1,lst1=-1;
    Lli res=0;
    for(I i=0;i<n;i++){
      if(s[i]=='0'){
        if((i-lst0)%2==1)l=max(l,lst0+1);
        if((i-lst1)%2==0)l=max(l,lst1+1);
        lst0=i;
      }
      if(s[i]=='1'){
        if((i-lst1)%2==1)l=max(l,lst1+1);
        if((i-lst0)%2==0)l=max(l,lst0+1);
        lst1=i;
      }
      res+=i-l+1;
    }
    printf("%lli\n",res);
  }
}