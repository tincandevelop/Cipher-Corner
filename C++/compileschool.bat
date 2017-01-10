SET PATH=D:\Programs\MinGW\bin
g++ "without gui.cpp" "Analysis/Analysis.cpp" "Analysis/Spaces.cpp" "Ciphers/Caesar.cpp" "Ciphers/Monoalphabetic.cpp" "Ciphers/Transposition.cpp" "Ciphers/Vigenere.cpp" -static-libgcc -std=c++11 -o "Cipher Corner.exe"
pause
START main.exe
