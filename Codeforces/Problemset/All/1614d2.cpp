#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e5;
const I A=2e7;
I a_arr[N];
B uses[A+1];
I facs[A+1];
I cnts[A+1];
Lli dp[A+1];
vector<pair<I,I>>prms;
map<I,I>curs;
void add(I i=0,I b=1){
  if(i==prms.size()){
    uses[b]=1,cnts[b]++;
    return;
  }
  auto[prm,cnt]=prms[i];
  for(I j=0;j<=cnt;j++)add(i+1,b),b*=prm;
}
void trn(I a,I i=0,I b=1){
  if(i==prms.size()){
    dp[b]=max(dp[b],dp[a]+(Lli)(cnts[b]-cnts[a])*b);
    return;
  }
  auto[prm,cnt]=prms[i];
  for(I j=0;j<=cnt;j++)trn(a,i+1,b),b*=prm;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  iota(facs,facs+A+1,0);
  for(I i=2;i*i<=A;i++)for(I j=i*i;j<=A;j+=i)facs[j]=min(facs[j],i);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++){
    curs.clear();
    for(I j=a_arr[i];j>1;j/=facs[j])curs[facs[j]]++;
    prms.assign(curs.begin(),curs.end()),add();
  }
  for(I i=0;i<=A;i++)dp[i]=(Lli)cnts[i]*i;
  for(I i=A;i>1;i--)if(uses[i]){
    curs.clear();
    for(I j=i;j>1;j/=facs[j])curs[facs[j]]++;
    prms.assign(curs.begin(),curs.end()),trn(i);
  }
  printf("%lli\n",*max_element(dp,dp+A+1));
}
/*
if we store the counts of each factor (possible gcd) of each a, we can solve
the problem using dynamic programming transitioning to factors of the current
state

this works because each factor of the current value will have at least the
same count as the current value and, as count denotes the number of
ocurrences in each gcd(a[0], a[1], ..., a[i - 1]), we can simply take the
difference in counts and treat it as the cost of "extending" the existing
sequence ending with the current value
*/