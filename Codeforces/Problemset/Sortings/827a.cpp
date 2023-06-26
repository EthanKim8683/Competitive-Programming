#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
const I N=1e5;
const I X=1e6;
S t_arr[N];
vector<I>inds[2*X];
B cmp(I a,I b){
  return t_arr[a].size()>t_arr[b].size();
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    cin>>t_arr[i];
    I k;cin>>k;
    for(I j=0;j<k;j++){
      I x;cin>>x,x--;
      inds[x].push_back(i);
    }
  }
  S res="";
  I j=-1,k=-1,len=0;
  for(I i=0;i<2*X;i++){
    sort(inds[i].begin(),inds[i].end(),cmp);
    if(inds[i].size()){
      I l=inds[i].front();
      if(j==-1||k==-1||i+t_arr[l].size()>=i-k+t_arr[j].size())j=l,k=0;
    }
    if(j==-1||k==-1||k>=t_arr[j].size())res+=S(1,'a');
    else res+=t_arr[j][k],k++,len=i+1;
  }
  res=res.substr(0,len);
  printf("%s\n",res.c_str());
}