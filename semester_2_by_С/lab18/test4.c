#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "shell_sort.c"

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))

/* Тест 1: Сортировка уже отсортированного массива */
static void test_sorted_array(void **state) {
    (void)state;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int len = ARRAY_LEN(arr);
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    shellSort(arr, len);
    
    for (int i = 0; i < len; i++) {
        assert_int_equal(arr[i], expected[i]);
    }
}

/* Тест 2: Сортировка обратно отсортированного массива */
static void test_reverse_sorted(void **state) {
    (void)state;
    int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int len = ARRAY_LEN(arr);
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    shellSort(arr, len);
    
    for (int i = 0; i < len; i++) {
        assert_int_equal(arr[i], expected[i]);
    }
}

/* Тест 3: Сортировка случайного массива */
static void test_random_array(void **state) {
    (void)state;
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 45, 33, 77};
    int len = ARRAY_LEN(arr);
    int expected[] = {11, 12, 22, 25, 33, 34, 45, 64, 77, 90};
    
    shellSort(arr, len);
    
    for (int i = 0; i < len; i++) {
        assert_int_equal(arr[i], expected[i]);
    }
}

/* Тест 4: Сортировка с дубликатами */
static void test_duplicates(void **state) {
    (void)state;
    int arr[] = {5, 2, 8, 2, 9, 1, 5, 5, 3, 0};
    int len = ARRAY_LEN(arr);
    int expected[] = {0, 1, 2, 2, 3, 5, 5, 5, 8, 9};
    
    shellSort(arr, len);
    
    for (int i = 0; i < len; i++) {
        assert_int_equal(arr[i], expected[i]);
    }
}

/* Тест 5: Один элемент */
static void test_single_element(void **state) {
    (void)state;
    int arr[] = {42};
    int len = ARRAY_LEN(arr);
    
    shellSort(arr, len);
    
    assert_int_equal(arr[0], 42);
}

/* Тест 6: Пустой массив */
static void test_empty_array(void **state) {
    (void)state;
    int arr[] = {};
    int len = 0;
    
    shellSort(arr, len);
    assert_true(1);
}

/* Тест 7: Два элемента */
static void test_two_elements(void **state) {
    (void)state;
    int arr[] = {5, 1};
    int len = ARRAY_LEN(arr);
    int expected[] = {1, 5};
    
    shellSort(arr, len);
    
    assert_int_equal(arr[0], expected[0]);
    assert_int_equal(arr[1], expected[1]);
}

/* Главная функция с форматированным выводом */
int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_sorted_array),
        cmocka_unit_test(test_reverse_sorted),
        cmocka_unit_test(test_random_array),
        cmocka_unit_test(test_duplicates),
        cmocka_unit_test(test_single_element),
        cmocka_unit_test(test_empty_array),
        cmocka_unit_test(test_two_elements),
    };
    
    printf("\n===========================================\n");
    printf("     SHELL SORT UNIT TESTS (CMOCKA)\n");
    printf("===========================================\n\n");
    
    /* Исправленный вызов для новой версии cmocka */
    int failed = _cmocka_run_group_tests("Shell Sort Tests", tests, 
                                         sizeof(tests) / sizeof(tests[0]), 
                                         NULL, NULL);
    
    printf("\n===========================================\n");
    if (failed == 0) {
        printf("✓ RESULT: ALL TESTS PASSED (%zu tests)\n", sizeof(tests) / sizeof(tests[0]));
    } else {
        printf("✗ RESULT: %d TESTS FAILED\n", failed);
    }
    printf("===========================================\n");
    
    return failed;
}