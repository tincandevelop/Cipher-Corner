SET PATH=F:\Programs\MinGW\bin
g++ -g main.cpp "Analysis/Analysis.cpp" "Analysis/Spaces.cpp" "Ciphers/Caesar.cpp" "Ciphers/Monoalphabetic.cpp" "Ciphers/Transposition.cpp" "Ciphers/Vigenere.cpp" -static-libgcc -std=c++11 -o ./main.exe
pause
gdb main.exe
