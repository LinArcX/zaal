//-- Installing: /usr/local/include/cmocka.h
//-- Installing: /usr/local/include/cmocka_pbc.h
//-- Installing: /usr/local/include/cmocka_version.h
//-- Installing: /usr/local/lib64/libcmocka.so.1.0.2
//-- Installing: /usr/local/lib64/libcmocka.so.0
//-- Installing: /usr/local/lib64/libcmocka.so


#include <cmocka.h>

/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
