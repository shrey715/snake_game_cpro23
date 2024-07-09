#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
// Necessary due to static functions in state.c
#include "state.c"

/* Look at asserts.c for some helpful assert functions */

  int greater_than_forty_two(int x) {
    return x > 42;
  }

  bool is_vowel(char c) {
    char* vowels = "aeiouAEIOU";
    for (int i = 0; i < strlen(vowels); i++) {
      if (c == vowels[i]) {
        return true;
      }
    }
    return false;
  }

  /*
    Example 1: Returns true if all test cases pass. False otherwise.
      The function greater_than_forty_two(int x) will return true if x > 42. False otherwise.
      Note: This test is NOT comprehensive
  */
  bool test_greater_than_forty_two() {
    int testcase_1 = 42;
    bool output_1 = greater_than_forty_two(testcase_1);
    if (!assert_false("output_1", output_1)) {
      return false;
    }

    int testcase_2 = -42;
    bool output_2 = greater_than_forty_two(testcase_2);
    if (!assert_false("output_2", output_2)) {
      return false;
    }

    int testcase_3 = 4242;
    bool output_3 = greater_than_forty_two(testcase_3);
    if (!assert_true("output_3", output_3)) {
      return false;
    }

    return true;
  }

  /*
    Example 2: Returns true if all test cases pass. False otherwise.
      The function is_vowel(char c) will return true if c is a vowel (i.e. c is a,e,i,o,u)
      and returns false otherwise
      Note: This test is NOT comprehensive
  */
  bool test_is_vowel() {
    char testcase_1 = 'a';
    bool output_1 = is_vowel(testcase_1);
    if (!assert_true("output_1", output_1)) {
      return false;
    }

    char testcase_2 = 'e';
    bool output_2 = is_vowel(testcase_2);
    if (!assert_true("output_2", output_2)) {
      return false;
    }

    char testcase_3 = 'i';
    bool output_3 = is_vowel(testcase_3);
    if (!assert_true("output_3", output_3)) {
      return false;
    }

    char testcase_4 = 'o';
    bool output_4 = is_vowel(testcase_4);
    if (!assert_true("output_4", output_4)) {
      return false;
    }

    char testcase_5 = 'u';
    bool output_5 = is_vowel(testcase_5);
    if (!assert_true("output_5", output_5)) {
      return false;
    }

    char testcase_6 = 'k';
    bool output_6 = is_vowel(testcase_6);
    if (!assert_false("output_6", output_6)) {
      return false;
    }

    return true;
  }

/* Task 4.1 */

bool test_is_tail() {
  // TODO: Implement this function.
  char testcase_1 = 'a';
    bool output_1 = is_tail(testcase_1);
    if (!assert_true("output_1", output_1)) {
      return false;
    }

    char testcase_2 = 'w';
    bool output_2 = is_tail(testcase_2);
    if (!assert_true("output_2", output_2)) {
      return false;
    }

    char testcase_3 = 's';
    bool output_3 = is_tail(testcase_3);
    if (!assert_true("output_3", output_3)) {
      return false;
    }

    char testcase_4 = 'd';
    bool output_4 = is_tail(testcase_4);
    if (!assert_true("output_4", output_4)) {
      return false;
    }

    char testcase_5 = 'u';
    bool output_5 = is_tail(testcase_5);
    if (!assert_false("output_5", output_5)) {
      return false;
    }

    char testcase_6 = 'k';
    bool output_6 = is_tail(testcase_6);
    if (!assert_false("output_6", output_6)) {
      return false;
    }

    printf("Testcases for is_tail passed.\n");
    return true;
}

bool test_is_head() {
  // TODO: Implement this function.
  char testcase_1 = 'a';
    bool output_1 = is_tail(testcase_1);
    if (!assert_true("output_1", output_1)) {
      return false;
    }

    char testcase_2 = 'w';
    bool output_2 = is_tail(testcase_2);
    if (!assert_true("output_2", output_2)) {
      return false;
    }

    char testcase_3 = 's';
    bool output_3 = is_tail(testcase_3);
    if (!assert_true("output_3", output_3)) {
      return false;
    }

    char testcase_4 = 'd';
    bool output_4 = is_tail(testcase_4);
    if (!assert_true("output_4", output_4)) {
      return false;
    }

    char testcase_5 = 'u';
    bool output_5 = is_tail(testcase_5);
    if (!assert_false("output_5", output_5)) {
      return false;
    }

    char testcase_6 = 'k';
    bool output_6 = is_tail(testcase_6);
    if (!assert_false("output_6", output_6)) {
      return false;
    }

    printf("Testcases for is_head passed.\n");
    return true;
}

