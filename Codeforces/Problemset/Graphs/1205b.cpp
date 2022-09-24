#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;
const I MAX=1e9;

vector<I>bits[64];
vector<I>adjs[N];
I diss[N];
queue<I>que;
I res=MAX;

void add(I d,I a){
  if(d>=diss[a])return;
  que.push(a),diss[a]=d;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    Lli a;cin>>a;
    for(I j=0;j<64;j++)if(a>>j&1)bits[j].push_back(i);
  }
  for(I i=0;i<64;i++)if(bits[i].size()>=3){printf("3\n");return 0;}
  for(I i=0;i<64;i++){
    if(bits[i].size()!=2)continue;
    I a=bits[i][0],b=bits[i][1];
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  I res=MAX;
  for(I i=0;i<64;i++){
    if(bits[i].size()!=2)continue;
    I a=bits[i][0],b=bits[i][1];
    fill_n(diss,n,MAX);
    add(0,a);
    while(que.size()){
      auto c=que.front();que.pop();
      for(auto d:adjs[c])if(min(a,b)!=min(c,d)||max(a,b)!=max(c,d))
        add(diss[c]+1,d);
    }
    res=min(res,diss[b]+1);
  }
  if(res==MAX)printf("-1\n");
  else printf("%i\n",res);
  return 0;
}