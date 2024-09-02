#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "laudoPorCondicao.h"


// Funçao para ler o arquivo db_report.txt
int lerArquivoDeLaudos(const char *nomeArquivo, ReportR **reports) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo db_report.txt");
        return -1;
    }

    int size = 0;
    int capacity = 10;
    *reports = (ReportR *)malloc(capacity * sizeof(ReportR));

    while (fscanf(file, "id: %d\nexam_id: %d\ncondition: %[^\n]\ntimestamp: %d\n-------------------------\n",
                  &(*reports)[size].id, &(*reports)[size].exam_id, (*reports)[size].condition, &(*reports)[size].timestamp) == 4) {
        size++;

        // Aumenta a capacidade do array dinamicamente, se necessário
        if (size >= capacity) {
            capacity *= 2;
            *reports = (ReportR *)realloc(*reports, capacity * sizeof(ReportR));
        }
    }

    fclose(file);
    return size; // Retorna o número de registros lidos
}

// Funçao para ler o arquivo de_exam.txt
int lerArquivoDeExames(const char *nomeArquivo, ExamR **exams) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo de_exam.txt");
        return -1;
    }

    int size = 0;
    int capacity = 10;
    *exams = (ExamR *)malloc(capacity * sizeof(ExamR));

    while (fscanf(file, "id: %d\nxr_id: %d\npatient_id: %d\ncondition_IA: %[^\n]\ntimestamp: %d\n-------------------------\n",
                  &(*exams)[size].id, &(*exams)[size].xr_id, &(*exams)[size].patient_id, (*exams)[size].condition_IA, &(*exams)[size].timestamp) == 5) {
        size++;

       
        if (size >= capacity) {
            capacity *= 2;
            *exams = (ExamR *)realloc(*exams, capacity * sizeof(ExamR));
        }
    }

    fclose(file);
    return size; 
}
int encontrarExamePorID(ExamR *exams, int numExams, int exam_id) {
    for (int i = 0; i < numExams; i++) {
        if (exams[i].id == exam_id) {
            return i;
        }
    }
    return -1; 
}

