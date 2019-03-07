all: out

out:
  g++ -o out ./Sem6/IndustrialProgramming/Task1/main.cpp
test: out
  echo "nice"
