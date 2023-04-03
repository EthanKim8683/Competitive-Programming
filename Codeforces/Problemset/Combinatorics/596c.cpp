#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100000;
pair<I,I>pnts[N];
I w_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    pnts[i]={x,y};
  }
  for(I i=0;i<n;i++)cin>>w_arr[i];
}