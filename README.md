<h1>Simulação de Realização de Exames de Raio-X</h1>
<hr>
Este projeto é um sistema de simulação para gerenciamento de pacientes e exames em um hospital, incluindo o gerenciamento de máquinas e a geração de laudos. A seguir, você encontrará instruções sobre como executar o programa, uma descrição dos principais Tipos Abstratos de Dados (TADs) usados e as principais decisões de implementação.

Passo a Passo para Executar o Programa:

Compilação:
Certifique-se de ter o gcc e o make instalado, e que o gcc está adicionado ao PATH.
Utilize o Makefile para compilar o programa. No terminal, navegue até o diretório do projeto e execute:

make
(caso esteja usando Windows e o mingw, execute: mingw32-make.)

Após a compilação, você pode executar o arquivo main.c:

./main

Ao rodar o código mais de uma vez, lembre-se de excluir os arquivos .txt, para não dar conflito nos relatórios
<hr>

<h2>Principais TADs</h2>

<b>Patient</b>

Representa um paciente com os seguintes atributos:
id: Identificação única do paciente.
name: Nome do paciente.
timestamp: Horário de chegada do paciente.

<b>Queue</b>

Representa uma fila de pacientes:
inicio: Ponteiro para o início da fila.
final: Ponteiro para o final da fila.

<b>Exam</b>

Representa um exame com os seguintes atributos:
id: Identificação única do exame.
id_rx: Identificação da máquina que realizou o exame.
patient_id: Identificação do paciente.
condition_IA: Diagnóstico feito pela IA.
nivel_gravidade: Nível de gravidade do exame.
timestamp: Horário do exame.

<b>QueueExam</b>

Representa uma fila de exames com prioridade:
inicio: Ponteiro para o início da fila.
final: Ponteiro para o final da fila.

<b>Report</b>

Representa um laudo gerado a partir de um exame:
id: Identificação única do laudo.
exam_id: Identificação do exame relacionado.
patient_id: Identificação do paciente.
condition: Condição final determinada.
timestamp: Horário em que o laudo foi gerado.

<b>MachineManager</b>

Gerencia as máquinas de exame:
id_maquina: IDs das máquinas.
status_maquina: Status das máquinas (disponível ou ocupada).
tempo_inicio_exame: Tempo de início do exame em cada máquina.
paciente_maquina: Paciente alocado em cada máquina.

<hr>

<h2>Principais Decisões de Implementação</h2>

<b>Gerenciamento de Pacientes e Exames:</b>

Pacientes são enfileirados em uma fila e alocados em uma das máquinas disponíveis.
Exames são realizados por uma máquina, e os resultados são enfileirados em uma fila de exames com prioridade, baseada no nível de gravidade do exame.

<b>Simulação e Relatórios</b>

O programa simula a chegada de pacientes e a realização de exames ao longo do tempo.
Relatórios periódicos são gerados para fornecer informações sobre o número de pacientes, exames realizados e a porcentagem de exames que geraram laudos.
Foi criado um arquivo unico para gerar o relatorio de tempo médio de laudo por condição. Nele existem funções que percorrem os os arquivos db_report.txt e db_exam.txt, 
para apartir do exam_id e o timestamp fazer o calculo da média de tempo que cada condição permanece na fila de prioridade.

<b>Arquivos de Dados</b>

Dados de pacientes e exames são salvos em arquivos de texto (db_patient.txt e db_exam.txt, respectivamente) para persistência.

<hr>
Dica: para executar o programa mais rapidamente, altere no final do arquivo main de sleep(UNIDADE_DE_TEMPO); para usleep(UNIDADE_DE_TEMPO), dessa forma cada unidade de tempo terá um microssegundo.
Grupo: Thiago Fabiano e Livia Hombre
