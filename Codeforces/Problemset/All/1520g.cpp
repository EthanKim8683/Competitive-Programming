#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e3;
const I M=2e3;
const Lli MAX=1e18;
I dx[]{-1,0,1,0},dy[]{0,-1,0,1};
I a_arr[N][M];
Lli diss[2][N][M];
priority_queue<tuple<Lli,I,I>>ques;
I n,m;
void add(I t,Lli dis,I i,I j){
  if(i<0||j<0||i>=n||j>=m)return;
  if(a_arr[i][j]==-1)return;
  if(dis>=diss[t][i][j])return;
  ques.push({-(diss[t][i][j]=dis),i,j});
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&diss[0][0][0],&diss[0][0][0]+2*N*M,MAX);
  I w;cin>>n>>m>>w;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>a_arr[i][j];
  add(0,0,0,0);
  while(ques.size()){
    auto[dis,i,j]=ques.top();ques.pop();
    if((dis=-dis)!=diss[0][i][j])continue;
    for(I k=0;k<4;k++)add(0,dis+w,i+dx[k],j+dy[k]);
  }
  add(1,0,n-1,m-1);
  while(ques.size()){
    auto[dis,i,j]=ques.top();ques.pop();
    if((dis=-dis)!=diss[1][i][j])continue;
    for(I k=0;k<4;k++)add(1,dis+w,i+dx[k],j+dy[k]);
  }
  Lli low=MAX,upp=MAX;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)if(a_arr[i][j]>0){
    low=min(low,diss[0][i][j]+a_arr[i][j]);
    upp=min(upp,diss[1][i][j]+a_arr[i][j]);
  }
  Lli res=min(diss[0][n-1][m-1],low+upp);
  printf("%lli\n",res==MAX?-1:res);
}