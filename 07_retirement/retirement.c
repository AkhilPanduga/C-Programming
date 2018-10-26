
#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double account_balance (int x, double y, retire_info z) {
  for (int i = 1; i <= z.months; i++) {
    printf ("Age %3d month %2d you have $%.2lf\n", x/12, x%12, y);
    y += (y * (z.rate_of_return/100)) + z.contribution;
    x++;
  }
  return y;
}

void retirement (int startAge, double initial, retire_info working, retire_info retired) {
  double w_savings = account_balance (startAge, initial, working);
  int retAge = startAge + working.months;
  account_balance (retAge, w_savings, retired);
}

int main(void) {
  int  age = 327;
  double savings = 21345;
  retire_info work;
  work.months = 489;
  work.contribution = 1000;
  work.rate_of_return = 4.5/(double)12;
  retire_info retire;
  retire.months = 384;
  retire.contribution = -4000;
  retire.rate_of_return = 1/(double)12;
  retirement (age, savings, work, retire);
  return EXIT_SUCCESS;
}
