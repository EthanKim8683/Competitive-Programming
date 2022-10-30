#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

I a_arr[N];
map<I,I>pres;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    pres.clear();
    Lli res=0;
    for(I i=0;i<n;i++){
      I val=a_arr[i]-i;
      res+=pres[val];
      pres[val]++;
    }
    printf("%lli\n",res);
  }
}