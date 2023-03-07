#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=3e5;
const I M=8;
I a_arr[N][M];
vector<tuple<I,I,I>>vals;
I curs[N];
map<I,I>viss;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>a_arr[i][j];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)vals.push_back({a_arr[i][j],i,j});
  sort(vals.begin(),vals.end(),greater<tuple<I,I,I>>());
  for(auto[val,i,j]:vals){
    curs[i]|=1<<j;
    viss[curs[i]]=i;
    for(auto[k,l]:viss)if((k|curs[i])==(1<<m)-1)printf("%i %i\n",i+1,l+1),exit(0);
  }
}