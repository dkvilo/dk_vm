# Build 
nasm -felf64 out.S -o out.o

# Link
ld out.o -o out

# Run
./out

# Print
echo $?