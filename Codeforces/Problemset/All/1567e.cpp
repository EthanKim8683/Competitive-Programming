#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
I a_arr[N];
set<I>brks;
Lli fens[N+1];
I n;
void upd(I i,Lli val){
  for(;i<=n;i+=i&-i)fens[i]+=val;
}
Lli qry(I i){
  Lli res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
void add(I i){
  Lli j=*prev(brks.lower_bound(i)),k=*brks.upper_bound(i),len1=i-j,len2=k-i,len3=k-j;
  upd(i+1,len2*(len2+1)/2),upd(j+1,len1*(len1+1)/2-len3*(len3+1)/2);
}
void rem(I i){
  Lli j=*prev(brks.lower_bound(i)),k=*brks.upper_bound(i),len1=i-j,len2=k-i,len3=k-j;
  upd(i+1,-len2*(len2+1)/2),upd(j+1,len3*(len3+1)/2-len1*(len1+1)/2);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  brks.insert(0),brks.insert(n);
  for(I i=1;i<n;i++)if(a_arr[i-1]>a_arr[i])brks.insert(i);
  for(auto it=brks.begin();next(it)!=brks.end();it++){
    Lli i=*it,j=*next(it),len=j-i;
    upd(i+1,len*(len+1)/2);
  }
  while(q--){
    I t;cin>>t;
    if(t==1){
      I x,y;cin>>x>>y,x--;
      if(x-1>=0&&a_arr[x-1]>a_arr[x])rem(x),brks.erase(x);
      if(x+1<n&&a_arr[x]>a_arr[x+1])rem(x+1),brks.erase(x+1);
      a_arr[x]=y;
      if(x-1>=0&&a_arr[x-1]>a_arr[x])add(x),brks.insert(x);
      if(x+1<n&&a_arr[x]>a_arr[x+1])add(x+1),brks.insert(x+1);
    }
    if(t==2){
      I l,r;cin>>l>>r,l--,r--;
      auto low=brks.lower_bound(l),upp=brks.upper_bound(r+1);
      if(low==upp){
        Lli len=r-l+1;
        printf("%lli\n",len*(len+1)/2);
        continue;
      }
      Lli i=*low,j=*prev(upp),len1=i-l,len2=r+1-j;
      printf("%lli\n",qry(j)-qry(i)+len1*(len1+1)/2+len2*(len2+1)/2);
    }
  }
}