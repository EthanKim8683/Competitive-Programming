#include<iostream>
#include<cstdio>
#include<set>
#include<queue>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;
struct Bld{I slts[10];};

const I N=10;
const I C=2e5;

I c_arr[N];
I slts[N][C];
set<Bld>viss;
set<Bld>invs;
priority_queue<pair<Lli,Bld>>que;
I n;

B operator<(const Bld&a,const Bld&b){
  for(I i=0;i<n;i++){
    if(a.slts[i]<b.slts[i])return 1;
    if(a.slts[i]>b.slts[i])return 0;
  }
  return 0;
}

void add(Bld a){
  if(viss.count(a))return;
  Lli sum=0;
  for(I i=0;i<n;i++){
    I c=a.slts[i];
    if(c<0)return;
    sum+=slts[i][c];
  }
  que.push({sum,a}),viss.insert(a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++){
    I c;cin>>c;
    c_arr[i]=c;
    for(I j=0;j<c;j++)cin>>slts[i][j];
  }
  I m;cin>>m;
  for(I i=0;i<m;i++){
    Bld cur;
    for(I j=0;j<n;j++){I b;cin>>b,cur.slts[j]=b-1;}
    invs.insert(cur);
  }
  Bld cur;
  for(I i=0;i<n;i++)cur.slts[i]=c_arr[i]-1;
  add(cur);
  while(que.size()){
    auto[d,a]=que.top();que.pop();
    if(!invs.count(a)){
      for(I i=0;i<n;i++)printf("%i ",a.slts[i]+1);
      exit(0);
    }
    for(I i=0;i<n;i++)a.slts[i]--,add(a),a.slts[i]++;
  }
}