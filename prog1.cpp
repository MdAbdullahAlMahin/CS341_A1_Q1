#include <iostream>
using namespace std;


void printArr(int n, long long * xs){
  for (int i = 0; i < n; i++){
    cout << xs[i] << " ";
  }
  cout << endl;
}

long long * calc(int op ,int n, long long * xs, long long * ys)
{
  long long * ret = new long long[n + 1];
  for (int i = 0; i < n + 1; i++)
  {
    if (op){
      ret[i] = xs[i] + ys[i];
    }
    else{
      ret[i] = xs[i] - ys[i];
    }
  }
  return ret;
}

long long * initializeArr(int n){
  long long * ret = new long long[n];
  for (int i = 0; i < n; i++){
    ret[i] = 0;
  }
  return ret;
}

long long * subArray(int l, int r, long long * xs, long long * ret){
  for (int i = 0; i < r; i++)
  {
    ret[i] = xs[l + i];
  }
  return ret;
}

long long * normalize(int l, int r, long long * xs){
  long long * ret = initializeArr(2 * r + 1);
  for (int i = 0; i < 2 * l - 1; i++)
  {
    ret[i] = xs[i];
  }
  return ret;
}

long long *kara(int terms, long long *xs, long long *ys)
{
  int ans_terms = 2 * terms - 1;
  int l = terms / 2;
  int r = terms - l;
  long long * ans = initializeArr(ans_terms);
  if (terms == 1)
  {
    ans[0] = xs[0] * ys[0];
    return ans;
  }
  long long *xl = subArray(0,l,xs,initializeArr(r));
  long long *xr = subArray(l,r,xs,initializeArr(r));
  long long *yl = subArray(0,l,ys,initializeArr(r));
  long long *yr = subArray(l,r,ys,initializeArr(r));

  long long *left = kara(l, xl, yl);
  long long *cross_temp_1 = kara(r, calc(1,r, xl, xr), calc(1, r, yl, yr));
  long long *right = kara(r, xr, yr);

  long long *leftn = normalize(l, r, left);

  long long *cross = calc(0, 2 * r - 1, calc(0, 2 * r - 1, cross_temp_1, leftn), right);

  for (int i = 0; i < 2 * r - 1; i++)
  {
    ans[i] += leftn[i];
    ans[i + l] += cross[i];
    ans[i + 2 * l] += right[i];
  }

  return ans;
}

int main()
{
  int n;
  cin >> n;
  long long *xs = new long long[n + 1];
  long long *ys = new long long[n + 1];
  for (int i = 0; i < n + 1; i++)
    cin >> xs[i];
  for (int i = 0; i < n + 1; i++)
    cin >> ys[i];
  long long *ans = kara(n + 1, xs, ys);
  printArr(2 * n + 1, ans);
  return 0;
}