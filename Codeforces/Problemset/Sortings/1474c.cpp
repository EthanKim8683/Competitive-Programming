#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1000;
I a_arr[2*N];
multiset<I>rems;
vector<pair<I,I>>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<2*n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+2*n);
    B vld=0;
    for(I i=0;i<2*n-1;i++){
      ress.clear(),rems.clear();
      for(I j=0;j<2*n-1;j++)if(j!=i)rems.insert(a_arr[j]);
      I x=a_arr[2*n-1];
      ress.push_back({a_arr[i],x});
      while(rems.size()){
        I y=*rems.rbegin();
        rems.erase(rems.find(y));
        auto it=rems.find(x-y);
        if(it==rems.end())break;
        ress.push_back({*it,y});
        rems.erase(it);
        x=y;
      }
      if(ress.size()==n){
        printf("YES\n");
        printf("%i\n",a_arr[2*n-1]+a_arr[i]);
        for(auto[x,y]:ress)printf("%i %i\n",x,y);
        vld=1;
        break;
      }
    }
    if(!vld)printf("NO\n");
  }
}