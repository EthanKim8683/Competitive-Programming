#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100000;
const I C=100000;
vector<I>c_arr[N];
vector<pair<I,I>>cols[C+1];
Lli fens[2][N+1];
I m;
void upd(I t,I i,Lli val){
  for(;i<=m;i+=i&-i)fens[t][i]+=val;
}
Lli qry(I t,I i){
  Lli res=0;
  for(;i>0;i-=i&-i)res+=fens[t][i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>m;
  for(I i=0;i<n;i++){
    c_arr[i].resize(m);
    for(I j=0;j<m;j++)cin>>c_arr[i][j];
  }
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)cols[c_arr[i][j]].push_back({i,j});
  Lli res=0;
  for(I i=1;i<=C;i++){
    sort(cols[i].begin(),cols[i].end());
    Lli cnt=0,pre=0;
    for(auto[j,k]:cols[i]){
      res+=qry(0,k)*k-qry(1,k)+(qry(1,m)-qry(1,k))-(qry(0,m)-qry(0,k))*k+cnt*j-pre;
      upd(0,k+1,1),upd(1,k+1,k),cnt++,pre+=j;
    }
    for(auto[j,k]:cols[i])upd(0,k+1,-1),upd(1,k+1,-k);
  }
  printf("%lli\n",res);
}
/*
for each cell, we can maintain the number of cells of the same color in each
of the four quadrants surrounding it

this handles the different signs when taking the Manhattan distance between
the cells
*/