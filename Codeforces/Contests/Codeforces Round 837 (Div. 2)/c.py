def gcd(a,b):
  if b>0:
    return gcd(b,a%b)
  else:
    return a
def lcm(a,b):
  return a*b/gcd(a,b)
t=int(input())
for i in range(t):
  n=int(input())
  res=False
  x,y=1,1
  a_arr=list(map(int,input().split()))
  for a in a_arr:
    x=x*a
    y=lcm(y,a)
  if x!=y:
    print("YES")
  else:
    print("NO")