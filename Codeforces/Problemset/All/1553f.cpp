#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I A=3e5;
I a_arr[N];
Lli fens[3][A+2];
void upd(I t,I i,Lli val){
  for(;i<=A+1;i+=i&-i)fens[t][i]+=val;
}
Lli qry(I t,I i){
  Lli res=0;
  for(i=min(i,A+1);i>0;i-=i&-i)res+=fens[t][i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli res=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    res+=qry(0,a+1)+a*(i-qry(1,a+1))+a*qry(1,a+1)-qry(2,a+1);
    for(I j=a;j<=A;j+=a){
      res+=(qry(0,j+a)-qry(0,j))-j*(qry(1,j+a)-qry(1,j));
      upd(2,j+1,a);
    }
    upd(0,a+1,a),upd(1,a+1,1);
    printf("%lli ",res);
  }
}
/*
we can find the sum of a[i] % a[j] for all a[j] < a[i] and j < i by subtracting
the largest multiple of a[j] less than or equal to a[i] for each j < i from
the number of j < i multiplied by a[i]

this can be done using a point update range sum data structure, since the
largest multiple of a[j] less than or equal to any value x is the sum of a[j]
added at each multiple of a[j] index greater than 0 and less than or equal to x

we can also find the sum of a[j] % a[i] for all a[j] > a[i] and j < i by
subtracting the greatest multiple of a[i] no greater than a[j] from a[j]

this too can be done using a point update range sum data structure by querying
at each multiple of a[i] index k greater than 0 and less than or equal to
max(a) the sum of a[j] in [k, k + a[i]) and subtracting the number of a[j] in
[k, k + a[i]) multiplied by a[i]

finally, a[i] % a[j] for all a[j] > a[i] and a[j] % a[i] for all a[j] < a[i]
is simply a[i] and a[j] respectively, which can also be kept using a point
update range query data structure keeping counts
*/