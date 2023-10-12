#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100;
const I L=100;
const I MAX=1e9;
I l_arr[N];
I cnts[L];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>l_arr[i];
    fill_n(cnts,L,0);
    for(I i=0;i<n;i++)cnts[l_arr[i]]++;
    I pre=MAX;B vld=1;
    for(I i=0;i<L;i++){
      vld&=cnts[i]<=pre;
      pre=cnts[i];
    }
    printf("%s\n",vld?"YES":"NO");
  }
}