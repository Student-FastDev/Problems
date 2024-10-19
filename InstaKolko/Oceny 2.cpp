#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int studentGradesAverage[100000] = {0};
  int averageGrade = 0;
  int averageGradeNumber = 0;

  int N;
  cin >> N;

  int studentGrades[N];

  for (int i = 0; i < N; i++) {
    cin >> studentGrades[i];
    studentGradesAverage[studentGrades[i] + 1]++;
    studentGradesAverage[studentGrades[i] - 1]++;

    if (studentGradesAverage[studentGrades[i] + 1] > averageGrade) {
      averageGrade = studentGradesAverage[studentGrades[i] + 1];
      averageGradeNumber = studentGrades[i] + 1;
    }
    if (studentGradesAverage[studentGrades[i] - 1] > averageGrade) {
      averageGrade = studentGradesAverage[studentGrades[i] - 1];
      averageGradeNumber = studentGrades[i] - 1;
    }
  }

  cout << averageGrade;
}