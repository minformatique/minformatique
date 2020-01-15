/*
Simple fichier source en C pour montrer en quoi les appels de fonctions en C se traduisent en assembleur.

Contributeurs : Rezal P18
*/

int add(int a, int b);

int main(int argc, char const *argv[]) {
  int a = 1;
  int b = 2;
  int c = add(a, b);
  return c;
}

int add(int a, int b) {
  return a + b;
}
