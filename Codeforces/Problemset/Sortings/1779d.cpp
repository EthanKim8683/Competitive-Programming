#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I M=2e5;
I a_arr[N];
I b_arr[N];
I x_arr[M];
vector<I>stks;
multiset<I>rems;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)cin>>b_arr[i];
    I m;cin>>m;
    for(I i=0;i<m;i++)cin>>x_arr[i];
    B res=1;
    for(I i=0;i<n;i++)res&=a_arr[i]>=b_arr[i];
    rems.clear();
    for(I i=0;i<m;i++)rems.insert(x_arr[i]);
    stks.clear();
    for(I i=0;i<n;i++){
      I a=a_arr[i],b=b_arr[i];
      while(stks.size()&&stks.back()<b){
        auto it=rems.find(stks.back());
        if(it==rems.end())res=0;
        else rems.erase(it);
        stks.pop_back();
      }
      if((!stks.size()||stks.back()!=b)&&a!=b){
        stks.push_back(b);
      }
    }
    while(stks.size()){
      auto it=rems.find(stks.back());
      if(it==rems.end())res=0;
      else rems.erase(it);
      stks.pop_back();
    }
    printf("%s\n",res?"YES":"NO");
  }
}