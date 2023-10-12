#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
vector<I>adjs[N];
I inds[N];
priority_queue<I>ques;
vector<I>tops;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[b].push_back(a);
    inds[a]++;
  }
  for(I i=0;i<n;i++)if(inds[i]==0)ques.push(i);
  while(ques.size()){
    I a=ques.top();ques.pop();
    tops.push_back(a);
    for(auto b:adjs[a])if(--inds[b]==0)ques.push(b);
  }
  reverse(tops.begin(),tops.end());
  for(auto i:tops)printf("%i ",i+1);
}