bool test_is_snake() {
  // TODO: Implement this function.
  char right_testcases[] = "WASDwasd<>v^";

  for(int i = 0; i < 12; i++){ //? TEST CASES 1-12 
    bool output = is_snake(right_testcases[i]);
    char statement[100];
    sprintf(statement, "%s%d", "output_", i+1);
    if (!assert_true(statement, output)) {
      return false;
    }
  }

  char wrong_testcases[] = "ijklmjoIJKLMNO";
  for(int i = 0; i < 12; i++){ //? TEST CASES 12-24
    bool output = is_snake(wrong_testcases[i]);
    char statement[100];
    sprintf(statement, "%s%d", "output_", i+13);
    if (!assert_false("output", output)) {
      return false;
    }
  }

  printf("Testcases for is_snake passed.\n");
  return true;
}

bool test_body_to_tail() {
  // TODO: Implement this function.
  char testcases[] = "<>v^hjkylopxzq";
  char expected[] =  "adsw??????????";
  for(int i = 0; i < 14; i++){
    char output = body_to_tail(testcases[i]);
    char statement[100];
    sprintf(statement, "%s%d", "output_", i+1);
    if (!assert_equals_char(statement, expected[i], output)) {
      return false;
    }
  }

  printf("Testcases for body_to_tail passed.\n");
  return true;
}

bool test_head_to_body() {
  // TODO: Implement this function.
  char testcases[] = "WASD123456789asdfghjklqwertyui";
  char expected[] =  "^<v>??????????????????????????";
  for(int i = 0; i < 30; i++){
    char output = head_to_body(testcases[i]);
    char statement[100];
    sprintf(statement, "%s%d", "output_", i+1);
    if (!assert_equals_char(statement, expected[i], output)) {
      return false;
    }
  }

  printf("Testcases for head_to_body passed.\n");
  return true;
}

bool test_get_next_row() {
  // TODO: Implement this function.
  char right_testcases[] = "^wW<AavSs>Dd";
  int curr_row = 4;
  int expected1[] = {3, 3, 3, 4, 4, 4, 5, 5, 5, 4, 4, 4};

  for(int i = 0; i < 12; i++){
    int output = get_next_row(right_testcases[i], curr_row);
    char statement[100];
    sprintf(statement, "%s%d", "output_", i+1);
    if (!assert_equals_int(statement, expected1[i], output)) {
      return false;
    }
  }

  return true;
}

bool test_get_next_col() {
  // TODO: Implement this function.
  char right_testcases[] = "^wW<AavSs>Dd";
  int curr_col = 4;
  int expected[] = {4, 4, 4, 3, 3, 3, 4, 4, 4, 5, 5, 5};
  
  for(int i = 0 ; i < 12; i++){
    int output = get_next_col(right_testcases[i], curr_col);
    char statement[100];
    sprintf(statement, "%s%d", "output_", i+1);
    if (!assert_equals_int(statement, expected[i], output)) {
      return false;
    }
  }
  
  return true;
}

bool test_customs() {
  if (!test_greater_than_forty_two()) {
    printf("%s\n", "test_greater_than_forty_two failed.");
    return false;
  }
  if (!test_is_vowel()) {
    printf("%s\n", "test_is_vowel failed.");
    return false;
  }
  if (!test_is_tail()) {
    printf("%s\n", "test_is_tail failed");
    return false;
  }
  if (!test_is_head()) {
    printf("%s\n", "test_is_head failed");
    return false;
  }
  if (!test_is_snake()) {
    printf("%s\n", "test_is_snake failed");
    return false;
  }
  if (!test_body_to_tail()) {
    printf("%s\n", "test_body_to_tail failed");
    return false;
  }
  if (!test_head_to_body()) {
    printf("%s\n", "test_head_to_body failed");
    return false;
  }
  if (!test_get_next_row()) {
    printf("%s\n", "test_get_next_row failed");
    return false;
  }
  if (!test_get_next_col()) {
    printf("%s\n", "test_get_next_col failed");
    return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  init_colors();

  if (!test_and_print("custom", test_customs)) {
    return 0;
  }

  return 0;
}
