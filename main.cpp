#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
void shift(int i, int count, double arrayint[], char arrayop[]) {
  for (int j = i + 1; j < count - 1; j++) {
    arrayint[j] = arrayint[j + 1];
  };
  for (int j = i; j < count - 2; j++) {
    arrayop[j] = arrayop[j + 1];
  };
}
double pow(double a, double b) {
  double rez = 1;
  for (int i = 0; i < (int)b; i++) {
    rez = rez * a;
  };
  return rez;
}
double mod(double a, double b) { return (int)a % (int)b; }
double add(double a, double b) { return a + b; }
double sub(double a, double b) { return a - b; }
double mul(double a, double b) { return a * b; }
double div(double a, double b) { return a / b; }
int main(int argc, char* argv[]) {
  string Main;
  string ch1;
  string ch2;
  string ch = "";
  double chisla[20];
  char znaki[20];
  Main = argv[1];
  int flag = 1;
  int PozOtkrSkobki = -1;
  int PozZakrSkobki = Main.length();
  int counter = 0;
  int k = 0;
  while (flag == 1) {
    for (int i = 0; i < Main.length(); i++) {
      if (Main[i] == '(') PozOtkrSkobki = i;
    }  //нашли самую внутреннюю скобку
    counter = PozOtkrSkobki;
    if (PozOtkrSkobki != -1) {
      while ((Main[counter]) != ')') {
        counter++;
      };
      PozZakrSkobki = counter;
    };  //нашли соответсвующую ей закрывающуюся скобку
    for (int i = (PozOtkrSkobki + 1); i < PozZakrSkobki; i++) {
      if ((Main[i] != '+') && (Main[i] != '-') && (Main[i] != '*') &&
          (Main[i] != '/') && (Main[i] != '^') && (Main[i] != '%')) {
        ch = ch + Main[i];
      }  //выделяем число
      else {
        k++;
        chisla[k - 1] = atof(ch.c_str());
        ch = "";
        znaki[k - 1] = Main[i];
      }
    }
    k++;
    chisla[k - 1] = atof(ch.c_str());
    ch = "";  //сформировали два массива (массив знаков внутри скобок и чисел
              //внутри скобок)
    for (int i = 0; i < k - 1; i++) {
      if (znaki[i] == '^') {
        chisla[i] = pow(chisla[i], chisla[i + 1]);
        shift(i, k, chisla, znaki);
        k--;
      }
    }

    for (int i = 0; i < k - 1; i++) {
      if (znaki[i] == '*') {
        chisla[i] = mul(chisla[i], chisla[i + 1]);
        shift(i, k, chisla, znaki);
        k--;
      }
    }
    for (int i = 0; i < k - 1; i++) {
      if (znaki[i] == '/') {
        chisla[i] = div(chisla[i], chisla[i + 1]);
        shift(i, k, chisla, znaki);
        k--;
      }
    }
    for (int i = 0; i < k - 1; i++) {
      if (znaki[i] == '%') {
        chisla[i] = mod(chisla[i], chisla[i + 1]);
        shift(i, k, chisla, znaki);
        k--;
      }
    }

    for (int i = 0; i < k - 1; i++) {
      if (znaki[i] == '+') {
        chisla[i] = add(chisla[i], chisla[i + 1]);
        shift(i, k, chisla, znaki);
        k--;
      }
    }
    for (int i = 0; i < k - 1; i++) {
      if (znaki[i] == '-') {
        chisla[i] = sub(chisla[i], chisla[i + 1]);
        shift(i, k, chisla, znaki);
        k--;
      }
    }
    k = 0;
    ostringstream strstr;
    strstr << chisla[0];
    string rez = strstr.str();
    string nach;
    for (int i = 0; i < PozOtkrSkobki; i++) {
      nach = nach + Main[i];
    }
    string end;
    int j = 0;
    for (int i = PozZakrSkobki + 1; i < Main.length(); i++) {
      end = end + Main[i];
    }
    Main = nach + rez + end;
    PozOtkrSkobki = -1;
    PozZakrSkobki = Main.length();
    flag = 0;
    for (int i = 0; i < Main.length(); i++) {
      if ((Main[i] == '+') || (Main[i] == '-') || (Main[i] == '*') ||
          (Main[i] == '/') || (Main[i] == '^') || (Main[i] == '%'))
        flag = 1;
    }
  }
  cout << Main << endl;
}
