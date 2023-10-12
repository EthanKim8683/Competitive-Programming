#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=5e4;
const I MAX=1e9;
vector<I>poss[26][26];
I diss[26][26][N-1];
I fdws[26][26][26][26];
queue<pair<I,I>>ques;
I n;
void cmb(I&a,I b){
  a=min(a,b);
}
void add(I i,I j,I k,I d){
  if(i<0||i+1>=n)return;
  if(d>=diss[i][j][k])return;
  ques.push({k,diss[i][j][k]=d});
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&diss[0][0][0],&diss[0][0][0]+26*26*(N-1),MAX);
  fill(&fdws[0][0][0][0],&fdws[0][0][0][0]+26*26*26*26,MAX);
  S s;cin>>s;
  n=s.size();
  for(I i=0;i+1<n;i++)poss[s[i]-'a'][s[i+1]-'a'].push_back(i);
  for(I i=0;i<26;i++)for(I j=0;j<26;j++){
    for(auto k:poss[i][j])add(i,j,k,0);
    while(ques.size()){
      auto[k,d]=ques.front();ques.pop();
      add(i,j,k-1,d+1),add(i,j,k+1,d+1);
    }
    for(I k=0;k+1<n;k++)cmb(fdws[i][j][s[k]-'a'][s[k+1]-'a'],diss[i][j][k]);
  }
  for(I a=0;a<26;a++)for(I b=0;b<26;b++)for(I c=0;c<26;c++)for(I d=0;d<26;d++)for(I e=0;e<26;e++)for(I f=0;f<26;f++){
    cmb(fdws[c][d][e][f],fdws[c][d][a][b]+fdws[a][b][e][f]+1);
  }
  for(I a=0;a<26;a++)for(I b=0;b<26;b++)for(I c=0;c<26;c++)for(I d=0;d<26;d++){
    for(auto i:poss[c][d])cmb(diss[a][b][i],fdws[a][b][c][d]+1);
  }
  I m;cin>>m;
  for(I i=0;i<m;i++){
    I f,t;cin>>f>>t,f--,t--;
    I res=abs(f-t);
    for(I j=0;j<26;j++)for(I k=0;k<26;k++){
      res=min(res,diss[j][k][f]+diss[j][k][t]+1);
    }
    printf("%i\n",res);
  }
}