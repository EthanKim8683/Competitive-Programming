#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=1000;
const I M=1000;

I di[]{-1,1,0,0},dj[]{0,0,-1,1};
I cnts1[N],cnts2[M];
B vlds1[N],vlds2[M];
C cels[N][M+1];
I pars[N*M];
I cnt;
I n,m;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m;
}

I ind(I i,I j){
  return i*m+j;
}

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
  cnt--;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  fill_n(pars,n*m,-1);
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)
    cels[i][j]=cels[i][j]=='#';
  for(I i=0;i<n;i++){
    for(I r=0;r<m;r++){
      if(!cels[i][r])continue;
      while(++r<m&&cels[i][r]);
      cnts1[i]++;
    }
    if(cnts1[i]>1)printf("-1\n"),exit(0);
    vlds1[i]=cnts1[i];
  }
  for(I i=0;i<m;i++){
    for(I r=0;r<n;r++){
      if(!cels[r][i])continue;
      while(++r<n&&cels[r][i]);
      cnts2[i]++;
    }
    if(cnts2[i]>1)printf("-1\n"),exit(0);
    vlds2[i]=cnts2[i];
  }
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)
    if(cnts1[i]==0&&cnts2[j]==0)
      vlds1[i]=vlds2[j]=1;
  for(I i=0;i<n;i++)
    if(!vlds1[i])printf("-1\n"),exit(0);
  for(I i=0;i<m;i++)
    if(!vlds2[i])printf("-1\n"),exit(0);
  cnt=0;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)
    cnt+=cels[i][j];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    for(I k=0;k<4;k++){
      I x=i+di[k],y=j+dj[k];
      if(bnd(x,y)&&cels[i][j]&&cels[x][y])
        uni(ind(i,j),ind(x,y));
    }
  }
  printf("%i\n",cnt);
  return 0;
}