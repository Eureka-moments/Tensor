#include "tensor.hpp"
#include <bits/types/clock_t.h>
#include <bits/types/time_t.h>
#include <cstddef>
#include <iostream>
#include <ctime>
using namespace std;
int main() {
  size_t arr[20] = {0};
  size_t n = 0;
  // while (1) {
  cout << "input dimensions:" << endl;
  cin >> n;
  cout << endl << "input each num:" << endl;
  for (int i=0; i<n; i++) {
    cin>>arr[i];
  }

  clock_t start, end;
  // start=clock();
  // tensor<double>(arr,n);
  // end = clock();
  // cout<<end-start<<"ms"<<endl;
  // }
  int I = 1, J = 10, K = 10;
  cout<<"input 386 96 96:"<<endl;
  cin>>I>>J>>K;
  start=clock();
  double****a=(double****)tensor<double>(5,5,5,5);
  end = clock();
  cout << end - start << "ms" << endl;
  cout<<CLOCKS_PER_SEC<<endl;
  double index = 0.0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 5; k++) {
        for (int l = 0; l < 5; l++) {
          //a[i][j][k][l] = index;
          cout << a[i][j][k][l] << " ";
          index++;
        }
        cout << endl;
      }
      cout << endl;
    }
    cout << endl;
  }
  cout << endl;
  // start=clock();
  // double *b = (double *)tensor<double>(6000000);
  // end = clock();
  // cout<<end-start<<"ms"<<endl;
  // for (int i = 0; i < 2; i++) {
  //   b[i] = index++;
  //   cout << b[i] << " ";
  // }
  // cout << endl;
  std::cout << "hello" << std::endl;
}