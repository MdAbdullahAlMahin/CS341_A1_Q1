def breakNums(n, xs):
  return (xs[0 : n//2], xs[n//2 : n])

def calculate(op, xs, ys):
  ret = []
  xl = len(xs)
  yl = len(ys)
  n = max(xl,yl)
  if op == "ADD":
    for i in range(n):
      ret.append((xs[i] if i < xl else 0) + (ys[i] if i < yl else 0))
  else:
    for i in range(n):
      ret.append((xs[i] if i < xl else 0) - (ys[i] if i < yl else 0))
  return ret

def offset(n, xs):
  return [0 for i in range(n)] + xs

def multiply(n, xs, ys):
  if n == 1: 
    return [xs[0] * ys[0]]
  else:
    # x1, x2 = breakNums(n + 1, xs)
    # y1, y2 = breakNums(n + 1, ys)
    # x3 = calculate("ADD", x1, x2)
    # y3 = calculate("ADD", y1, y2)
    # x = multiply(len(x1), x1, y1)
    # y = multiply(len(x2), x2, y2)
    xy = calculate("SUB", calculate("SUB", multiply(len(x3), x3, y3), x), y)
    ans = calculate("ADD", x, 
                    calculate("ADD", offset((n//2) if n % 2 == 0 else (n // 2) + 1, xy), 
                              offset(n if n % 2 == 0 else n + 1, y)
                              )
                    )
    return ans

def printNums(a):
  s = ""
  for i in range(len(a) - 1):
    s += str(a[i]) + " "
  s += str(a[len(a) - 1])
  print(s)

def driver():
  n = int(input())
  xs = input().split()
  ys = input().split()
  for i in range(n):
    xs[i] = int(xs[i])
    ys[i] = int(ys[i])
  printNums(multiply(n, xs, ys))
driver()