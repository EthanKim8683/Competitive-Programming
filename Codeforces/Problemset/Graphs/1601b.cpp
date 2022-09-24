#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<set>
#include<vector>

using namespace std;

using I=int;

const I N=300000;
const I MAX=1e9;

I a_arr[N+1];
I b_arr[N+1];
queue<I>que;
set<I>unvs;
I diss[N+1];
I pars1[N+1],pars2[N+1];
vector<I>ress;

void add(I d,I i,I p){
  I j=i+b_arr[i];
  pars1[i]=p;
  if(diss[j]!=MAX)return;
  pars2[j]=i;
  que.push(j),diss[j]=d;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(diss,n+1,MAX);
  for(I i=1;i<=n;i++)cin>>a_arr[i];
  for(I i=1;i<=n;i++)cin>>b_arr[i];
  for(I i=0;i<=n;i++)unvs.insert(i);
  add(0,n,-1);
  while(que.size()){
    I a=que.front();que.pop();
    if(a==0){
      I d=diss[a];
      for(I i=0;i<d;i++){
        a=pars2[a];
        ress.push_back(a);
        a=pars1[a];
      }
      reverse(ress.begin(),ress.end());
      printf("%i\n",d);
      for(auto i:ress)printf("%i ",i);
      return 0;
    }
    for(auto it=unvs.lower_bound(a-a_arr[a]);it!=unvs.end();it=unvs.erase(it))
      add(diss[a]+1,*it,a);
  }
  printf("-1\n");
  return 0;
}