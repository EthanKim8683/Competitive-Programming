#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=1e5;
const I A=1e6;
I a_arr[N];
I cnts[N];
priority_queue<pair<Lli,I>>ques;
Lli cst(I i,I cnt){
  I a=a_arr[i],upp=a%cnt,low=cnt-upp,x=a/cnt,y=x+1;
  return(Lli)y*y*upp+(Lli)x*x*low;
}
void psh(I i){
  ques.push({cst(i,cnts[i])-cst(i,cnts[i]+1),i});
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  fill_n(cnts,n,1);
  Lli res=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    res+=(Lli)a*a,psh(i);
  }
  for(I i=n;i<k;i++){
    auto[rem,j]=ques.top();ques.pop();
    res-=rem,cnts[j]++,psh(j);
  }
  printf("%lli\n",res);
}