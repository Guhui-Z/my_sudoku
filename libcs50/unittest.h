/*
* unittest.h - unit test for tile and grid modules
* Dartmouth College, CS50 22S
*/

#define START_TEST_CASE(name) int _failures=0; char * _testname=(name);

// expect condition 
#define EXPECT(x)                                               \
  if (!(x)) {                                                   \
    _failures++;                                                \
    printf("Fail %s Line %d: [%s]\n", _testname, __LINE__, #x); \
  }

#define END_TEST_CASE                                                   \
  if (_failures == 0) {                                                 \
    printf("PASS test %s\n\n", _testname);                              \
  } else {                                                              \
    printf("FAIL test %s with %d errors\n\n", _testname, _failures);    \
  }

#define TEST_RESULT (_failures)