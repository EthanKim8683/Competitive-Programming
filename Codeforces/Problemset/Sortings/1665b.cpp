#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
const I MAX=1e9;
I a_arr[N];
map<I,I>cnts;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    cnts.clear();
    for(I i=0;i<n;i++)cnts[a_arr[i]]++;
    I res=MAX;
    for(auto[a,cnt]:cnts){
      I rem=n-cnt,cur=0;
      while(rem>0){
        I dif=min(rem,cnt);
        cur+=dif+1,rem-=dif,cnt*=2;
      }
      res=min(res,cur);
    }
    printf("%i\n",res);
  }
}