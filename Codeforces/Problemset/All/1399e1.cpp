#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
Lli w_arr[N-1];
vector<pair<I,I>>adjs[N];
Lli cnts[N-1];
priority_queue<pair<Lli,I>>ques;
Lli dfs(I a,I p=-1){
  Lli cnt=adjs[a].size()==1;
  for(auto[b,i]:adjs[a])if(b!=p){
    Lli cur=dfs(b,a);
    cnts[i]=cur,cnt+=cur;
  }
  return cnt;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;Lli s;cin>>n>>s;
    for(I i=0;i<n;i++)adjs[i].clear();
    fill_n(cnts,n-1,0);
    for(I i=0;i<n-1;i++){
      I u,v,w;cin>>u>>v>>w,u--,v--;
      adjs[u].push_back({v,i});
      adjs[v].push_back({u,i});
      w_arr[i]=w;
    }
    dfs(0);
    Lli tot=0;
    for(I i=0;i<n-1;i++)tot+=w_arr[i]*cnts[i];
    while(ques.size())ques.pop();
    for(I i=0;i<n-1;i++){
      Lli w=w_arr[i],dif=w-w/2;
      ques.push({dif*cnts[i],i});
    }
    I res=0;
    while(ques.size()&&tot>s){
      auto[cur,i]=ques.top();ques.pop();
      tot-=cur,res++;
      w_arr[i]/=2;
      Lli w=w_arr[i],dif=w-w/2;
      ques.push({dif*cnts[i],i});
    }
    printf("%i\n",res);
  }
}