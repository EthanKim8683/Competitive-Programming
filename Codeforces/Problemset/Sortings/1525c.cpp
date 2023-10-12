#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I N=3e5;
const I MAX=1e9;
const I MIN=-MAX;
I x_arr[N];
C dirs[N];
vector<I>flts[2];
map<I,I>rgts;
vector<pair<I,I>>lfts;
I ress[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>x_arr[i];
    for(I i=0;i<n;i++)cin>>dirs[i];
    for(I i=0;i<2;i++)flts[i].clear();
    for(I i=0;i<n;i++)flts[x_arr[i]%2].push_back(i);
    fill_n(ress,n,-1);
    for(I i=0;i<2;i++){
      lfts.clear(),rgts.clear();
      for(auto j:flts[i]){
        I x=x_arr[j],dir=dirs[j];
        if(dir=='R')rgts.insert({x,j});
        if(dir=='L')lfts.push_back({x,j});
      }
      sort(lfts.begin(),lfts.end());
      for(auto[x,j]:lfts){
        auto it=rgts.lower_bound(x);
        if(it==rgts.begin())continue;
        auto[y,k]=*--it;rgts.erase(it);
        ress[j]=ress[k]=(x-y)/2;
      }
      lfts.clear(),rgts.clear();
      for(auto j:flts[i])if(ress[j]==-1){
        I x=x_arr[j],dir=dirs[j];
        if(dir!='L')continue;
        rgts.insert({-x,j});
        lfts.push_back({x,j});
      }
      sort(lfts.begin(),lfts.end());
      for(auto[x,j]:lfts){
        auto it=rgts.lower_bound(x);
        while(it!=rgts.begin()){
          auto[y,k]=*--it;
          if(j==k)continue;
          ress[j]=ress[k]=(x-y)/2;
          rgts.erase(it);break;
        }
      }
      lfts.clear(),rgts.clear();
      for(auto j:flts[i])if(ress[j]==-1){
        I x=x_arr[j],dir=dirs[j];
        if(dir!='R')continue;
        rgts.insert({x,j});
        lfts.push_back({2*m-x,j});
      }
      sort(lfts.begin(),lfts.end());
      for(auto[x,j]:lfts){
        auto it=rgts.lower_bound(x);
        while(it!=rgts.begin()){
          auto[y,k]=*--it;
          if(j==k)continue;
          ress[j]=ress[k]=(x-y)/2;
          rgts.erase(it);break;
        }
      }
      lfts.clear(),rgts.clear();
      for(auto j:flts[i])if(ress[j]==-1){
        I x=x_arr[j],dir=dirs[j];
        if(dir=='L')rgts.insert({-x,j});
        if(dir=='R')lfts.push_back({2*m-x,j});
      }
      sort(lfts.begin(),lfts.end());
      for(auto[x,j]:lfts){
        auto it=rgts.lower_bound(x);
        if(it==rgts.begin())continue;
        auto[y,k]=*--it;rgts.erase(it);
        ress[j]=ress[k]=(x-y)/2;
      }
    }
    for(I i=0;i<n;i++)printf("%i ",ress[i]);
    printf("\n");
  }
}