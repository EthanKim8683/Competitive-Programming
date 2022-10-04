#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=3000;
const I MAX=1e9;

vector<I>adjs[N];
I diss[N][N];
queue<I>que;
I n;

void add(I d,I a,I i){
  if(d>=diss[i][a])return;
  diss[i][a]=d,que.push(a);
}

void bfs(I x){
  fill_n(diss[x],n,MAX);
  add(0,x,x);
  while(que.size()){
    I a=que.front();que.pop();
    for(auto b:adjs[a])add(diss[x][a]+1,b,x);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  I s1,t1,l1;cin>>s1>>t1>>l1,s1--,t1--;
  I s2,t2,l2;cin>>s2>>t2>>l2,s2--,t2--;
  for(I i=0;i<n;i++)bfs(i);
  I res=MAX;
  I s1t1=diss[s1][t1],s2t2=diss[s2][t2];
  if(s1t1<=l1&&s2t2<=l2)res=min(res,s1t1+s2t2);
  for(I i=0;i<n;i++)for(I j=0;j<n;j++){
    I is1=diss[i][s1],is2=diss[i][s2];
    I it1=diss[i][t1],it2=diss[i][t2];
    I js1=diss[j][s1],js2=diss[j][s2];
    I jt1=diss[j][t1],jt2=diss[j][t2];
    I ij=diss[i][j];
    if(is1+ij+jt1<=l1&&is2+ij+jt2<=l2)res=min(res,is1+is2+ij+jt1+jt2);
    if(is1+ij+jt1<=l1&&it2+ij+js2<=l2)res=min(res,is1+js2+ij+jt1+it2);
    if(it1+ij+js1<=l1&&is2+ij+jt2<=l2)res=min(res,js1+is2+ij+it1+jt2);
    if(it1+ij+js1<=l1&&it2+ij+js2<=l2)res=min(res,js1+js2+ij+it1+it2);
  }
  printf("%i\n",res==MAX?-1:m-res);
}