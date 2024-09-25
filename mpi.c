#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <fcntl.h>

#define max 50
#define maxNome 60
#define maxSigla 10

typedef struct Pessoa Pessoa;
typedef struct Pessoa{
    char nome[maxNome];
    int idade;
};
typedef struct Professor Professor;
struct Professor{
    Pessoa pes;
    int codigo;
    char depto[maxSigla];
};
typedef struct Aluno Aluno;
struct Aluno{
    Pessoa pes;
    int matricula;
    int ano;
    char depto[maxSigla];
};
typedef struct TG TG;
struct TG{
    int codigo;
    int autor;
    int orientador;
    char titulo[maxNome];
    int qtdeVotos;
};
typedef struct Eleitor Eleitor;
struct Eleitor{
    char cpf[15];
    bool votou;
    int codigoTG;
};

Professor docentes[max];
int qtdeDocentes;

Aluno formandos[max];
int qtdeFormandos;

TG listaTGs[max];
int qtdeTGs;

Eleitor comissao[max];
int qtdeEleitores;

// verifica se um CPF é válido
bool verificarCPF(const char *cpf){
    int soma=0;
    int peso=10;
    int digito1, digito2;
    char cpfTemp[12];
    int j=0;
    for(int i=0;i<strlen(cpf);i++){
        if(isdigit(cpf[i])){
            cpfTemp[j++]=cpf[i];}
    } cpfTemp[j]='\0';
    if(strlen(cpfTemp)!=11){
        return false;
    }
    for(int i=0;i<11;i++){
        if (!isdigit(cpfTemp[i])){
            return false;}
    }
    for(int i=0;i<9;i++){
        soma+=(cpfTemp[i]-'0')*peso;
        peso--;
    } digito1=(soma*10)%11;
    if(digito1==10){
        digito1=0;}
    soma=0;
    peso=11;
    for (int i=0;i<10;i++){
        soma+=(cpfTemp[i]-'0')*peso;
        peso--;
    } digito2=(soma*10)%11;
    if(digito2==10){
        digito2=0;}
    if(digito1!=(cpfTemp[9]-'0') || digito2!=(cpfTemp[10]-'0')){
        return false;
    } return true;
}

// faz a leitura dos dados dos professores no arquivo "professor.txt"
void lerProfessores(){
    FILE *arq=fopen("professor.txt", "r");
    if(arq==NULL){
        printf("Arquivo professor.txt faltando.\n");
        exit(1);
    } fscanf(arq, "%d", &qtdeDocentes);
    for(int i=0;i<qtdeDocentes;i++){
        fscanf(arq, "%d %s %d %[^\n]", 
            &docentes[i].codigo, // cod professor
            docentes[i].depto, // departamento (ADS, AMS e etc)
            &docentes[i].pes.idade, // idade
            docentes[i].pes.nome); // nome completo
    } fclose(arq);
}

// faz a leitura dos dados dos alunos no arquivo "aluno.txt"
void lerAlunos(){
    FILE*arq=fopen("aluno.txt", "r");
    if(arq==NULL){
        printf("Arquivo aluno.txt faltando.\n");
        exit(1);
    } fscanf(arq, "%d", &qtdeFormandos);
    for(int i=0;i<qtdeFormandos;i++){
        fscanf(arq, "%d %d %s %d %[^\n]", 
            &formandos[i].matricula, // cod matricula 
            &formandos[i].ano, // ano (3)
            formandos[i].depto, // departamento (ADS, AMS e etc)
            &formandos[i].pes.idade, // idade
            formandos[i].pes.nome); // nome completo
    } fclose(arq);
}

// verifica se um professor existe
bool verProfessor(int codigo){
 for(int i=0;i<qtdeDocentes;i++){
        if (docentes[i].codigo==codigo){
            return true;
        }
    } return false;
}
// verifica se um aluno existe
bool verAluno(int matricula){
    for(int i=0;i<qtdeFormandos;i++){
        if(formandos[i].matricula==matricula){
            return true;
        }
    } return false;
}

