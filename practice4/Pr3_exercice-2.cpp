#include <cstdio>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

void showMatrix(int **arr, int rows, int cols);
void generateFileGraph(int **matrix, int rows, int cols,
                       std::vector<std::string> labels);

int main(int argc, char *argv[]) {
  std::ifstream inputFile("./../adyacencia.txt");
  int rows;
  int num;
  int **arr;
  std::string line;
  std::vector<std::string> labels;

  if (inputFile.is_open()) {
    if (getline(inputFile, line)) {
      rows = std::stoi(line);

      arr = new int *[rows];
      for (int i = 0; i < rows; i++) {
        arr[i] = new int[rows];
      }
    }
    if (getline(inputFile, line)) {
      std::istringstream iss(line);
      std::string label;
      while (iss >> label) {
        labels.push_back(label);
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
  generateFileGraph(arr, rows, rows, labels);
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

void generateFileGraph(int **matrix, int rows, int cols,
                       std::vector<std::string> labels) {
  std::ofstream dotFile("./../graph.dot");

  if (!dotFile) {
    std::cerr << "Hubo un problema al abrir el archivo";
  }

  dotFile << "graph G { \n";
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (matrix[i][j] == 1) {
        dotFile << "    " << labels[i] << " -- " << labels[j] << ";"
                << std::endl;
      }
    }
  }
  dotFile << "}" << std::endl;
  std::cout << "Se creo correctamente el archivo";
}
