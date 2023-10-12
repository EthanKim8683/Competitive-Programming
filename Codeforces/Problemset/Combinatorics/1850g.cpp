#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
map<I,I>cnts[4];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<4;i++)cnts[i].clear();
    for(I i=0;i<n;i++){
      I x,y;cin>>x>>y;
      cnts[0][x]++;
      cnts[1][y]++;
      cnts[2][x+y]++;
      cnts[3][x-y]++;
    }
    Lli res=0;
    for(I i=0;i<4;i++)for(auto[j,cnt]:cnts[i])res+=(Lli)cnt*(cnt-1);
    printf("%lli\n",res);
  }
}
/*
the points must lie on the same axis (N, E, NE, NW)
*/