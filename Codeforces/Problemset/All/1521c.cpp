#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e4;
I ress[N];
I n;
I ask(I t,I i,I j,I x){
  printf("? %i %i %i %i\n",t,i+1,j+1,x),fflush(stdout);
  I y;cin>>y;
  if(y==-1)exit(0);
  return y;
}
void ans(){
  printf("! ");
  for(I i=0;i<n;i++)printf("%i ",ress[i]);
  printf("\n"),fflush(stdout);
}
void slv(I i){
  if(ress[i]==1)for(I j=0;j<n;j++)if(ress[j]==-1)ress[j]=ask(1,i,j,n-1);
  if(ress[i]==n)for(I j=0;j<n;j++)if(ress[j]==-1)ress[j]=ask(2,j,i,1);
  ans();
}
void all(){
  I a=max(ask(1,0,1,n-1),ask(1,1,0,n-1)),b=ask(2,1,0,a-1),i=a==b,c;
  if((ress[i]=a)==1)return slv(i);
  if((ress[i]=a)==n)return slv(i);
  if(a<=n/2)for(I j=0;j<n;j++)if(i!=j)if((c=ask(1,i,j,n-1))!=a&&(ress[j]=c)==n)return slv(j);
  if(a>n/2)for(I j=0;j<n;j++)if(i!=j)if((c=ask(2,j,i,1))!=a&&(ress[j]=c)==1)return slv(j);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    fill_n(ress,n,-1),all();
  }
}