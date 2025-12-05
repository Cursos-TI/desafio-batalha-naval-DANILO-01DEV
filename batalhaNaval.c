#include <stdio.h>

// --- CONSTANTES ---
#define TAMANHO 10       // Tamanho fixo do tabuleiro principal 10x10
#define TAMANHO_NAVIO 3  // Tamanho fixo do navio (3 posições)
#define HAB_TAMANHO 5   // Tamanho fixo das matrizes de habilidade 
#define HAB_CENTRO 2     // Índice central
#define AGUA 0           // Valor para representar a água
#define NAVIO 3          // Valor para representar as partes do navio
#define HABILIDADE 5     // VALOR: Área afetada pela habilidade 

int main() {
    printf("\n--- TABULEIRO BATALHA NAVAL ---\n");
    
    int tabuleiro[TAMANHO][TAMANHO] = {AGUA};
    int matriz_cone[HAB_TAMANHO][HAB_TAMANHO] = {AGUA};
    int matriz_cruz[HAB_TAMANHO][HAB_TAMANHO] = {AGUA};
    int matriz_octaedro[HAB_TAMANHO][HAB_TAMANHO] = {AGUA};
    
    int i, j, k; // Variáveis de controle de loops
    
    // 1. CONSTRUÇÃO DAS MATRIZES DE HABILIDADE 
    for (i = 0; i < HAB_TAMANHO; i++) {
        for (j = 0; j < HAB_TAMANHO; j++) {
            // Cone
            if (j >= (HAB_CENTRO - i) && j <= (HAB_CENTRO + i) && i < HAB_CENTRO + 1) {
                 matriz_cone[i][j] = 1;
            }
            // Cruz
            if (i == HAB_CENTRO || j == HAB_CENTRO) {
                matriz_cruz[i][j] = 1;
            }
            // Octaedro (Losango)
            int dist_i = (i >= HAB_CENTRO) ? (i - HAB_CENTRO) : (HAB_CENTRO - i);
            int dist_j = (j >= HAB_CENTRO) ? (j - HAB_CENTRO) : (HAB_CENTRO - j);
            if (dist_i + dist_j <= HAB_CENTRO) {
                matriz_octaedro[i][j] = 1;
            }
        }
    }

    // 2. POSICIONAMENTO DOS NAVIOS 

    int navio1_linha = 1, navio1_coluna = 1; 
    int navio2_linha = 4, navio2_coluna = 8; 
    int navio3_linha = 7, navio3_coluna = 1; 
    int navio4_linha = 7, navio4_coluna = 8; 
    
    for (k = 0; k < TAMANHO_NAVIO; k++) {
        tabuleiro[navio1_linha][navio1_coluna + k] = NAVIO; 
        tabuleiro[navio2_linha + k][navio2_coluna] = NAVIO; 
        tabuleiro[navio3_linha + k][navio3_coluna + k] = NAVIO; 
        tabuleiro[navio4_linha + k][navio4_coluna - k] = NAVIO; 
    }

    // 3. SOBREPOSIÇÃO DAS HABILIDADES 
    
    // Coordenadas DISTANTES para garantir que as formas sejam visíveis.
    int origem_cone_lin = 2, origem_cone_col = 2; 
    int origem_cruz_lin = 3, origem_cruz_col = 7; 
    int origem_octaedro_lin = 7, origem_octaedro_col = 4; 

    int dest_lin, dest_col;
    
    // PROJEÇÃO DO CONE
    for (i = 0; i < HAB_TAMANHO; i++) {
        for (j = 0; j < HAB_TAMANHO; j++) {
            if (matriz_cone[i][j] == 1) {
                dest_lin = origem_cone_lin + i - HAB_CENTRO;
                dest_col = origem_cone_col + j - HAB_CENTRO;                
                if (dest_lin >= 0 && dest_lin < TAMANHO && dest_col >= 0 && dest_col < TAMANHO) {
                    tabuleiro[dest_lin][dest_col] = HABILIDADE; 
                }
            }
        }
    }

    // PROJEÇÃO DA CRUZ
    for (i = 0; i < HAB_TAMANHO; i++) {
        for (j = 0; j < HAB_TAMANHO; j++) {
            if (matriz_cruz[i][j] == 1) {
                dest_lin = origem_cruz_lin + i - HAB_CENTRO;
                dest_col = origem_cruz_col + j - HAB_CENTRO;

                if (dest_lin >= 0 && dest_lin < TAMANHO && dest_col >= 0 && dest_col < TAMANHO) {
                    tabuleiro[dest_lin][dest_col] = HABILIDADE; 
                }
            }
        }
    }

    // PROJEÇÃO DO OCTAEDRO/LOSANGO
    for (i = 0; i < HAB_TAMANHO; i++) {
        for (j = 0; j < HAB_TAMANHO; j++) {
            if (matriz_octaedro[i][j] == 1) {
                dest_lin = origem_octaedro_lin + i - HAB_CENTRO;
                dest_col = origem_octaedro_col + j - HAB_CENTRO;
                
                if (dest_lin >= 0 && dest_lin < TAMANHO && dest_col >= 0 && dest_col < TAMANHO) {
                    tabuleiro[dest_lin][dest_col] = HABILIDADE; 
                }
            }
        }
    }

    // 4. EXIBIÇÃO FINAL 
    
    printf("\n   "); 
    for (char c = 'A'; c < 'A' + TAMANHO; c++) {
        printf(" %c ", c);
    }
    printf("\n");

    for (i = 0; i < TAMANHO; i++) { 
        printf("%2d ", i + 1); 
        for (j = 0; j < TAMANHO; j++) {
            printf(" %d ", tabuleiro[i][j]); 
        }
        printf("\n");
    }

    return 0;
}
