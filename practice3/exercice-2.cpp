#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void showMatrix(int **arr, int rows, int cols);

int main(int argc, char *argv[]) {
  std::ifstream inputFile("./../sample.txt");
  int rows;
  int num;
  int **arr;
  std::string line;

  if (inputFile.is_open()) {
    if (getline(inputFile, line)) {
      rows = std::stoi(line);

      arr = new int *[rows];
      for (int i = 0; i < rows; i++) {
        arr[i] = new int[rows];
      }
    }
    int i = 0;
    while (std::getline(inputFile, line) && i < rows) {
      std::istringstream iss(line);
      for (int j = 0; j < rows; j++) {
        iss >> arr[i][j]; // Leer cada número de la línea
      }
      i++;
    }
    inputFile.close();
  }
  showMatrix(arr, rows, rows);
  return 0;
}

void showMatrix(int **arr, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols;
         j++) { // Cambié `rows` por `cols` para mayor claridad
      std::cout << arr[i][j] << " "; // Espacio para mejor formato
    }
    std::cout << "\n";
  }
}
