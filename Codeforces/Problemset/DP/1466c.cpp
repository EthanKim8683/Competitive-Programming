#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=1e5;

B viss[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    I res=0;
    for(I i=0;i<n;i++){
      B cur=0;
      cur|=i-1>=0&&s[i-1]==s[i]&&!viss[i-1];
      cur|=i-2>=0&&s[i-2]==s[i]&&!viss[i-2];
      viss[i]=cur;
      res+=cur;
    }
    printf("%i\n",res);
  }
}