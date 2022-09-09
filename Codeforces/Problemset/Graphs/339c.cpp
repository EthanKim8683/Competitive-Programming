#include<iostream>
#include<cstdio>
#include<queue>
#include<tuple>
#include<vector>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I M=1000;

B viss[M+1][10+1][10+1];
I movs[M+1][10+1][10+1];
queue<tuple<I,I,I>>que;
vector<I>ress;

void add(I i,I j,I k,I l){
  if(viss[i][j][k])return;
  viss[i][j][k]=true;
  movs[i][j][k]=l;
  que.push({i,j,k});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I m;cin>>m;
  add(0,0,0,-1);
  while(que.size()){
    auto[i,j,k]=que.front();que.pop();
    if(i==m){
      while(k!=-1){
        ress.push_back(k);
        I p=movs[i][j][k];
        i-=1,j=k-j,k=p;
      }
      printf("YES\n");
      ress.pop_back();
      while(ress.size()){
        printf("%i ",ress.back());
        ress.pop_back();
      }
      return 0;
    }
    for(I l=1;l<=10;l++)
      if(l!=k&&l>j&&s[l-1]=='1')
      add(i+1,l-j,l,k);
  }
  printf("NO\n");
  return 0;
}