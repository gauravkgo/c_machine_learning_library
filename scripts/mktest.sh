
#!/bin/bash

# Check that a path is provided

if [ ! $# -eq 1 ]; then
  echo "Error: Must provide one path for test folder."
  exit 1
fi

test_path="$1"

# Check that path doesn't already exist

cd ../test

if [ -d "$test_path" ]; then
  echo "Error: Test folder already exists."
  exit 1
fi

# Check that no existing folder in the path is a test leaf directory,
# specifically that no existing folder in the path contains "test.sh"

# Strip new directories from path so only existing directories are left

existing_path=$test_path
while [ ! -d $existing_path ]
do
  existing_path=$(dirname $existing_path)
done

# Check through each level in existing path that there is no "test.sh"

back_to_top=$PWD
current_level_existing_path=$existing_path
while [ $current_level_existing_path != "." ]
do
  if [ -f "$current_level_existing_path/test.sh" ]; then
    echo "Error: Cannot add a test subdirectory to an existing 'leaf-node' test directory."
    echo "(A 'test.sh' file must not be present in any existing directories in the given path 'test/$test_path'. However, 'test.sh' was found in the directory 'test/$current_level_existing_path'.)"
    exit 1
  else
    current_level_existing_path=$(dirname $current_level_existing_path)
  fi
done

# Create and populate the test directory

mkdir -p $test_path
cp -Rn ../templates/test_template/* $test_path

if [ $? -ne 0 ]; then
  echo "Failed to create test folder at test/$test_path"
  exit 1
fi

echo "Created test folder at test/$test_path"
