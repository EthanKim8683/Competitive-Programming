#include<iostream>
#include<cstdio>
#include<queue>
#include<tuple>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using S=string;

const I N=1000;
const I MAX=1e9;

priority_queue<tuple<I,I,I>>que;
I diss[N][N+1];
I movs[N+1][N+1];
vector<I>ress;

void add(I i,I j,I d,I m){
  if(d>=diss[i][j])return;
  que.push({-(diss[i][j]=d),i,j}),movs[i][j]=m;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  fill(&diss[0][0],&diss[0][0]+sizeof(diss)/sizeof(I),MAX);
  for(I i=1;i<=n;i++)add(0,i,i,-1);
  while(que.size()){
    auto[d,i,j]=que.top();que.pop();
    if(i==n-1){
      for(I k=n-1;k>=0;k--)ress.push_back(j),j=movs[k][j];
      reverse(ress.begin(),ress.end());
      for(auto i:ress)printf("%i ",i);
      return 0;
    }
    if((d*=-1)!=diss[i][j])continue;
    if(s[i]=='=')add(i+1,j,d+j,j);
    if(s[i]=='L')for(I k=1;k<j;k++)add(i+1,k,d+k,j);
    if(s[i]=='R')for(I k=j+1;k<=n;k++)add(i+1,k,d+k,j);
  }
  return 0;
}