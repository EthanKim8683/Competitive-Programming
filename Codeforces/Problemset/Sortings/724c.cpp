#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=100000;
const I M=100000;
const I K=100000;
const Lli MAX=1e18;
pair<I,I>sens[K];
vector<I>qrys[2][N+M+1];
B viss[4][N+1];
Lli ress[K];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  for(I i=0;i<k;i++){
    I x,y;cin>>x>>y;
    sens[i]={x,y};
    qrys[0][m+x-y].push_back(i);
    qrys[1][x+y].push_back(i);
  }
  fill_n(ress,k,MAX);
  I x=0,y=0,z=1,w=1;
  Lli tot=0;
  while(1){
    if(x==0&&viss[0][y])break;
    if(x==0)viss[0][y]=1;
    if(x==n)viss[1][y]=1;
    if(y==0)viss[2][x]=1;
    if(y==m)viss[3][x]=1;
    Lli len1=(0-x)/z,len2=(0-y)/w,len3=(n-x)/z,len4=(m-y)/w,len=MAX;
    if(len1>0)len=min(len,len1);
    if(len2>0)len=min(len,len2);
    if(len3>0)len=min(len,len3);
    if(len4>0)len=min(len,len4);
    for(auto i:qrys[z!=w][z!=w?x+y:m+x-y]){
      auto[u,v]=sens[i];
      ress[i]=min(ress[i],tot+(u-x)/z);
    }
    x+=z*len,y+=w*len,tot+=len;
    if((x==0||x==n)&&(y==0||y==m))break;
    x==0||x==n?z=-z:w=-w;
  }
  for(I i=0;i<k;i++)printf("%lli\n",ress[i]==MAX?-1:ress[i]);
}