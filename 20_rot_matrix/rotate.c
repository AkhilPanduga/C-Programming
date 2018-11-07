
void rotate(char matrix[10][10]) {
  char temp[10][10];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      temp[i][j] = matrix[i][j];
    }
  }
  for (int k = 0; k < 10; k++) {
    for (int l = 0; l < 10; l++) {
      matrix[k][l] = temp[9 - l][k];
    }
  }
}
