#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

std::string MSG;

std::pair<int, int> readLength(std::ifstream &file);
int **readMatrix(std::ifstream &file, int nodes, int edges);
void printMatrix(int **matrix, int nodes, int edges);
void freeMatrix(int **matrix, int nodes);
std::pair<int, int> getNodes(int **matrix, int lenNodes, int edge);
void modifyMatrix(int **matrix, int nodes, int edges);
void saveMatrix(int **matrix, int nodes, int edges, bool &modified);
std::vector<std::string> getLabels(std::ifstream &file);

int main() {
  int optUser;
  int **matrix;
  int rowsNodes, colsEdges;
  bool modified = false;
  std::vector<std::string> labels;
  std::ifstream file("./../incidencia.txt");
  if (!file) {
    std::cerr << "No se pudo abrir el archivo." << std::endl;
    return 1;
  }

  std::cout << "--- MENU ---\n";
  std::cout << "1. Leer matriz desde el archivo\n";
  std::cout << "2. Imprimir la matriz\n";
  std::cout << "3. Modificar la matriz\n";
  std::cout << "4. Guardar la matriz\n";
  std::cout << "0. Salir\n";
  do {

    std::cout << "--- \\_._/ ---\n";
    std::cout << "Indicar la operacion que desea realizar: ";
    std::cin >> optUser;

    switch (optUser) {
    case 1:
      std::tie(rowsNodes, colsEdges) = readLength(file);
      matrix = readMatrix(file, rowsNodes, colsEdges);
      labels = getLabels(file);
      break;
    case 2:
      printMatrix(matrix, rowsNodes, colsEdges);
      break;
    case 3:
      modifyMatrix(matrix, rowsNodes, colsEdges);
      printMatrix(matrix, rowsNodes, colsEdges);
      modified = true;
      break;
    case 4:
      saveMatrix(matrix, rowsNodes, colsEdges, modified);
      std::cout << "Matriz guardada en el archivo." << std::endl;
      break;
    case 0:
      std::cout << "Saliendo del programa..." << std::endl;
      freeMatrix(matrix, rowsNodes);
      break;
    default:
      std::cout << "Opción no válida. Inténtalo de nuevo." << std::endl;
      break;
    };
  } while (optUser != 0);
  file.close();
  return 0;
}

std::pair<int, int> readLength(std::ifstream &file) {
  int rowsNodes, ColsEdges;
  file >> rowsNodes >> ColsEdges;
  return {rowsNodes, ColsEdges};
}

int **readMatrix(std::ifstream &file, int nodes, int edges) {
  int **matrix = new int *[nodes];
  for (int i = 0; i < nodes; ++i) {
    matrix[i] = new int[edges];
  }

  for (int i = 0; i < nodes; ++i) {
    for (int j = 0; j < edges; ++j) {
      file >> matrix[i][j];
    }
  }

  return matrix;
}

void printMatrix(int **matrix, int nodes, int edges) {
  for (int i = 0; i < nodes; ++i) {
    for (int j = 0; j < edges; ++j) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void freeMatrix(int **matrix, int nodes) {
  for (int i = 0; i < nodes; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

std::pair<int, int> getNodes(int **matrix, int lenNodes, int edge) {
  int nodeInit = 0;
  int nodeEnd = 0;
  for (int i = 0; i < lenNodes; i++) {
    if (matrix[i][edge] == 1) {
      if (nodeInit == 0) {
        nodeInit = i + 1;
      } else {
        nodeEnd = i + 1;
      }
    }
    if (nodeInit != 0 && nodeEnd != 0) {
      break;
    }
  }
  return {nodeInit, nodeEnd};
}

void modifyMatrix(int **matrix, int lenNodes, int lenEdges) {
  int modEdg;
  int newNodeI, newNodeE;

  std::cout << "Indique la arista que desea cambiar (entre 1 y " << lenEdges
            << "): ";
  std::cin >> modEdg;

  if (modEdg < 0 || modEdg > lenEdges) {
    std::cerr << "Arista no válida." << std::endl;
    return;
  }
  modEdg--;
  auto [nodeInit, nodeEnd] = getNodes(matrix, lenNodes, modEdg);
  std::cout << "La arista " << modEdg + 1 << " es incidente con los nodos "
            << nodeInit << " y " << nodeEnd << "\n";

  do {
    std::cout
        << "Indique a qué nodos desea que incida la arista ahora (entre 1 y "
        << lenNodes << "): ";
    std::cin >> newNodeI >> newNodeE;
  } while ((newNodeI < 1 || newNodeI > lenNodes || newNodeE < 1 ||
            newNodeE > lenNodes) ||
           (newNodeI == nodeInit && newNodeE == nodeEnd));

  for (int i = 0; i < lenNodes; ++i) {
    matrix[i][modEdg] = 0;
  }

  matrix[newNodeI - 1][modEdg] = 1;
  matrix[newNodeE - 1][modEdg] = 1;
}

void saveMatrix(int **matrix, int nodes, int edges, bool &modified) {
  std::ofstream saveFile("./../catch_incidence.txt", std::ios::app);

  if (!saveFile) {
    std::cerr << "Error al abrir el archivo, para guardar \n";
    return;
  }

  if (modified) {
    saveFile << "La matriz fue modificada, guardando en el archivo..." << "\n";
  }
  saveFile << "Matriz de incidencia (nodos: " << nodes << ", " << edges
           << ")\n";
  for (int i = 0; i < nodes; i++) {
    for (int j = 0; j < nodes; j++) {
      saveFile << matrix[i][j] << " ";
    }
    saveFile << "\n";
  };
  saveFile << "\n";
  modified = false;
}

std::vector<std::string> getLabels(std::ifstream &file) {}
