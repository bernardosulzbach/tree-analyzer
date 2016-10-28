# A script to execute LLVM reformatting.
SECONDS=0

COMPILATION_DATABASE="compile_commands.json"

# Create the symbolic link we need.
if [ ! -f $COMPILATION_DATABASE ]; then
  ln -s build/compile_commands.json
fi

echo Reformatting...
clang-format -i src/*.[hc]

echo "Done after $SECONDS seconds."
