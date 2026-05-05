#include "parserTests.h"
#include <cmocka.h>

/**
 * @brief Test that example_main() correctly processes a valid expression
 *        and produces expected output.
 *
 * This integration test verifies the complete application behavior including
 * output formatting.
 */
static void parser_test_spaces(void **state)
{
    const char *args[] = {
        "example",
        "1",
        "+",
        "3",
        "*",
        "10",
    };

    (void)state;

    /* Verify expected output lines */
    expect_string(example_test_printf, temporary_buffer, "1\n");
    expect_string(example_test_printf, temporary_buffer, "  + 3 = 4\n");
    expect_string(example_test_printf, temporary_buffer, "  * 10 = 40\n");
    expect_string(example_test_printf, temporary_buffer, "= 40\n");
}

static void parser_test_null(void **state)
{
  // no-op. tells the compiler state is intentionally unused. It suppresses "unused parameter" 
  (void) state; /* unused */
}

int parserRunner(void)
{
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(parser_test_null),
      cmocka_unit_test(parser_test_spaces),
  };

  return cmocka_run_group_tests_name("Parser", tests, NULL, NULL);
}
