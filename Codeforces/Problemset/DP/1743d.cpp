#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=1e6;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  s=s.substr(find(s.begin(),s.end(),'1')-s.begin());
  I j=find(s.begin(),s.end(),'0')-s.begin();
  S res=s;
  for(I i=0;i<=j;i++){
    S a=s,b=S(i,'0')+s.substr(0,n-i);
    for(I i=0;i<n;i++)if(b[i]=='1')a[i]='1';
    res=max(res,a);
  }
  printf("%s\n",res.size()?res.c_str():"0");
}