// faz a leitura de TG específico
void lerTGs(const char *filename){
    FILE*arq=fopen(filename, "r");
    int qtdeTGsArquivo;
    if(arq==NULL){
        printf("Erro no arquivo %s.\n", filename);
        exit(1);
    } fscanf(arq, "%d", &qtdeTGsArquivo);
    for(int i=0;i<qtdeTGsArquivo;i++){
        int autor, orientador;
        if(fscanf(arq, "%d %d %d %[^\n]", 
                &listaTGs[qtdeTGs].codigo, // cod pi
                &autor, // cod aluno autor
                &orientador, // cod orientador
                listaTGs[qtdeTGs].titulo)!=4 // titulo
                ) 
                {
            printf("Erro ao ler o arquivo %s.\n", filename);
            exit(1);
        } 
        if(!verAluno(autor) || !verProfessor(orientador)){
            printf("Erro no arquivo %s.\n", filename);
            exit(1);
        } listaTGs[qtdeTGs].qtdeVotos=0;
        listaTGs[qtdeTGs].autor=autor;
        listaTGs[qtdeTGs].orientador=orientador;
        qtdeTGs++;
    }
    fclose(arq);
}

// faz a leitura dos dados da comissão no arquivo "comissao.txt"
void lerComissao(){
    FILE*arq=fopen("comissao.txt", "r");
    if(arq==NULL){
        printf("Arquivo comissao.txt faltando.\n");
        exit(1);
    } fscanf(arq, "%d", &qtdeEleitores);
    for(int i=0;i<qtdeEleitores;i++){
        fscanf(arq, "%s", comissao[i].cpf);
        comissao[i].votou=false;
    } fclose(arq);
}

