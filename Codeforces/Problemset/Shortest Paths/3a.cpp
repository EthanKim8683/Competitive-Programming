#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I MAX=1e9;

S dirs[]{"L","R","U","D","LU","LD","RU","RD"};
I dx[]{-1,1,0,0,-1,-1,1,1};
I dy[]{0,0,1,-1,1,-1,1,-1};
I diss[8][8];
I pars[8][8];
queue<pair<I,I>>que;
vector<I>ress;

B bnd(I i,I j){
  return i>=0&&i<8&&j>=0&&j<8;
}

void add(I d,I i,I j,I k){
  if(k!=-1)i+=dx[k],j+=dy[k];
  if(!bnd(i,j)||d>=diss[i][j])return;
  diss[i][j]=d,pars[i][j]=k,que.push({i,j});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&diss[0][0],&diss[0][0]+8*8,MAX);
  S s;cin>>s;
  S t;cin>>t;
  add(0,s[0]-'a',s[1]-'1',-1);
  while(que.size()){
    auto[x,y]=que.front();que.pop();
    for(I i=0;i<8;i++)add(diss[x][y]+1,x,y,i);
  }
  I x=t[0]-'a',y=t[1]-'1';
  I d=diss[x][y];
  for(I i=0;i<d;i++){
    I j=pars[x][y];
    ress.push_back(j);
    x-=dx[j],y-=dy[j];
  }
  reverse(ress.begin(),ress.end());
  printf("%i\n",ress.size());
  for(auto i:ress)printf("%s\n",dirs[i].c_str());
}