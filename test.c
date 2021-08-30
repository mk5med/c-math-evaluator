#include <stdio.h>
#include "./parser.h"
void assert_eq(int val1, int val2, int *SUCCESS_COUNT, int *TOTAL_TEST_COUNT)
{
  (*TOTAL_TEST_COUNT)++;
  if (val1 == val2) (*SUCCESS_COUNT)++;
  else printf("Test failed: %d != %d\n", val1, val2);
}

void test_cases()
{
  int success_count = 0;
  int total_test_count = 0;
  printf("Simple test cases:\n");
  
  assert_eq(solve("-1"), -1, &success_count, &total_test_count);
  assert_eq(solve("1+1"), 1+1, &success_count, &total_test_count);
  assert_eq(solve("1-1"), 1-1, &success_count, &total_test_count);
  assert_eq(solve("2*2"), 2*2, &success_count, &total_test_count);
  assert_eq(solve("2*2*2"), 2*2*2, &success_count, &total_test_count);
  printf("\tTest cases passed: %d/%d\n", success_count, total_test_count);
  success_count = total_test_count = 0;

  printf("Test division:\n");
  assert_eq(solve("10/2"), 5, &success_count, &total_test_count);
  assert_eq(solve("3/-2"), 3/-2, &success_count, &total_test_count);
  printf("\tTest cases passed: %d/%d\n", success_count, total_test_count);
  success_count = total_test_count = 0;

  printf("Test complex expressions:\n");
  assert_eq(solve("1*2*3+2*2+2*2"), 1*2*3+2*2+2*2, &success_count, &total_test_count);
  assert_eq(solve("1+3*-1*2+1*4"), 1+3*-1*2+1*4, &success_count, &total_test_count);
  assert_eq(solve("1+1*2+1*-4"), 1+1*2+1*-4, &success_count, &total_test_count);
  printf("\tTest cases passed: %d/%d\n", success_count, total_test_count);
  success_count = total_test_count = 0;
}