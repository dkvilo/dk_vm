# Build 
as out.S -o out.o

# Link
ld out.o -o out -L /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib/ -lSystem

# Run
./out

# Print
echo $?