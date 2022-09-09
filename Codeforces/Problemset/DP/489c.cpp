#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>

using namespace std;

using I=int;

const I M=100;
const I S=900;

I movs1[M+1][S+1],movs2[M+1][S+1];
queue<pair<I,I>>que1,que2;
vector<I>ress1,ress2;

void add1(I i,I j,I k){
  if(j<0||movs1[i][j]!=-1)return;
  movs1[i][j]=k;
  que1.push({i,j});
}

void add2(I i,I j,I k){
  if(j<0||movs2[i][j]!=-1)return;
  movs2[i][j]=k;
  que2.push({i,j});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m,s;cin>>m>>s;
  if(m==1&&s==0){printf("0 0\n");return 0;}
  fill(&movs1[0][0],&movs1[0][0]+sizeof(movs1)/sizeof(I),-1);
  fill(&movs2[0][0],&movs2[0][0]+sizeof(movs2)/sizeof(I),-1);
  for(I i=1;i<=9;i++)add1(1,s-i,i);
  while(que1.size()){
    auto[d,a]=que1.front();que1.pop();
    if(d==m){
      if(a!=0)continue;
      while(d){
        ress1.push_back(movs1[d][a]);
        a+=movs1[d][a],d-=1;
      }
      reverse(ress1.begin(),ress1.end());
      break;
    }
    for(I i=0;i<=9;i++)add1(d+1,a-i,i);
  }
  for(I i=9;i>=1;i--)add2(1,s-i,i);
  while(que2.size()){
    auto[d,a]=que2.front();que2.pop();
    if(d==m){
      if(a!=0)continue;
      while(d){
        ress2.push_back(movs2[d][a]);
        a+=movs2[d][a],d-=1;
      }
      reverse(ress2.begin(),ress2.end());
      break;
    }
    for(I i=9;i>=0;i--)add2(d+1,a-i,i);
  }
  if(ress1.size())for(auto i:ress1)printf("%i",i);
  else printf("-1");
  printf(" ");
  if(ress2.size())for(auto i:ress2)printf("%i",i);
  else printf("-1");
  return 0;
}