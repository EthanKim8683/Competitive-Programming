#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=300000;
const I LOGA=19;
const I MAX=1e9;
I a_arr[N];
I upps[N][LOGA];
I pres[LOGA];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&upps[0][0],&upps[0][0]+N*LOGA,MAX);
  I n,q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  fill_n(pres,LOGA,MAX);
  for(I i=n-1;i>=0;i--){
    I a=a_arr[i];
    for(I j=0;j<LOGA;j++)if(a>>j&1){
      I k=pres[j];
      if(k!=MAX)for(I l=0;l<LOGA;l++)upps[i][l]=min(upps[i][l],upps[k][l]);
      upps[i][j]=min(upps[i][j],i);
      pres[j]=min(pres[j],i);
    }
  }
  while(q--){
    I x,y;cin>>x>>y,x--,y--;
    I a=a_arr[y],res=MAX;
    for(I i=0;i<LOGA;i++)if(a>>i&1)res=min(res,upps[x][i]);
    printf("%s\n",res>y?"Fou":"Shi");
  }
}
/*
we can define a "group" as the set of all i sharing a specific bit

if two indices are in the same group, the former index can reach all groups
the latter one can

if we keep track of all minimum indices of groups reachable via each index,
we can simply check if the earliest index of a group shared by y and reachable
by x is less than y
*/