void imprimirTempoMedioDeLaudoPorCondicao(){
    ReportR *reports = NULL;
    ExamR *exams = NULL;
    int reportCount, contadorExames;

    reportCount = lerArquivoDeLaudos("db_report.txt", &reports);

    
    contadorExames = lerArquivoDeExames("db_exam.txt", &exams);

    // Alocaçao dinâmica para armazenar as diferenças de unidade de tempo para cada condicao
    int *temposCovid = NULL, *temposTuberculose = NULL, *temposCancerDePulmao = NULL;
    int *temposBronquite = NULL, *temposPneumonia = NULL, *temposSaudeNormal = NULL;
    int *temposEmboliaPulmonar = NULL, *temposDerramePleural = NULL, *temposFibrosePulmonar = NULL;
    int contadorCovid = 0, contadorTuberculose = 0, contadorCancerDePulmao = 0;
    int contadorBronquite = 0, contadorPneumonia = 0, contadorSaudeNormal = 0;
    int contadorEmboliaPulmonar = 0, contadorDerramePleural = 0, contadorFibrosePulmonar = 0;
    int covidCapacity = 10, tuberculosisCapacity = 10, lungCancerCapacity = 10;
    int bronchitisCapacity = 10, pneumoniaCapacity = 10, normalHealthCapacity = 10;
    int pulmonaryEmbolismCapacity = 10, pleuralEffusionCapacity = 10, pulmonaryFibrosisCapacity = 10;

    // Inicializa os arrays dinâmicos
    temposCovid = (int *)malloc(covidCapacity * sizeof(int));
    temposTuberculose = (int *)malloc(tuberculosisCapacity * sizeof(int));
    temposCancerDePulmao = (int *)malloc(lungCancerCapacity * sizeof(int));
    temposBronquite = (int *)malloc(bronchitisCapacity * sizeof(int));
    temposPneumonia = (int *)malloc(pneumoniaCapacity * sizeof(int));
    temposSaudeNormal = (int *)malloc(normalHealthCapacity * sizeof(int));
    temposEmboliaPulmonar = (int *)malloc(pulmonaryEmbolismCapacity * sizeof(int));
    temposDerramePleural = (int *)malloc(pleuralEffusionCapacity * sizeof(int));
    temposFibrosePulmonar = (int *)malloc(pulmonaryFibrosisCapacity * sizeof(int));

    // Processa cada report
    for (int i = 0; i < reportCount; i++) {
        int examIndex = encontrarExamePorID(exams, contadorExames, reports[i].exam_id);
        if (examIndex != -1) {
            int diferencaDeTempo = reports[i].timestamp - exams[examIndex].timestamp;

            // Verifica e expande os arrays dinâmicos se necessário
            if (strcmp(reports[i].condition, "COVID") == 0) {
                if (contadorCovid >= covidCapacity) {
                    covidCapacity *= 2;
                    temposCovid = (int *)realloc(temposCovid, covidCapacity * sizeof(int));
                }
                temposCovid[contadorCovid++] = diferencaDeTempo;
            } else if (strcmp(reports[i].condition, "Tuberculose") == 0) {
                if (contadorTuberculose >= tuberculosisCapacity) {
                    tuberculosisCapacity *= 2;
                    temposTuberculose = (int *)realloc(temposTuberculose, tuberculosisCapacity * sizeof(int));
                }
                temposTuberculose[contadorTuberculose++] = diferencaDeTempo;
            } else if (strcmp(reports[i].condition, "Cancer de pulmao") == 0) {
                if (contadorCancerDePulmao >= lungCancerCapacity) {
                    lungCancerCapacity *= 2;
                    temposCancerDePulmao = (int *)realloc(temposCancerDePulmao, lungCancerCapacity * sizeof(int));
                }
                temposCancerDePulmao[contadorCancerDePulmao++] = diferencaDeTempo;
            } else if (strcmp(reports[i].condition, "Bronquite") == 0) {
                if (contadorBronquite >= bronchitisCapacity) {
                    bronchitisCapacity *= 2;
                    temposBronquite = (int *)realloc(temposBronquite, bronchitisCapacity * sizeof(int));
                }
                temposBronquite[contadorBronquite++] = diferencaDeTempo;
            } else if (strcmp(reports[i].condition, "Pneumonia") == 0) {
                if (contadorPneumonia >= pneumoniaCapacity) {
                    pneumoniaCapacity *= 2;
                    temposPneumonia = (int *)realloc(temposPneumonia, pneumoniaCapacity * sizeof(int));
                }
                temposPneumonia[contadorPneumonia++] = diferencaDeTempo;
            } else if (strcmp(reports[i].condition, "Saude Normal") == 0) {
                if (contadorSaudeNormal >= normalHealthCapacity) {
                    normalHealthCapacity *= 2;
                    temposSaudeNormal = (int *)realloc(temposSaudeNormal, normalHealthCapacity * sizeof(int));
                }
                temposSaudeNormal[contadorSaudeNormal++] = diferencaDeTempo;
            } else if (strcmp(reports[i].condition, "Embolia pulmonar") == 0) {
                if (contadorEmboliaPulmonar >= pulmonaryEmbolismCapacity) {
                    pulmonaryEmbolismCapacity *= 2;
                    temposEmboliaPulmonar = (int *)realloc(temposEmboliaPulmonar, pulmonaryEmbolismCapacity * sizeof(int));
                }
                temposEmboliaPulmonar[contadorEmboliaPulmonar++] = diferencaDeTempo;
            } else if (strcmp(reports[i].condition, "Derrame pleural") == 0) {
                if (contadorDerramePleural >= pleuralEffusionCapacity) {
                    pleuralEffusionCapacity *= 2;
                    temposDerramePleural = (int *)realloc(temposDerramePleural, pleuralEffusionCapacity * sizeof(int));
                }
                temposDerramePleural[contadorDerramePleural++] = diferencaDeTempo;
            } else if (strcmp(reports[i].condition, "Fibrose pulmonar") == 0) {
                if (contadorFibrosePulmonar >= pulmonaryFibrosisCapacity) {
                    pulmonaryFibrosisCapacity *= 2;
                    temposFibrosePulmonar = (int *)realloc(temposFibrosePulmonar, pulmonaryFibrosisCapacity * sizeof(int));
                }
                temposFibrosePulmonar[contadorFibrosePulmonar++] = diferencaDeTempo;
            }
        }
    }

    // Cálculo e impressao das médias
    int somaCovid = 0, somaTuberculose = 0, somaCancerDePulmao = 0;
    int somaBronquite = 0, somaPneumonia = 0, somaSaudeNormal = 0;
    int somaEmboliaPulmonar = 0, somaDerramePleural = 0, somaFibrosePulmonar = 0;


    // Tempo medio de laudo pela condicao: Saúde Normal
    for (int i = 0; i < contadorSaudeNormal; i++) {
        somaSaudeNormal += temposSaudeNormal[i];
    }
    if (contadorSaudeNormal) {
        printf("Tempo medio de laudo pela condicao: Saude Normal: %d\n", somaSaudeNormal / contadorSaudeNormal);
    } else {
        printf("Tempo medio de laudo pela condicao: Saude Normal: Nao houve pacientes com essa condicao.\n");
    }

    // Tempo medio de laudo pela condicao: Bronquite
    for (int i = 0; i < contadorBronquite; i++) {
        somaBronquite += temposBronquite[i];
    }
    if (contadorBronquite) {
        printf("Tempo medio de laudo pela condicao: Bronquite: %d\n", somaBronquite / contadorBronquite);
    } else {
        printf("Tempo medio de laudo pela condicao: Nao houve pacientes com essa condicao.\n");
    }

    // Tempo medio de laudo pela condicao: Pneumonia
    for (int i = 0; i < contadorPneumonia; i++) {
        somaPneumonia += temposPneumonia[i];
    }
    if (contadorPneumonia) {
        printf("Tempo medio de laudo pela condicao: Pneumonia: %d\n", somaPneumonia / contadorPneumonia);
    } else {
        printf("Tempo medio de laudo pela condicao: Nao houve pacientes com essa condicao.\n");
    }

    // Tempo medio de laudo pela condicao: COVID
    for (int i = 0; i < contadorCovid; i++) {
        somaCovid += temposCovid[i];
    }
    if (contadorCovid) {
        printf("Tempo medio de laudo pela condicao: COVID: %d\n", somaCovid / contadorCovid);
    } else {
        printf("Tempo medio de laudo pela condicao: Nao houve pacientes com essa condicao.\n");
    }

    // Tempo medio de laudo pela condicao: Embolia Pulmonar
    for (int i = 0; i < contadorEmboliaPulmonar; i++) {
        somaEmboliaPulmonar += temposEmboliaPulmonar[i];
    }
    if (contadorEmboliaPulmonar) {
        printf("Tempo medio de laudo pela condicao: Embolia Pulmonar: %d\n", somaEmboliaPulmonar / contadorEmboliaPulmonar);
    } else {
        printf("Tempo medio de laudo pela condicao: Nao houve pacientes com essa condicao.\n");
    }

    // Tempo medio de laudo pela condicao: Derrame Pleural
    for (int i = 0; i < contadorDerramePleural; i++) {
        somaDerramePleural += temposDerramePleural[i];
    }
    if (contadorDerramePleural) {
        printf("Tempo medio de laudo pela condicao: Derrame Pleural: %d\n", somaDerramePleural / contadorDerramePleural);
    } else {
        printf("Tempo medio de laudo pela condicao: Nao houve pacientes com essa condicao.\n");
    }

    // Tempo medio de laudo pela condicao: Fibrose Pulmonar
    for (int i = 0; i < contadorFibrosePulmonar; i++) {
        somaFibrosePulmonar += temposFibrosePulmonar[i];
    }
    if (contadorFibrosePulmonar) {
        printf("Tempo medio de laudo pela condicao: Fibrose Pulmonar: %d\n", somaFibrosePulmonar / contadorFibrosePulmonar);
    } else {
        printf("Tempo medio de laudo pela condicao: Nao houve pacientes com essa condicao.\n");
    }

    // Tempo medio de laudo pela condicao: Tuberculose
    for (int i = 0; i < contadorTuberculose; i++) {
        somaTuberculose += temposTuberculose[i];
    }
    if (contadorTuberculose) {
        printf("Tempo medio de laudo pela condicao: Tuberculose: %d\n", somaTuberculose / contadorTuberculose);
    } else {
        printf("Tempo medio de laudo pela condicao: Nao houve pacientes com essa condicao.\n");
    }

    // Tempo medio de laudo pela condicao: Câncer de Pulmao
    for (int i = 0; i < contadorCancerDePulmao; i++) {
        somaCancerDePulmao += temposCancerDePulmao[i];
    }
    if (contadorCancerDePulmao) {
        printf("Tempo medio de laudo pela condicao: Cancer de Pulmao: %d\n", somaCancerDePulmao / contadorCancerDePulmao);
    } else {
        printf("Tempo medio de laudo pela condicao: Nao houve pacientes com essa condicao.\n");
    }

    
    // Libera a memória alocada dinamicamente
    free(reports);
    free(exams);
    free(temposCovid);
    free(temposTuberculose);
    free(temposCancerDePulmao);
    free(temposBronquite);
    free(temposPneumonia);
    free(temposSaudeNormal);
    free(temposEmboliaPulmonar);
    free(temposDerramePleural);
    free(temposFibrosePulmonar);
                
         
}