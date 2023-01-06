#include<bits/stdc++.h>
using namespace std;
using I=int;
const I L=31;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m,m++;
    I res=0;
    for(I i=L-1;i>=0;i--){
      I hlf=1<<i,low=min(m,hlf),upp=max(m-hlf,0);
      if(n>>i&1)swap(low,upp);
      if(low==hlf)res+=hlf,m=upp;
      else m=low;
    }
    printf("%i\n",res);
  }
}