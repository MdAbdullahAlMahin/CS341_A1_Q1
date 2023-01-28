#include <iostream>

using namespace std;

long long *polynomialCalc(int size, long long *arr1, long long *arr2, char type)
{
  // declare and initialize result array
  long long *res = new long long[size + 1];
  for (int i = 0; i < size + 1; i++)
  {
    res[i] = 0;
  }

  // perform calculation based on type
  // addition
  if (type == 'A')
  {
    // add the two polynomials
    for (int i = 0; i < size + 1; i++)
    {
      res[i] = arr1[i] + arr2[i];
    }
  }
  // subtraction
  else if (type == 'S')
  {
    // subtract the two polynomials
    for (int i = 0; i < size + 1; i++)
    {
      res[i] = arr1[i] - arr2[i];
    }
  }

  return res;
}

void printArr(int n, long long * xs){
  for (int i = 0; i < n; i++){
    cout << xs[i] << " ";
  }
  cout << endl;
}

/**
 * @brief Karatsuba Polynomial Multiplication Algorithm
 *
 * @param N number of terms in the polynomials
 * @param x first polynomial
 * @param y second polynomial
 * @return long long * the product of the two polynomials
 */
long long *karatsubaPolynomialMult(int N, long long *a, long long *b)
{
  // declare and initialize result array
  long long *res = new long long[2 * N - 1];
  for (int i = 0; i < 2 * N - 1; i++)
  {
    res[i] = 0;
  }

  // base case
  if (N == 1)
  {
    res[0] = a[0] * b[0];
    return res;
  }

  // otherwise, split the polynomials into two halves
  int size1 = N / 2;
  int size2 = N - size1;

  // declare and initialize arrays to store split polynomials
  long long *a0 = new long long[size2];
  long long *a1 = new long long[size2];
  long long *b0 = new long long[size2];
  long long *b1 = new long long[size2];

  for (int i = 0; i < size2; i++)
  {
    a0[i] = 0;
    a1[i] = 0;
    b0[i] = 0;
    b1[i] = 0;
  }

  // split the polynomials
  for (int i = 0; i < size1; i++)
  {
    a0[i] = a[i];
    b0[i] = b[i];
  }
  for (int i = 0; i < size2; i++)
  {
    a1[i] = a[i + size1];
    b1[i] = b[i + size1];
  }

  long long *z0 = karatsubaPolynomialMult(size1, a0, b0);
  printArr(2 * size2 + 1, z0);
  long long *z1 = karatsubaPolynomialMult(size2, polynomialCalc(size2, a0, a1, 'A'), polynomialCalc(size2, b0, b1, 'A'));
  printArr(2 * size2 + 1, z1);
  long long *z2 = karatsubaPolynomialMult(size2, a1, b1);
  printArr(2 * size2 + 1, z2);

  long long *tempZ0 = new long long[2 * size2 - 1];
  for (int i = 0; i < 2 * size2 - 1; i++)
  {
    tempZ0[i] = 0;
  }

  for (int i = 0; i < 2 * size1 - 1; i++)
  {
    tempZ0[i] = z0[i];
  }

  z0 = tempZ0;

  // long long *temp1 = polynomialCalc(2 * size2 - 1, z1, z0, 'S');

  long long *temp = polynomialCalc(2 * size2 - 1, polynomialCalc(2 * size2 - 1, z1, z0, 'S'), z2, 'S');

  z1 = temp;

  for (int i = 0; i < 2 * size2 - 1; i++)
  {
    res[i] += z0[i];
    res[i + size1] += z1[i];
    res[i + 2 * size1] += z2[i];
  }

  return res;
}

int main()
{
  // store degree of polynomials
  int n = 0;
  cin >> n;
  // two arrays to store the coefficients of the polynomials
  long long *f = new long long[n + 1];
  long long *g = new long long[n + 1];
  // read in the coefficients of the polynomials
  for (int i = 0; i < n + 1; i++)
    cin >> f[i];

  for (int i = 0; i < n + 1; i++)
    cin >> g[i];

  // print the result

  long long *karatsubaRes = karatsubaPolynomialMult(n + 1, f, g);

  for (int i = 0; i < 2 * n + 1; i++)
  {
    cout << karatsubaRes[i] << " ";
  }

  delete[] f;
  delete[] g;

  return 0;
}