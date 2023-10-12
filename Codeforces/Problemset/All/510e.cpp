#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=200;
const I A=1e4;
const I MAX=1e9;
B coms[2*A+1];
I a_arr[N];
I pars[N+2];
I incs[N+2];
I rems[N+2][N+2];
I flws[N+2][N+2];
queue<I>ques;
B viss[N];
vector<vector<I>>ress;
I n;
I bfs(){
  fill_n(incs,n+2,0),fill_n(pars,n+2,-1);
  incs[n]=MAX,pars[n]=n,ques.push(n);
  while(ques.size()){
    I a=ques.front();ques.pop();
    for(I b=0;b<n+2;b++)if(pars[b]==-1&&rems[a][b]>0)incs[b]=min(incs[a],rems[a][b]),pars[b]=a,ques.push(b);
  }
  return incs[n+1];
}
I edk(){
  I res=0,cur;
  while((cur=bfs())>0){
    res+=cur;
    for(I a=n+1;a!=n;a=pars[a]){
      I b=pars[a];
      rems[b][a]-=cur,rems[a][b]+=cur,flws[b][a]+=cur,flws[a][b]-=cur;
    }
  }
  return res;
}
void dfs(I a){
  viss[a]=1,ress.back().push_back(a);
  for(I b=0;b<n;b++)if(!viss[b]&&(flws[a][b]>0||flws[b][a]>0))dfs(b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  for(I i=2;i*i<=2*A;i++)for(I j=i*i;j<=2*A;j+=i)coms[j]=1;
  cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)if(a_arr[i]%2==0)for(I j=0;j<n;j++)if(a_arr[j]%2==1&&!coms[a_arr[i]+a_arr[j]])rems[i][j]=1;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(a%2==0)rems[n][i]=2;
    if(a%2==1)rems[i][n+1]=2;
  }
  if(edk()<n)printf("Impossible"),exit(0);
  for(I i=0;i<n;i++)if(!viss[i])ress.push_back({}),dfs(i);
  printf("%i\n",ress.size());
  for(auto&tabs:ress){
    printf("%i",tabs.size());
    for(auto i:tabs)printf(" %i",i+1);
    printf("\n");
  }
}
/*
for two numbers to sum to a prime number, they must be of different parity

this is because any two numbers of the same sign will sum up to an even number

meanwhile, we can check if it is possible to assign each fox a table if we can
assign each fox two different neighbors

for that we can create a flow graph of two parts: even and odd parity foxes,
each with capacity 2, and edges of capacity 1 between them representing prime
sum pairs

this ensures that each edge is used at most once, meaning no fox has the same
neighbor twice
*/