#include<iostream>
#include<cstdio>
 
using namespace std;
 
using I=int;
using C=char;
using B=bool;
 
const I N=100;
const I M=100;
const I K=100;
 
C cels[N][M][K+1];
I n,m,k;
 
B bnd(I i,I j,I l){
  return i>=0&&i<n&&j>=0&&j<m&&l>=0&&l<k;
}
 
B qry(I i,I j,I l){
  return bnd(i,j,l)&&cels[i][j][l]=='1';
}
 
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m>>k;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>cels[i][j];
  I res=0;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)for(I l=0;l<k;l++){
    if(cels[i][j][l]=='0')continue;
    B cri=0;
    cri|=qry(i-1,j,l)&&qry(i+1,j,l);
    cri|=qry(i,j-1,l)&&qry(i,j+1,l);
    cri|=qry(i,j,l-1)&&qry(i,j,l+1);
    cri|=qry(i-1,j,l)&&qry(i,j+1,l)&&!qry(i-1,j+1,l);
    cri|=qry(i-1,j,l)&&qry(i,j,l+1)&&!qry(i-1,j,l+1);
    cri|=qry(i,j-1,l)&&qry(i+1,j,l)&&!qry(i+1,j-1,l);
    cri|=qry(i,j-1,l)&&qry(i,j,l+1)&&!qry(i,j-1,l+1);
    cri|=qry(i,j,l-1)&&qry(i+1,j,l)&&!qry(i+1,j,l-1);
    cri|=qry(i,j,l-1)&&qry(i,j+1,l)&&!qry(i,j+1,l-1);
    res+=cri;
  }
  printf("%i\n",res);
  return 0;
}