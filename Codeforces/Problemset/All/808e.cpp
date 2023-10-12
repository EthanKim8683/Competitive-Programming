#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100000;
const I M=300000;
const I W=3;
vector<Lli>csts[W+1];
vector<Lli>ps[W+1];
Lli reps[M+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++){
    I w,c;cin>>w>>c;
    csts[w].push_back(c);
  }
  for(I i=1;i<=W;i++){
    sort(csts[i].rbegin(),csts[i].rend());
    ps[i].push_back(0);
    for(auto cst:csts[i])ps[i].push_back(ps[i].back()+cst);
  }
  for(I x=0;x<3&&x<=csts[2].size();x++)for(I y=0;y<2&&y<=csts[3].size();y++){
    Lli acc=ps[2][x]+ps[3][y];
    for(I i=x,j=y;;){
      reps[i*2+j*3]=max(reps[i*2+j*3],acc);
      if(i+3<=csts[2].size()&&j+2<=csts[3].size()){
        ps[2][i+3]-ps[2][i]>ps[3][j+2]-ps[3][j]?(acc+=ps[2][i+3]-ps[2][i],i+=3):(acc+=ps[3][j+2]-ps[3][j],j+=2);
      }else if(i+3<=csts[2].size()){
        acc+=ps[2][i+3]-ps[2][i],i+=3;
      }else if(j+2<=csts[3].size()){
        acc+=ps[3][j+2]-ps[3][j],j+=2;
      }else{
        break;
      }
    }
  }
  for(I i=0;i+1<=m;i++)reps[i+1]=max(reps[i+1],reps[i]);
  Lli res=0;
  for(I i=0;i<=m;i++)res=max(res,(m-i<=csts[1].size()?ps[1][m-i]:0)+reps[i]);
  printf("%lli\n",res);
}
/*
instead of using dynamic programming to find the optimal choice of 2's and 3's
to replace any given amount of 1's with, we can greedily choose chunks of
total weight 6 of either 2's or 3's and add between 0 and 3 and 0 and 2 2's
and 3's respectively for in-betweens
*/