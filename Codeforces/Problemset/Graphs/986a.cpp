#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;
const I K=100;
const I MAX=1e9;

I a_arr[N];
queue<I>que[K];
I diss[N][K];
vector<I>adjs[N];

void add(I i,I j,I d){
  if(d>=diss[j][i])return;
  diss[j][i]=d;
  que[i].push(j);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k,s;cin>>n>>m>>k>>s;
  fill(&diss[0][0],&diss[0][0]+sizeof(diss)/sizeof(I),MAX);
  for(I i=0;i<n;i++){I a;cin>>a,add(a-1,i,0);}
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  for(I i=0;i<k;i++){
    while(que[i].size()){
      I a=que[i].front();que[i].pop();
      for(auto b:adjs[a])add(i,b,diss[a][i]+1);
    }
  }
  for(I i=0;i<n;i++){
    sort(diss[i],diss[i]+k);
    Lli sum=0;
    for(I j=0;j<s;j++)sum+=diss[i][j];
    printf("%lli ",sum);
  }
  return 0;
}