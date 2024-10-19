#include <bits/stdc++.h>

using namespace std;

int main() {
  int sixTab[1000000] = {0};
  int fiveTab[1000000] = {0};
  int fourTab[1000000] = {0};
  int threeTab[1000000] = {0};
  int twoTab[1000000] = {0};
  int oneTab[1000000] = {0};

  int m;
  cin >> m;

  for (int i = 0; i < m; i++) {
    int studentNumber, studentGrade;
    cin >> studentNumber >> studentGrade;

    if (studentGrade == 1) {
      oneTab[studentNumber]++;
    } else if (studentGrade == 2) {
      twoTab[studentNumber]++;
    } else if (studentGrade == 3) {
      threeTab[studentNumber]++;
    } else if (studentGrade == 4) {
      fourTab[studentNumber]++;
    } else if (studentGrade == 5) {
      fiveTab[studentNumber]++;
    } else if (studentGrade == 6) {
      sixTab[studentNumber]++;
    }
  }

  // One
  int maxGrade = 0;
  int studentNumber = -1;
  for (int i = 0; i < 1000000; i++) {
    if (oneTab[i] > maxGrade) {
      maxGrade = oneTab[i];
      studentNumber = i;
    }
  }

  if (maxGrade == 0) {
    cout << "BRAK" << " ";
  } else {
    cout << studentNumber << " ";
  }

  // Two
  maxGrade = 0;
  studentNumber = -1;
  for (int i = 0; i < 1000000; i++) {
    if (twoTab[i] > maxGrade) {
      maxGrade = twoTab[i];
      studentNumber = i;
    }
  }

  if (maxGrade == 0) {
    cout << "BRAK" << " ";
  } else {
    cout << studentNumber << " ";
  }

  // Three
  maxGrade = 0;
  studentNumber = -1;
  for (int i = 0; i < 1000000; i++) {
    if (threeTab[i] > maxGrade) {
      maxGrade = threeTab[i];
      studentNumber = i;
    }
  }

  if (maxGrade == 0) {
    cout << "BRAK" << " ";
  } else {
    cout << studentNumber << " ";
  }

  // Four
  maxGrade = 0;
  studentNumber = -1;
  for (int i = 0; i < 1000000; i++) {
    if (fourTab[i] > maxGrade) {
      maxGrade = fourTab[i];
      studentNumber = i;
    }
  }

  if (maxGrade == 0) {
    cout << "BRAK" << " ";
  } else {
    cout << studentNumber << " ";
  }

  // Five
  maxGrade = 0;
  studentNumber = -1;
  for (int i = 0; i < 1000000; i++) {
    if (fiveTab[i] > maxGrade) {
      maxGrade = fiveTab[i];
      studentNumber = i;
    }
  }

  if (maxGrade == 0) {
    cout << "BRAK" << " ";
  } else {
    cout << studentNumber << " ";
  }

  // Six
  maxGrade = 0;
  studentNumber = -1;
  for (int i = 0; i < 1000000; i++) {
    if (sixTab[i] > maxGrade) {
      maxGrade = sixTab[i];
      studentNumber = i;
    }
  }

  if (maxGrade == 0) {
    cout << "BRAK" << " ";
  } else {
    cout << studentNumber << " ";
  }
}