// salva os votos em um arquivo "parcial.txt"
void salvarVotos(){
    FILE*arq=fopen("parcial.txt", "w");
    int votosContados=0;
    if(arq==NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    for(int i=0;i<qtdeEleitores;i++){
        if(comissao[i].votou){
            votosContados++;
        }
    } fprintf(arq, "%d\n", votosContados);
    for(int i=0;i<qtdeEleitores;i++){
        if(comissao[i].votou){
            fprintf(arq, "%s %d\n", 
                comissao[i].cpf, 
                comissao[i].codigoTG
            );
        }
    } fclose(arq);
}

// faz a leitura de um arquivo "parcial.txt"
void lerVotos(){
    FILE*arq=fopen("parcial.txt", "r");
    if(arq==NULL){
        printf("Arquivo parcial.txt faltando.\n");
        return;
    }
    int votosContados;
    fscanf(arq, "%d", &votosContados);
    for(int i=0;i<votosContados;i++){
        char cpf[15];
        int codigoTG;
        fscanf(arq, "%s %d", cpf, &codigoTG);
        for(int j=0;j<qtdeEleitores;j++){
            if(strcmp(comissao[j].cpf, cpf)==0){
                comissao[j].votou=true;
                comissao[j].codigoTG=codigoTG;
                for (int k=0;k<qtdeTGs;k++){
                    if (listaTGs[k].codigo==codigoTG){
                        listaTGs[k].qtdeVotos++;
                        break;
                    }
                } break;
            }
        }
    } fclose(arq);
}

// imprime os dados dos TGs
void imprimirTGs(){
    for(int i=0;i<qtdeTGs;i++){
        printf("Codigo: %d\n", listaTGs[i].codigo);
        printf("Titulo: %s\n", listaTGs[i].titulo);
        printf("Qtde Votos: %d\n", listaTGs[i].qtdeVotos);
        printf("\n");
    }
}

// gera o resultado da votação no arquivo "resultado.txt"
void gerarResultado(){
    FILE*arq=fopen("resultado.txt", "w");
    if(arq==NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;}
    int votosMax=0;
    int qtdeVencedores=0;
    for(int i=0;i<qtdeTGs;i++){
        if(listaTGs[i]. qtdeVotos>votosMax){
            votosMax=listaTGs[i].qtdeVotos;
            qtdeVencedores=1;
        } else if(listaTGs[i].qtdeVotos==votosMax){
            qtdeVencedores++;
        }
    } fprintf(arq, "PI vencedor\n");
    for(int i=0;i<qtdeTGs;i++){
        if(listaTGs[i].qtdeVotos==votosMax){
            fprintf(arq, "\nCodigo: %d\n", listaTGs[i].codigo);
            fprintf(arq, "Titulo: %s\n", listaTGs[i].titulo);
            for(int j=0;j<qtdeFormandos; j++){
                if(formandos[j].matricula==listaTGs[i].autor){
                    fprintf(arq, "Aluno: %s\n", formandos[j].pes.nome);
                    fprintf(arq, "Curso aluno: %s\n", formandos[j].depto);
                    break;
                }
            }
            for(int j=0;j<qtdeDocentes;j++){
                if(docentes[j].codigo==listaTGs[i].orientador){
                    fprintf(arq, "Orientador: %s\n", docentes[j].pes.nome);
                    fprintf(arq, "Depto orientador: %s\n", docentes[j].depto);
                    break;
                }
            } fprintf(arq, "Qtde Votos: %d\n", listaTGs[i].qtdeVotos);
        }
    }
    fprintf(arq, "\nEleitores presentes\n");
    for(int i=0;i<qtdeEleitores;i++){
        if(comissao[i].votou){
            fprintf(arq, "%s\n", comissao[i].cpf);
        }
    } fprintf(arq, "\nEleitores ausentes\n");
    for(int i=0;i<qtdeEleitores;i++){
        if (!comissao[i].votou){
            fprintf(arq, "%s\n", comissao[i].cpf);
        }
    } fclose(arq);
}

char msg[100] = "";
char MENU1(){
    printf("\033[H\033[J");
    printf("+---------------------------------------+\n");
    printf("|                Melhor PI              |\n");
    printf("|             MENU PRINCIPAL            |\n");
    printf("+---------------------------------------+\n");
    printf("| a) Iniciar nova votação               |\n");
    printf("| b) Continuar votação                  |\n");
    printf("| c) Sair                               |\n");
    printf("+---------------------------------------+\n");
    if(strlen(msg)>0){
        printf(" %s", msg);
    }
}
char MENU2(){
    printf("\033[H\033[J");
    printf("+---------------------------------------+\n");
    printf("|                Melhor PI              |\n");
    printf("|               MENU VOTACAO            |\n");
    printf("+---------------------------------------+\n");
    printf("| a) Entrar com voto                    |\n");
    printf("| b) Suspender votacao                  |\n");
    printf("| c) Concluir votacao                   |\n");
    printf("+---------------------------------------+\n");
    if(strlen(msg)>0){
        printf(" %s", msg);
    }
}

int main(){
    char opcao;
    char opcaoVotar;
    char cpf[15];
    int codigoTG;
    do{
       MENU1();
       scanf(" %c", &opcao);
        switch(opcao){
            case 'A':
            case 'a':
                lerProfessores();
                lerAlunos();
                lerTGs("tg_AMS.txt");
                lerTGs("tg_ADS.txt");
                lerTGs("tg_DSM.txt");
                lerTGs("tg_CEX.txt");
                lerTGs("tg_EMP.txt");
                lerTGs("tg_LOG.txt");
                lerTGs("tg_POL.txt");
                lerComissao();
                do {
                    MENU2();
                    scanf(" %c", &opcaoVotar);
                    switch(opcaoVotar){
                        case 'A':
                        case 'a':
                            printf("Digite o CPF do eleitor: ");
                            scanf("%s", cpf);
                            if(verificarCPF(cpf)){
                                bool eleitorEncontrado=false;
                                for(int i=0;i<qtdeEleitores;i++){
                                    if (strcmp(comissao[i].cpf,cpf)==0){
                                        eleitorEncontrado=true;
                                            if(comissao[i].votou){
                                                strcpy(msg, "Este eleitor ja votou.\n");
                                                break;
                                            }
                                            printf("Digite o codigo do TG: ");
                                            scanf("%d", &codigoTG);
                                            bool tgEncontrado=false;
                                            for(int j=0;j<qtdeTGs;j++){
                                                if(listaTGs[j].codigo==codigoTG){
                                                    comissao[i].codigoTG=codigoTG;
                                                    listaTGs[j].qtdeVotos++;
                                                    comissao[i].votou=true;
                                                    strcpy(msg, "Voto registrado com sucesso.\n");
                                                    tgEncontrado=true;
                                                    break;
                                                }
                                            }
                                            if(!tgEncontrado){
                                                strcpy(msg, "TG nao encontrado. Tente novamente.\n");
                                            }
                                            break; 
                                    }
                                }
                                if(!eleitorEncontrado){
                                    strcpy(msg, "Eleitor nao encontrado.\n");
                                }
                        } else{
                            sprintf(msg, "CPF %s invalido.\n", cpf);
                        }
                        break;
                        case 'B':
                        case 'b':
                            strcpy(msg, "Votacao suspensa. Voto salvo!\n");
                            salvarVotos();
                            break;
                        case 'C':
                        case 'c':
                            strcpy(msg, "Votacao concluida.\n");
                            gerarResultado();
                            break;
                    }
                } while(opcaoVotar!='C' && opcaoVotar!='c');
                break;
            case 'B':
            case 'b':
                lerVotos();
                strcpy(msg, "Continuando votacao gravada.\n");
                do{
                    MENU2();
                    scanf(" %c", &opcaoVotar);
                    switch(opcaoVotar){
                        case 'A':
                        case 'a':
                            printf("Digite o CPF do eleitor: ");
                            scanf("%s", cpf);
                            if(verificarCPF(cpf)){
                                bool eleitorEncontrado=false;
                                for(int i=0;i<qtdeEleitores;i++){
                                    if(strcmp(comissao[i].cpf,cpf)==0){
                                        eleitorEncontrado=true;
                                            if(comissao[i].votou){
                                                strcpy(msg, "Este eleitor ja votou.\n");
                                                break;
                                            }
                                            printf("Digite o codigo do TG: ");
                                            scanf("%d", &codigoTG);
                                            bool tgEncontrado=false;
                                            for(int j=0;j<qtdeTGs;j++){
                                                if(listaTGs[j].codigo==codigoTG){
                                                    comissao[i].codigoTG=codigoTG;
                                                    listaTGs[j].qtdeVotos++;
                                                    comissao[i].votou=true;
                                                    strcpy(msg, "Voto registrado com sucesso.\n");
                                                    tgEncontrado=true;
                                                    break;
                                                }
                                            }
                                            if(!tgEncontrado){
                                                strcpy(msg, "TG nao encontrado. Tente novamente.\n");
                                            }
                                            break; 
                                    }
                                }
                                if(!eleitorEncontrado){
                                    strcpy(msg, "Eleitor nao encontrado.\n");
                                }
                        } else{
                            sprintf(msg, "CPF %s invalido. Tente novamente.\n", cpf);
                        }
                        break;
                        case 'B':
                        case 'b':
                            strcpy(msg, "Votacao suspensa. Voto salvo!\n");
                            salvarVotos();
                            break;
                        case 'C':
                        case 'c':
                            strcpy(msg, "Votacao concluida.\n");
                            gerarResultado();
                            break;
                    }
                } while(opcaoVotar!='C' && opcaoVotar!='c');
                break;
            case 'C':
            case 'c':
                strcpy(msg, "Saindo...\n");
                break;
            default:
               strcpy(msg, "Opcao invalida. Tente novamente.\n");
               break;
        }
    } while (opcao!='C' && opcao!='c');
    return 0;
}