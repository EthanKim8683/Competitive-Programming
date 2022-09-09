#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=100;
const I M=1e6;
const I MAX=1e9;

C cels[N][N];
I diss[N][N];
I p_arr[M];
vector<I>ress;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>cels[i];
  I m;cin>>m;
  for(I i=0;i<m;i++){I p;cin>>p,p_arr[i]=p-1;}
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)
    diss[i][j]=cels[i][j]=='1'?1:MAX;
  for(I i=0;i<n;i++)diss[i][i]=0;
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)for(I k=0;k<n;k++)
    diss[j][k]=min(diss[j][k],diss[j][i]+diss[i][k]);
  ress.push_back(p_arr[0]);
  I j=0;
  for(I i=1;i<m;i++)
    if(diss[p_arr[j]][p_arr[i]]<i-j)
      ress.push_back(p_arr[j=i-1]);
  printf("%i\n",ress.size()+1);
  for(auto i:ress)printf("%i ",i+1);
  printf("%i",p_arr[m-1]+1);
  return 0;
}