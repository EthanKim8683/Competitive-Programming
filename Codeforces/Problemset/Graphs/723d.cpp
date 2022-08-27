#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=50;
const I M=50;
const I MAX=1e9;

I dx[]{-1,1,0,0},dy[]{0,0,-1,1};
C cels[N][M];
I pars[N*M+1];
vector<I>laks;
B trns[N*M+1];
I n,m;
I cnt=1;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m;
}

I cps(I i,I j){
  if(!bnd(i,j))return n*m;
  return i*m+j;
}

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

C qry(I i,I j){
  if(!bnd(i,j))return '.';
  return cels[i][j];
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
  cnt--;
}

void cmb(I i,I j,I k,I l){
  if(qry(i,j)=='.'&&qry(k,l)=='.')
    uni(cps(i,j),cps(k,l));
}

I siz(I i){
  if((i=fnd(i))==n*m)return MAX;
  return -pars[i];
}

B cmp(I i,I j){
  return siz(i)<siz(j);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>n>>m>>k;
  fill_n(pars,n*m+1,-1);
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)
    for(I k=0;k<4;k++)cmb(i,j,i+dx[k],j+dy[k]);
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    if(qry(i,j)!='.')continue;
    I k=cps(i,j);
    if(k==fnd(k))laks.push_back(k);
  }
  if(n*m==fnd(n*m))laks.push_back(n*m);
  sort(laks.begin(),laks.end(),cmp);
  I res=0;
  for(I i=0;i<laks.size()-k-1;i++){
    I lak=laks[i];
    trns[lak]=true,res+=siz(lak);
  }
  printf("%i\n",res);
  for(I i=0;i<n;i++){
    for(I j=0;j<m;j++){
      if(cels[i][j]=='*'){printf("*");continue;}
      if(trns[fnd(cps(i,j))])printf("*");
      else printf(".");
    }
    printf("\n");
  }
  return 0;
}