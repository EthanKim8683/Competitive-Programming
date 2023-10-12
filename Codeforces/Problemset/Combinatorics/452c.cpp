#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I N=1000;
const I M=1000;
Lf prbs1[M+1];
Lf prbs2[M+1];
Lf prbs3[M+1];
Lf bin(I n,I k){
  if(n<0||k<0||n-k<0)return 0;
  Lf res=1;
  for(I i=1;i<=k;i++)res/=i;
  for(I i=n-k+1;i<=n;i++)res*=i;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<=m;i++)prbs1[i]=(Lf)i/n;
  for(I i=0;i<=m;i++)prbs2[i]=bin(m,i)*bin(n*m-m,n-i)/bin(n*m,n);
  Lf prb=0;
  for(I i=0;i<=m;i++)prb+=prbs1[i]*prbs2[i];
  for(I i=0;i<=m;i++)prbs3[i]=prbs1[i]*prbs2[i]/prb;
  Lf res=0;
  for(I i=0;i<=m;i++)res+=prbs3[i]*i/n;
  printf("%.16Lf\n",res);
}
/*
the probability of Alex successfully performing the trick is the probability
that a card is chosen from a deck containing i copies of said card, and that
Alex chooses one of those copies after re-shuffling

the probability a card is chosen from a deck of cards containing i copies of
the card can be solved using Bayes' rule, where P(A[i] | B) is the probability
there are i copies (A[i]) given a card is chosen (B)

let P(B | A[i]) equal i / n, P(A[i]) equal bin(m, i) * bin(n * m - m, n - i) /
bin(n * m, n), and P(B) be sum of P(B & A[i]) (P(B | A[i]) * P(A[i])) among all
A[i]

then, P(A[i] | B) will be equal to P(B | A[i]) * P(A[i]) / P(B)
*/