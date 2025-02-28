
#!/bin/bash

dir_name=$(basename "$PWD")
test_exec="./${dir_name}_executable"

"$test_exec"

