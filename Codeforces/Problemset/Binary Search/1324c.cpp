#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

vector<I>pnts;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    pnts.clear();
    for(I i=0;i<n;i++)if(s[i]=='R')pnts.push_back(i+1);
    pnts.push_back(n+1);
    I res=0,a=0;
    while(a<n){
      I b=*upper_bound(pnts.begin(),pnts.end(),a);
      res=max(res,b-a),a=b;
    }
    printf("%i\n",res);
  }
}