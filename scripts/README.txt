
This directory contains scripts for ease of building and development.

mktest.sh:
Creates test/testsuite folders. To use, enter "./mktest.sh" followed by the
desired test path. The path must not already exist and must local/relative to
the project directory's "test" directory. The ending folder in the path will
become the unit test folder with relevant testing files, while all directories
up the path are testsuite folders. The ending test folder will be and should
remain as a leaf directory. User must provide leaf directory with a c file
with same title as the leaf directory name, and enter expected output and
error in the appropriate files.
Example:
"./mktest.sh test_functions/test_func_init/test_func_init_error"
- Creates testsuite folder "test_functions" if it doesn't exist already at the
  path PROJECT_ROOT/test/test_functions.
- Creates testsuite folder "test_func_init" under testsuite "test_functions"
  if it doesn't exist already.
- Creates leaf directory test folder "test_func_init_error" under testsuite
  "test_func_init".
- Populates "test_func_init" with all needed testing infrastructure.
- User must provide a c file "test_func_init.c".
- User must provide the c file's expected output "in correct_output.txt".
- User must provide the c file's expected errors "in expected_errors.txt".

test.sh:
Runs tests and stores results. To use, enter "./test.sh" followed by the
desired test root origin folder, or followed by nothing. The path must exist
local/relative to the project directory's "test" directory. Path can be a leaf
directory test folder, or any parent directory testsuite. If no path is
provided, then the project's "test" folder is the assumed default path. The
script builds any object, library, and test files or executables as necessary
via the Makefile under the project directory's "make" folder. After building,
the script runs all tests in all leaf directory test folders at any level
underneath the provided path, then stores results in a "results" folder at the
provided path. The results produced are a tally of all tests in which running
a test's built executable results in output and errors that match the expected
output and errors provided by user prior as txt files in the test folder.
Example:
"./test.sh test_functions/test_func_init"
- Runs Makefile to build library and test executables as necessary.
- Runs all tests in all leaf directory test folders at any level under the path
  PROJECT_ROOT/test/test_functions/test_func_init.
- At each leaf directory test folder, the main executable is run and has its
  output compared to "correct_output.txt" and has its errors compared to
  "expected_errors.txt".
- Tallies of successful comparisons are stored in a results file under a results
  folder at the path PROJECT_ROOT/test/test_functions/test_func_init/results.

clean.sh:
Runs clean operation as specified in Makefile under project's "make" folder.
Deletes any library and object files, as well as all test executable files.

********************************************************************************

