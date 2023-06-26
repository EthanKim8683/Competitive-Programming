#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1000;
const I M=1000;
I a_arr[N][M];
vector<I>unqs1[N],unqs2[M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>a_arr[i][j];
  for(I i=0;i<n;i++){
    for(I j=0;j<m;j++)unqs1[i].push_back(a_arr[i][j]);
    sort(unqs1[i].begin(),unqs1[i].end());
    unqs1[i].erase(unique(unqs1[i].begin(),unqs1[i].end()),unqs1[i].end());
  }
  for(I i=0;i<m;i++){
    for(I j=0;j<n;j++)unqs2[i].push_back(a_arr[j][i]);
    sort(unqs2[i].begin(),unqs2[i].end());
    unqs2[i].erase(unique(unqs2[i].begin(),unqs2[i].end()),unqs2[i].end());
  }
  for(I i=0;i<n;i++){
    for(I j=0;j<m;j++){
      I x=lower_bound(unqs1[i].begin(),unqs1[i].end(),a_arr[i][j])-unqs1[i].begin();
      I y=lower_bound(unqs2[j].begin(),unqs2[j].end(),a_arr[i][j])-unqs2[j].begin();
      printf("%i ",max(x,y)+max(unqs1[i].size()-x,unqs2[j].size()-y));
    }
    printf("\n");
  }
}