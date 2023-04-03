#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
I a_arr[N];
vector<Lli>vals;
map<I,Lli>rems;
priority_queue<pair<Lli,I>>ques;
Lli sgn(Lli x){
  return(x>0)-(x<0);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    rems.clear(),vals.clear();
    for(I i=0;i<n;i++){
      Lli a=a_arr[i];
      if(a==0)continue;
      if(vals.size()&&sgn(a)==sgn(vals.back()))vals.back()+=a;
      else vals.push_back(a);
    }
    I m=vals.size();
    for(I i=0;i<m;i++)rems[i]=abs(vals[i]);
    for(auto[i,val]:rems)ques.push({-val,i});
    Lli res=0;
    while(ques.size()){
      auto[val,i]=ques.top();ques.pop();
      if(!rems.count(i))continue;
      val=-val;
      if(val!=rems[i])continue;
      res=max(res,val);
      Lli sum=0;
      auto it=rems.upper_bound(i);
      if(it!=rems.end())sum+=it->second-val,rems.erase(it);
      it=rems.lower_bound(i);
      if(it--!=rems.begin())sum+=it->second-val,rems.erase(it);
      sum+=val;
      rems[i]=sum;
      if(sum>res)ques.push({-sum,i});
    }
    printf("%lli\n",res);
  }
}