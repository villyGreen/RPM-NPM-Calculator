#include <check.h>
#include "smartCalc.h"
#include <string.h>
#include <math.h>

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
    char * searchString = "12^3*321,1";
    double res = calculator(searchString,strlen(searchString),&set,0);
    double origin_res = pow(12,3) * 321.1;
    ck_assert_double_eq(origin_res, res);
}
END_TEST

START_TEST(test_calc_3) {
    charactersSet set;
    char * searchString = "cos(5 * 11 * sin(tan(5)))";
    double res = calculator(searchString,strlen(searchString),&set,0);
    double origin_res = cosl(5 * 11 * sinl(tan(5)));
    ck_assert_float_eq(origin_res, res);
}
END_TEST

START_TEST(test_calc_4) {
    charactersSet set;
    char * searchString = "sqrt(99*4*cos(5))";
    double res = calculator(searchString,strlen(searchString),&set,0);
    double origin_res = sqrtl(99 * 4 * cos(5));
    ck_assert_double_eq(origin_res, res);
}
END_TEST

START_TEST(test_calc_5) {
    charactersSet set;
    char * searchString = "acos(0,5)*asin(1)*atan(2)";
    double res = calculator(searchString,strlen(searchString),&set,0);
    double origin_res = acosl(0.5) * asinl(1) * atanl(2);
    
    ck_assert_double_eq(origin_res, res);
}
END_TEST

START_TEST(test_calc_6) {
    charactersSet set;
    double res = 0;
    char * searchString = "acos(,)*asin(1)*atan(2)";
    set =  validator(searchString,strlen(searchString));
    if (set.errors == IS_EMPTY_FEEL || set.errors == IS_SYNTAX_ERROR) {
        res = 0;
    } else {
        res = calculator(searchString,strlen(searchString),&set,0);
    }
    
    double origin_res = 0;
    ck_assert_double_eq(origin_res, res);
}
END_TEST

START_TEST(test_calc_7) {
    charactersSet set;
    double res = 0;
    char * searchString = "123-098.11--09++()";
    set =  validator(searchString,strlen(searchString));
    if (set.errors == IS_EMPTY_FEEL || set.errors == IS_SYNTAX_ERROR) {
        res = 0;
    } else {
        res = calculator(searchString,strlen(searchString),&set,0);
    }
    
    double origin_res = 0;
    ck_assert_double_eq(origin_res, res);
}
END_TEST

START_TEST(test_calc_8) {
    charactersSet set;
    double res = 0;
    char * searchString = "321";
    set =  validator(searchString,strlen(searchString));
    if (set.errors == IS_EMPTY_FEEL || set.errors == IS_SYNTAX_ERROR) {
        res = 0;
    } else {
        res = calculator(searchString,strlen(searchString),&set,0);
    }
    
    double origin_res = 0;
    ck_assert_double_eq(origin_res, res);
}
END_TEST

START_TEST(test_calc_9) {
    charactersSet set;
    double res = 0;
    char * searchString = "sin(1 * cos(4)";
    set =  validator(searchString,strlen(searchString));
    if (set.errors == IS_EMPTY_FEEL || set.errors == IS_SYNTAX_ERROR) {
        res = 0;
    } else {
        res = calculator(searchString,strlen(searchString),&set,0);
    }
    
    double origin_res = 0;
    ck_assert_double_eq(origin_res, res);
}
END_TEST

START_TEST(test_calc_10) {
    charactersSet set;
    double res = 0;
    char * searchString = "^12 * 123";
    set =  validator(searchString,strlen(searchString));
    if (set.errors == IS_EMPTY_FEEL || set.errors == IS_SYNTAX_ERROR) {
        res = 0;
    } else {
        res = calculator(searchString,strlen(searchString),&set,0);
    }
    
    double origin_res = 0;
    ck_assert_double_eq(origin_res, res);
}
END_TEST

START_TEST(test_calc_11) {
    charactersSet set;
    double res = 0;
    char * searchString = "x";
    set =  validator(searchString,strlen(searchString));
    if (set.errors == IS_EMPTY_FEEL || set.errors == IS_SYNTAX_ERROR) {
        res = 0;
    } else {
        res = calculator(searchString,strlen(searchString),&set,0);
    }
    
    double origin_res = 0;
    ck_assert_double_eq(origin_res, res);
}
END_TEST

START_TEST(test_calc_12) {
    charactersSet set;
    double res = 0;
    char * searchString = "mod";
    set =  validator(searchString,strlen(searchString));
    if (set.errors == IS_EMPTY_FEEL || set.errors == IS_SYNTAX_ERROR) {
        res = 0;
    } else {
        res = calculator(searchString,strlen(searchString),&set,0);
    }
    
    double origin_res = 0;
    ck_assert_double_eq(origin_res, res);
}
END_TEST

START_TEST(test_calc_13) {
    charactersSet set;
    double res = 0;
    char * searchString = "123.2-";
    set =  validator(searchString,strlen(searchString));
    if (set.errors == IS_EMPTY_FEEL || set.errors == IS_SYNTAX_ERROR) {
        res = 0;
    } else {
        res = calculator(searchString,strlen(searchString),&set,0);
    }
    
    double origin_res = 0;
    ck_assert_double_eq(origin_res, res);
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
    tcase_add_test(tc1_1, test_calc_4);
    tcase_add_test(tc1_1, test_calc_5);
    tcase_add_test(tc1_1, test_calc_6);
    tcase_add_test(tc1_1, test_calc_7);
    tcase_add_test(tc1_1, test_calc_8);
    tcase_add_test(tc1_1, test_calc_9);
    tcase_add_test(tc1_1, test_calc_10);
    tcase_add_test(tc1_1, test_calc_11);
    tcase_add_test(tc1_1, test_calc_12);
    tcase_add_test(tc1_1, test_calc_13);
    
    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return nf == 0 ? 0 : 1;
}
