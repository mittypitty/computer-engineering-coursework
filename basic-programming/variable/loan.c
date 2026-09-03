#include <stdio.h>

int main()
{
    double loan_amount, profit_amount, installments_number, first_answer, second_answer;
    scanf("%lf" , &loan_amount);
    scanf("%lf" , &profit_amount);
    scanf("%lf" , &installments_number);
    first_answer = (loan_amount * profit_amount * (installments_number + 1))/2400;
    second_answer = (loan_amount + first_answer)/installments_number;
    printf("%.1lf\n" , first_answer);
    printf("%.1lf" , second_answer);
    return 0;
}