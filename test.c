#include <check.h>
#include "smartCalc.h"
#include <string.h>
#include <math.h>
//#include <cairo.h>

START_TEST(test_calc_1) {
    charactersSet set;
    char * searchString = "43 + 2 + 6 * 3245/5";
    double res = calculator(searchString,strlen(searchString),&set,0);
    double origin_res = 43 + 2 + 6 * 3245/5;
    ck_assert_double_eq(origin_res, res);
}
END_TEST


START_TEST(test_calc_2) {
    charactersSet set;
    char * searchString = "12^3*3";
    double res = calculator(searchString,strlen(searchString),&set,0);
    double origin_res = pow(12,3) * 3;
    ck_assert_double_eq(origin_res, res);
}
END_TEST

START_TEST(test_calc_3) {
    charactersSet set;
    char * searchString = "cos(5 * 11 * sin(tan(5)))";
    double res = calculator(searchString,strlen(searchString),&set,0);
    printf("%.10lf\n",res);
    double origin_res = cos(5 * 11 * sin(tan(5)));
     printf("%.10lf\n",origin_res);
  
    ck_assert_msg(origin_res == res, "failed");
}
END_TEST


int main(void) {
  Suite *s1 = suite_create("Calculate_Operations");
  SRunner *sr = srunner_create(s1);
  int nf;

  TCase *tc1_1 = tcase_create("Calculate_Operations");
  suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, test_calc_1);
     tcase_add_test(tc1_1, test_calc_2);
        tcase_add_test(tc1_1, test_calc_3);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
