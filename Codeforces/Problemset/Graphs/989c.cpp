#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using C=char;

const I N=50;
const I M=50;

C ress[N][M+1];

void col1(I i,I j,C c){
  ress[i][j]=c;
}

void col2(I i,I j,C c){
  ress[N-1-i][j]=c;
}

void col3(I i,I j,C c){
  ress[i][M-1-j]=c;
}

void col4(I i,I j,C c){
  ress[N-1-i][M-1-j]=c;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I a,b,c,d;cin>>a>>b>>c>>d;
  for(I i=0;i<N;i++)for(I j=0;j<M;j++)ress[i][j]='A';
  for(I i=0;i<21;i++)for(I j=0;j<21;j++)
    col1(i,j,'A'),col2(i,j,'B'),col3(i,j,'C'),col4(i,j,'D');
  for(I i=0;i<b-1;i++)col1((i/10)*2+1,(i%10)*2+1,'B');
  for(I i=0;i<c-1;i++)col2((i/10)*2+1,(i%10)*2+1,'C');
  for(I i=0;i<d-1;i++)col3((i/10)*2+1,(i%10)*2+1,'D');
  for(I i=0;i<a-1;i++)col4((i/10)*2+1,(i%10)*2+1,'A');
  printf("%i %i\n",N,M);
  for(I i=0;i<N;i++)printf("%s\n",ress[i]);
  return 0;
}