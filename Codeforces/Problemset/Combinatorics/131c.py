def bin(n,k):
  res=1
  for i in range(n-k+1,n+1):res*=i
  for i in range(1,k+1):res//=i
  return res
n,m,t=map(int,input().split())
res=0
for i in range(4,t):res+=bin(n,i)*bin(m,t-i)
print(res)