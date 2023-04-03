#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
const I N=500;
const I K=N;
const I MIN=-1e9;
I a_arr[N];
I b_arr[K];
vector<pair<I,C>>ress;
map<I,I>rems;
priority_queue<tuple<I,I,I>>ques;
I fens[N+1];
I n;
void upd(I i,I val){
  for(;i<=n;i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I k;cin>>k;
  for(I i=0;i<k;i++)cin>>b_arr[i];
  I j=0,o=0,sum=0;
  for(I i=0;i<n;i++){
    if(sum<b_arr[o])sum+=a_arr[i];
    if(sum>b_arr[o])printf("NO\n"),exit(0);
    if(sum==b_arr[o]){
      rems.clear();
      for(I l=j;l<=i;l++)rems[l]=a_arr[l];
      for(I l=j;l<=i;l++){
        if(l-1>=j&&rems[l]>rems[l-1])ques.push({rems[l],l,l-1});
        if(l+1<=i&&rems[l]>rems[l+1])ques.push({rems[l],l,l+1});
      }
      while(ques.size()){
        auto[a,x,y]=ques.top();ques.pop();
        if(!rems.count(x)||!rems.count(y))continue;
        if(rems[x]<=rems[y])continue;
        rems[x]+=rems[y];
        ress.push_back({x-qry(x),"RL"[y<x]});
        rems.erase(y),upd(y+1,1);
        auto it=rems.find(x);
        if(it!=rems.begin()){
          I z=prev(it)->first;
          if(rems[x]>rems[z])ques.push({rems[x],x,z});
          if(rems[z]>rems[x])ques.push({rems[z],z,x});
        }
        if(it!=--rems.end()){
          I z=next(it)->first;
          if(rems[x]>rems[z])ques.push({rems[x],x,z});
          if(rems[z]>rems[x])ques.push({rems[z],z,x});
        }
      }
      if(rems.size()>1)printf("NO\n"),exit(0);
      j=i+1,o++,sum=0;
    }
  }
  if(o!=k)printf("NO\n"),exit(0);
  printf("YES\n");
  for(auto[x,c]:ress)printf("%i %c\n",x+1,c);
}