#include <stdio.h>
#include <string.h>

typedef struct {
    int registro;
    char tipo[50];
    char modelo[50];
    char fabricante[50];
    float valorPorDia;
} Maquina;

float calcularValorTotal(Maquina maquina, int dias) {
    return maquina.valorPorDia * dias;
}

int buscarMaquinaPorRegistro(Maquina maquinas[], int tamanho, int registroBuscado) {
    for (int i = 0; i < tamanho; i++) {
        if (maquinas[i].registro == registroBuscado) {
            return i;
        }
    }
    return -1;
}

void preencherDados(Maquina *maquinas, int numMaquinas);

void listarMaquinasPorTipo(Maquina maquinas[], int numMaquinas, const char tipoBuscado[50]) {
    int maquinasEncontradas = 0;
    
    if (tipoBuscado[0] == '\0') {
        for (int i = 0; i < numMaquinas; i++) {
            printf("Maquina %d:\n", i + 1);
            printf("Registro: %d\n", maquinas[i].registro);
            printf("Tipo: %s\n", maquinas[i].tipo);
            printf("Modelo: %s\n", maquinas[i].modelo);
            printf("Fabricante: %s\n", maquinas[i].fabricante);
            printf("Valor por dia de aluguel: %.2f\n", maquinas[i].valorPorDia);
        }
    } else {
        for (int i = 0; i < numMaquinas; i++) {
            if (strcmp(maquinas[i].tipo, tipoBuscado) == 0) {
                maquinasEncontradas++;
                printf("Maquina %d:\n", maquinasEncontradas);
                printf("Registro: %d\n", maquinas[i].registro);
                printf("Tipo: %s\n", maquinas[i].tipo);
                printf("Modelo: %s\n", maquinas[i].modelo);
                printf("Fabricante: %s\n", maquinas[i].fabricante);
                printf("Valor por dia de aluguel: %.2f\n", maquinas[i].valorPorDia);
            }
        }
        
        if (maquinasEncontradas == 0) {
            printf("Nao existem maquinas do tipo '%s'.\n", tipoBuscado);
        }
    }
}

int main() {
    int opcao;
    int numMaquinas = 0;
    int tamanhoMaximo = 100;
    Maquina maquinas[tamanhoMaximo];

    do {
        printf("\nMenu de Opcoes:\n");
        printf("1. Informar numero de maquinas\n");
        printf("2. Preencher dados das maquinas\n");
        printf("3. Exibir SubMenu\n");
        printf("4. Encerrar o programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Informe o numero de maquinas: ");
                scanf("%d", &numMaquinas);
                break;
            case 2:
                if (numMaquinas == 0) {
                    printf("Antes de preencher os dados, informe o numero de maquinas.\n");
                } else if (numMaquinas <= tamanhoMaximo) {
                    preencherDados(maquinas, numMaquinas);
                } else {
                    printf("Numero de maquinas excede o tamanho maximo.\n");
                }
                break;
            case 3:
                if (numMaquinas == 0) {
                    printf("Antes de escolher esta opcao, informe o numero de maquinas e preencha os dados.\n");
                } else {
                    int submenuFlag = 1;

                    while (submenuFlag) {
                        printf("\nSubMenu:\n");
                        printf("1. Entrar com um novo conjunto de maquinas\n");
                        printf("2. Listar maquinas de um determinado tipo\n");
                        printf("3. Pesquisar uma maquina pelo registro\n");
                        printf("4. Voltar ao menu principal\n");
                        printf("Escolha uma opcao: ");
                        int opcaoSubMenu; 
                        scanf("%d", &opcaoSubMenu);
                        switch (opcaoSubMenu) { 
                            case 1:
                                printf("\n--- Entrando com dados de maquinas ---\n");
                                preencherDados(maquinas, numMaquinas);
                                break;
                            case 2:
                                char tipoBuscado[50];
                                printf("Informe o tipo de maquina a ser listado (ou deixe em branco para listar todas): ");
                                scanf("%s", tipoBuscado);
                                listarMaquinasPorTipo(maquinas, numMaquinas, tipoBuscado);
                                break;
                            case 3: {
                                int registroBuscado;
                                printf("Informe o numero de registro da maquina: ");
                                scanf("%d", &registroBuscado);

                                int indice = buscarMaquinaPorRegistro(maquinas, numMaquinas, registroBuscado);
                                if (indice != -1) {
                                    printf("Maquina encontrada:\n");
                                    printf("Registro: %d\n", maquinas[indice].registro);
                                    printf("Tipo: %s\n", maquinas[indice].tipo);
                                    printf("Modelo: %s\n", maquinas[indice].modelo);
                                    printf("Fabricante: %s\n", maquinas[indice].fabricante);
                                    printf("Valor por dia de aluguel: %.2f\n", maquinas[indice].valorPorDia);

                                    int dias;
                                    printf("Informe o numero de dias de aluguel: ");
                                    scanf("%d", &dias);

                                    float valorTotal = calcularValorTotal(maquinas[indice], dias);
                                    printf("Valor total do contrato de aluguel: %.2f\n", valorTotal);
                                } else {
                                    printf("Maquina nao encontrada.\n");
                                }
                                break;
                            }
                            case 4:
                                printf("Voltando ao menu principal.\n");
                                submenuFlag = 0;
                                break;
                            default:
                                printf("Opcao inexistente, digite uma opcao valida.\n");
                                break;
                        }
                    }
                }
                break;
            case 4:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao inexistente, digite uma opcao valida.\n");
                break;
        }
    } while (opcao != 4);

    return 0;
}

void preencherDados(Maquina *maquinas, int numMaquinas) {
    for (int i = 0; i < numMaquinas; i++) {
        printf("Informe os dados da maquina %d:\n", i + 1);
        printf("Numero de Registro: ");
        scanf("%d", &maquinas[i].registro);
        printf("Tipo da Maquina: ");
        scanf("%s", maquinas[i].tipo);
        printf("Modelo da Maquina: ");
        scanf("%s", maquinas[i].modelo);
        printf("Fabricante: ");
        scanf("%s", maquinas[i].fabricante);
        printf("Valor por dia de aluguel: ");
        scanf("%f", &maquinas[i].valorPorDia);
    }
}