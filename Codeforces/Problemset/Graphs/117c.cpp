#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=5000;

C cels[N][N+1];
I viss[N];
vector<I>stks;
I n;

B dfs(I a){
  if(viss[a]==1)return 1;
  if(viss[a]==2)return 0;
  viss[a]=1;
  stks.push_back(a);
  for(I b=0;b<n;b++)if(cels[a][b]=='1'&&dfs(b))return 1;
  viss[a]=2;
  stks.pop_back();
  return 0;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++){
    if(!dfs(i))continue;
    while(1){
      I c=stks.back();stks.pop_back();
      I b=stks.back();stks.pop_back();
      I a=stks.back();stks.pop_back();
      if(cels[c][a]=='1'){
        printf("%i %i %i\n",a+1,b+1,c+1);
        exit(0);
      }
      stks.push_back(a);
      stks.push_back(c);
    }
  }
  printf("-1\n");
}