#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e5;
I a_arr[N];
I inds[N];
vector<I>rems;
queue<I>ques;
B cmp(I a,I b){
  return a_arr[a]<a_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;Lli k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  Lli pre=0;
  for(I i=0;i<n;i++){
    I a=a_arr[inds[i]];
    Lli tot=(Lli)(n-i)*(a-pre);
    if(tot<=k){k-=tot,pre=a;continue;}
    Lli rem=k/(n-i),fin=pre+rem+1;k-=(Lli)rem*(n-i);
    for(I j=i;j<n;j++)rems.push_back(inds[j]);
    sort(rems.begin(),rems.end());
    for(auto j:rems)ques.push(j);
    while(k--){
      I j=ques.front();ques.pop();
      if(a_arr[j]>fin)ques.push(j);
    }
    while(ques.size())printf("%i ",ques.front()+1),ques.pop();
    exit(0);
  }
  if(!k)exit(0);
  printf("-1\n");
}