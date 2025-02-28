
#!/bin/bash

# Make test executables if necessary

cd ../make
echo "\nBuilding tests...\n"
make test
if [ $? -ne 0 ]; then
  echo "Error: Failed to build tests."
  exit 1
fi

# Check path is valid test/testsuite
# Default to /test if no path provided

cd ..
test_root="test"
cd_back=$PWD

if [ $# -ge 1 ]; then
  test_root="${test_root}/${1}"
  if [ ! -d "$test_root" ]; then
    echo "Error: Path ${test_root} does not exist."
    exit 1
  fi
fi

# Find all leaf paths with tests (with test.sh)

test_leafs=$(find "$test_root" -type f -name "test.sh" -exec dirname {} \;)

# Run all tests and compare
# Create results folder at common ancestor testsuite/test folder

results_folder="${test_root}/results"
mkdir -p "$results_folder"
time_for_file=$(date +"%Y-%m-%d_%H-%M-%S")
time_for_text=$(date +"%Y-%m-%d %H:%M:%S")
results_file="${results_folder}/results_${time_for_file}.txt"
absolute_path_results_file="${cd_back}/${results_file}"
echo "\nTesting started on ${time_for_text}." | tee -a "${absolute_path_results_file}"
echo "––––––––––––––––––––––––––––––––" | tee -a "${absolute_path_results_file}"

total_tests=0
total_successes=0
total_failures=0
for test_leaf in $test_leafs; do
  cd "${test_leaf}"
  stdout_temp=$(mktemp)
  stderr_temp=$(mktemp)
  correct_stdout_file="correct_output.txt"
  correct_stderr_file="expected_errors.txt"
  does_test_pass=1
  echo "${test_leaf}/test.sh:\nTesting..." | tee -a "${absolute_path_results_file}"

  "./test.sh" > "$stdout_temp" 2> "$stderr_temp"

  if [ ! -e "$correct_stdout_file" ]; then
    echo "File ${correct_stdout_file} does not exist." | tee -a "${absolute_path_results_file}"
    does_test_pass=0
  elif [ "$(cat "$stdout_temp")" != "$(cat "$correct_stdout_file")" ]; then
    echo "Test standard output does not match with ${correct_stdout_file}." | tee -a "${absolute_path_results_file}"
    does_test_pass=0
  fi
  rm "$stdout_temp"

  if [ ! -e "$correct_stderr_file" ]; then
    echo "File ${correct_stderr_file} does not exist." | tee -a "${absolute_path_results_file}"
    does_test_pass=0
  elif [ "$(cat "$stderr_temp")" != "$(cat "$correct_stderr_file")" ]; then
    echo "Test standard error does not match with ${correct_stderr_file}." | tee -a "${absolute_path_results_file}"
    does_test_pass=0
  fi
  rm "$stderr_temp"

  if [ $does_test_pass -eq 1 ]; then
    ((total_successes++))
    echo "Passed!" | tee -a "${absolute_path_results_file}"
  else
    ((total_failures++))
    echo "Failed." | tee -a "${absolute_path_results_file}"
  fi
  ((total_tests++))
  echo "––––––––––––––––––––––––––––––––" | tee -a "${absolute_path_results_file}"

  cd "$cd_back"
done

echo "Summary:\n--  Total: ${total_tests}  --  Passed: ${total_successes}  --  Failed: ${total_failures}  --\n" | tee -a "${absolute_path_results_file}"
echo "The above test results are stored in ${results_file}.\n"
