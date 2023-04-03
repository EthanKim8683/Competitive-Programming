#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=3e5;
const I A=3e5;
const I MAX=1e9;
I eras[A+1];
I a_arr[N];
map<I,I>adjs[A+1];
vector<I>facs;
I deps[A+1];
I pars[A+1];
I edgs[A+1];
queue<I>que;
vector<I>ress;
void fac(I a){
  facs.clear();
  for(;a!=1;a/=eras[a])facs.push_back(eras[a]);
}
void add(I a,I d,I p,I i){
  if(d>=deps[a])return;
  deps[a]=d,pars[a]=p,edgs[a]=i,que.push(a);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  iota(eras,eras+A+1,0);
  for(I i=2;i*i<=A;i++)if(eras[i]==i)for(I j=i*i;j<=A;j+=i)eras[j]=min(eras[j],i);
  fill_n(deps,A+1,MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I s,t;cin>>s>>t,s--,t--;
  if(s==t)printf("1\n%i\n",s+1),exit(0);
  for(I i=0;i<n;i++){
    fac(a_arr[i]);
    for(I j=0;j<facs.size();j++)for(I k=j+1;k<facs.size();k++){
      I a=facs[j],b=facs[k];
      adjs[a][b]=i,adjs[b][a]=i;
    }
  }
  fac(a_arr[s]);
  for(auto a:facs)add(a,0,-1,s);
  while(que.size()){
    I a=que.front();que.pop();
    for(auto[b,i]:adjs[a])add(b,deps[a]+1,a,i);
  }
  pair<I,I>par={MAX,-1};
  fac(a_arr[t]);
  for(auto a:facs)par=min(par,{deps[a],a});
  if(par.first==MAX)printf("-1\n"),exit(0);
  ress.push_back(t);
  for(I a=par.second;a!=-1;a=pars[a]){
    I edg=edgs[a];
    if(edg!=ress.back())ress.push_back(edg);
  }
  reverse(ress.begin(),ress.end());
  printf("%i\n",ress.size());
  for(auto res:ress)printf("%i ",res+1);
}