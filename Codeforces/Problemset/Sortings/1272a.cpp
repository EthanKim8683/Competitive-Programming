#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
I poss[3];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    for(I i=0;i<3;i++)cin>>poss[i];
    sort(poss,poss+3);
    poss[0]=min(poss[0]+1,poss[2]);
    poss[2]=max(poss[2]-1,poss[0]);
    poss[1]=min(poss[1]+1,poss[2]);
    poss[1]=max(poss[1]-1,poss[0]);
    Lli res=0;
    res+=abs(poss[0]-poss[1]);
    res+=abs(poss[0]-poss[2]);
    res+=abs(poss[1]-poss[2]);
    printf("%lli\n",res);
  }
}