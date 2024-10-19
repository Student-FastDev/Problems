#include <bits/stdc++.h>

using namespace std;

int stack[100000];

int top = -1;

void push(int a) {

  if (top < 99999) {

    stack[++top] = a;
  }
}

int pop() {

  if (top > -1) {

    return stack[top--];
  }

  return -1;
}

int size() { return top + 1; }

bool empty() { return top == -1; }

int main()

{

  int N;

  cin >> N;

  for (int i = 0; i < N; i++) {

    int A;

    cin >> A;

    if (A > 0) {

      push(A);
    }

    if (A == 0 && !empty()) {

      cout << pop() << " ";
    }
  }

  cout << endl;

  cout << size() << endl;
}