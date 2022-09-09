#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using B=bool;

const I N=1000;

B ress[N][N];
B viss1[N],viss2[N];
I n;

void dfs1(I a){
  if(viss1[a])return;
  viss1[a]=1;
  for(I b=0;b<n;b++)if(ress[a][b])dfs1(b);
}

void dfs2(I a){
  if(viss2[a])return;
  viss2[a]=1;
  for(I b=0;b<n;b++)if(!ress[a][b])dfs2(b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I a,b;cin>>n>>a>>b;
  B inv=0;
  if(b>a)swap(a,b),inv=1;
  if(b!=1){printf("NO\n");return 0;}
  if(a==1)for(I i=0;i+1<n;i++)
    ress[i][i+1]=ress[i+1][i]=1;
  else for(I i=a-1;i<n;i++)for(I j=i+1;j<n;j++)
    ress[i][j]=ress[j][i]=1;
  I cnt1=0,cnt2=0;
  for(I i=0;i<n;i++){
    if(!viss1[i])dfs1(i),cnt1++;
    if(!viss2[i])dfs2(i),cnt2++;
  }
  if(cnt1!=a||cnt2!=b){printf("NO\n");return 0;}
  printf("YES\n");
  for(I i=0;i<n;i++){
    for(I j=0;j<n;j++){
      if(i==j)printf("0");
      else printf("%i",ress[i][j]^inv);
    }
    printf("\n");
  }
  return 0;
}