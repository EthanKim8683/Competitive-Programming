#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I N=2000;
const I M=2000;
I di[]{-1,0,1,0},dj[]{0,-1,0,1};
C brds[N][M+1];
I adjs1[N*M];
B adjs2[N*M][4];
B viss[N*M];
I sizs[N*M];
queue<I>ques;
I n,m;
B out(I i,I j){
  return i<0||i>=n||j<0||j>=m;
}
I cps(I i,I j){
  return i*m+j;
}
void adj(I i1,I j1,I k){
  I i2=i1+di[k],j2=j1+dj[k];
  if(out(i1,j1)||out(i2,j2))return;
  I a=cps(i1,j1),b=cps(i2,j2);
  adjs1[a]=b,adjs2[b][(k+2)%4]=1;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n>>m;
    for(I i=0;i<n;i++)cin>>brds[i];
    for(I i=0;i<n*m;i++)adjs1[i]=-1,fill_n(adjs2[i],4,0);
    for(I i=0;i<n;i++)for(I j=0;j<m;j++){
      if(brds[i][j]=='U')adj(i,j,0);
      if(brds[i][j]=='D')adj(i,j,2);
      if(brds[i][j]=='L')adj(i,j,1);
      if(brds[i][j]=='R')adj(i,j,3);
    }
    fill_n(viss,n*m,0);
    fill_n(sizs,n*m,0);
    for(I i=0;i<n*m;i++)if(sizs[i]==0){
      I a=i;
      for(;!viss[a];a=adjs1[a]){
        viss[a]=1;
        if(adjs1[a]==-1)break;
      }
      if(adjs1[a]==-1){
        sizs[a]=1,ques.push(a);
      }else{
        I len=1;
        for(I b=adjs1[a];b!=a;b=adjs1[b])len++;
        sizs[a]=len,ques.push(a);
        for(I b=adjs1[a];b!=a;b=adjs1[b])sizs[b]=len,ques.push(b);
      }
      while(ques.size()){
        I a=ques.front();ques.pop();
        for(I i=0;i<4;i++)if(adjs2[a][i]){
          I b=a+di[i]*m+dj[i];
          if(sizs[b]==0)sizs[b]=sizs[a]+1,ques.push(b);
        }
      }
    }
    I i=max_element(sizs,sizs+n*m)-sizs,r=i/m,c=i%m,d=sizs[i];
    printf("%i %i %i\n",r+1,c+1,d);
  }
}
/*
the board forms a functional graph, meaning it consists of cycles (not always,
in this case) and paths leading into cycles

therefore, we should look for all cycles and find the maximal path leading
into those cycles

the length of the cycle in addition to that of the maximal path is the maximum
number of moves for that component
*/