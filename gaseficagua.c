#include<stdio.h>
#include<locale.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define MAX_SENHA 6
#define MAX_LOGIN 50
#define CLEAN_BUFF do{ int c; while((c = getchar()) != '\n' && c != EOF);}while(0)

struct cadastro_dados{
    char nome[15][2];
    int cod[2],quant[2];
    float valor[2];
};
struct cadastro_dados cadastro;

int Usuario( FILE* file, char* user, char* senha ) //valida usuario
{
	char tmpLogin[MAX_LOGIN];
	char tmpSenha[MAX_SENHA];

	fscanf(file, "%s", tmpLogin);

	while( !feof(file) )
	{
		if( !strcmp(tmpLogin, user))
		{
			fscanf(file, "%s", tmpSenha);

			if( !strcmp(tmpSenha, senha))
				return 1;
		}
		else
		{
			fscanf(file, "%*s");
		}

		fscanf(file, "%s", tmpLogin);
	}

	return 0;
}

char* CriaSenha()
{
    register int i;

	char* senha = (char*)malloc(sizeof *senha * MAX_SENHA);

    for(i = 0; i < MAX_SENHA; i++)
	{
        senha[i] = getch();
        if(senha[i] == '\r')
            break;
        else
            printf("*");
    }
	senha[i] = '\0';

	return senha;
}

int login(){
    FILE*fpIN;

	int option;

	char *user  = (char*)malloc(sizeof *user * MAX_LOGIN);
	char *senha,
		 *confirmaSenha;

    CLEAN_BUFF;

    printf("Usuario: ");
    gets(user);
    printf("Senha: ");
    senha = CriaSenha();

    fpIN = fopen("usuarios.txt", "a+");
    if(Usuario(fpIN, user, senha)){
        printf("\nLogin Concluido.\n\n");
    }else{
        printf("\nUsuario nao registrado\n");
    }

    fclose(fpIN);
    free(senha);
}

int cadastro_usuario(){
    FILE* fpIN;

	int option;

	char *user  = (char*)malloc(sizeof *user * MAX_LOGIN);
	char *senha,
		 *confirmaSenha;

    CLEAN_BUFF;
        
    printf("Usuario: ");
    gets(user);

    do{
        printf("Senha: ");
        senha = CriaSenha();
        printf("\nConfirmacao de senha: ");
        confirmaSenha = CriaSenha();
        printf("\n");

        if( !strcmp(senha, confirmaSenha) )
            break;
        else
            printf("As senhas nao sao iguais. Tente novamente.\n");
    }while(1);

    fpIN = fopen("usuarios.txt", "a+");
    fprintf(fpIN, "%s %s\n", user, senha);
    fclose(fpIN);

    free(senha);
    free(confirmaSenha);
}

int cadastro_produto(){
    setlocale(LC_ALL,"portuguese");

    int i,opcao,opcao2;

    FILE*arq;

    arq=fopen("Cadastros.txt","a");

    printf("Bem vindo \n");

    do{
        for(i=0;i<2;i++){
            printf("Nome do produto que deseja cadastrar: \n");
            fflush(stdin);
            gets(cadastro.nome[i]);

            fprintf(arq,"%s \n",cadastro.nome[i]);

            printf("Codigo do produto que deseja cadastrar: \n");
            scanf("%d",&cadastro.cod[i]);

            fprintf(arq,"%d \n",cadastro.cod[i]);

            printf("Valor do produto que deseja cadastrar: \n");
            scanf("%f",&cadastro.valor[i]);

            fprintf(arq,"%.2f \n",cadastro.valor[i]);

            printf("Quantidade do produto que está cadastrando: \n");
            scanf("%d",&cadastro.quant[i]);

            fprintf(arq,"%d \n\n",cadastro.quant[i]);
        }

        printf("Digite 1 para recomeçar o cadastro, ou outro número para ver os produtos cadastrados: ");
        scanf("%d",&opcao);
    }while(opcao==1);

    fclose(arq);

    for(i=0;i<2;i++){
        printf("nome: %s \n",cadastro.nome[i]);
        printf("codigo: %d \n",cadastro.cod[i]);
        printf("valor: %.2f \n",cadastro.valor[i]);
        printf("quantidade: %d \n\n",cadastro.quant[i]);
    }
}

int consulta_produto(){
    char nome[20];
    int cod;
    int quant;
    float valor;

    FILE*arq;

    arq = fopen("Cadastros.txt", "r");
    if(arq == NULL){
        printf("Erro ao encontrar arquivo.");
    }else{
        while(!feof(arq)){
            fgets(nome, 20, arq);
            printf("%s", nome);
        }
    }
    fclose(arq);
}

int inserir_estoque(){
    int cod, i, quant, trocar;
    char matriz[9][20];

    FILE*arq;

    arq = fopen("Cadastros.txt", "r");

    for(i = 0; i < 9; i++){
        fscanf(arq, "%s\n", matriz[i]);
    }

    fclose(arq);

    printf("Insira o codigo do produto que deseja adicionar estoque: ");
    scanf("%i", &cod);

    printf("Insira a quantidade que deseja adicionar: ");
    scanf("%i", &quant);

    if(cod == 1){
        trocar = atoi(matriz[3]);
        trocar = trocar + quant;
    }else if(cod == 2){
        trocar = atoi(matriz[7]);
        trocar = trocar + quant;
    }

    arq = fopen("Cadastros.txt", "w+");

    if(cod == 1){
        fprintf(arq, "%s\n", matriz[0]);
        fprintf(arq, "%s\n", matriz[1]);
        fprintf(arq, "%s\n", matriz[2]);
        fprintf(arq, "%i\n\n", trocar);
        fprintf(arq, "%s\n", matriz[4]);
        fprintf(arq, "%s\n", matriz[5]);
        fprintf(arq, "%s\n", matriz[6]);
        fprintf(arq, "%s\n\n", matriz[7]);
    }

    if(cod == 2){
        fprintf(arq, "%s\n", matriz[0]);
        fprintf(arq, "%s\n", matriz[1]);
        fprintf(arq, "%s\n", matriz[2]);
        fprintf(arq, "%s\n\n", matriz[3]);
        fprintf(arq, "%s\n", matriz[4]);
        fprintf(arq, "%s\n", matriz[5]);
        fprintf(arq, "%s\n", matriz[6]);
        fprintf(arq, "%i\n\n", trocar);
    }

    fclose(arq);
}

int venda_produto(){
    int cod, i, quant, trocar;
    char matriz[9][20];
    float valor, total;
    
    FILE*arq;

    arq = fopen("Cadastros.txt", "r");

    for(i = 0; i < 9; i++){
        fscanf(arq, "%s\n", matriz[i]);
    }

    fclose(arq);

    while(cod != 0){
        printf("Insira o codigo do item que sera vendido: ");
        scanf("%i", &cod);

        printf("Digite a quantidade que sera vendida: ");
        scanf("%i", &quant);

        if(cod == 1){
            trocar = atoi(matriz[3]);
            trocar = trocar - quant;

            valor = atof(matriz[2]);
            total = valor * quant;
            break;
        }else if(cod == 2){
            trocar = atoi(matriz[7]);
            trocar = trocar - quant;

            valor = atof(matriz[6]);
            total = valor * quant;
            break;
        }
    }

    printf("O valor total de sua compra foi: %.2f", total);

    arq = fopen("Cadastros.txt", "w+");

    if(cod == 1){
        fprintf(arq, "%s\n", matriz[0]);
        fprintf(arq, "%s\n", matriz[1]);
        fprintf(arq, "%s\n", matriz[2]);
        fprintf(arq, "%i\n\n", trocar);
        fprintf(arq, "%s\n", matriz[4]);
        fprintf(arq, "%s\n", matriz[5]);
        fprintf(arq, "%s\n", matriz[6]);
        fprintf(arq, "%s\n\n", matriz[7]);
    }

    if(cod == 2){
        fprintf(arq, "%s\n", matriz[0]);
        fprintf(arq, "%s\n", matriz[1]);
        fprintf(arq, "%s\n", matriz[2]);
        fprintf(arq, "%s\n\n", matriz[3]);
        fprintf(arq, "%s\n", matriz[4]);
        fprintf(arq, "%s\n", matriz[5]);
        fprintf(arq, "%s\n", matriz[6]);
        fprintf(arq, "%i\n\n", trocar);
    }

    fclose(arq);
}

int produtos(){
    int op;

    while(op != 0){
        printf("\n\n----- MENU -----\n\n");
        printf("1 - Cadastro de Produto\n");
        printf("2 - Consulta de Produto\n");
        printf("3 - Adicionar Produto no Estoque\n");
        printf("4 - Fazer Venda de Produto\n");
        printf("0 - Sair\n");

        printf("\nDigite o item desejado: ");
        scanf("%i", &op);
        printf("\n");

        switch(op){
            case 1:
                cadastro_produto();
            break;

            case 2:
                consulta_produto();
            break;

            case 3:
                inserir_estoque();
            break;

            case 4:
                venda_produto();
            break;
        }
    }
}

int main(){
	int option;

    while(option != 0){

        printf("\n\n----- MENU -----\n\n");
        printf("1 - Login\n");
        printf("2 - Cadastro\n");
        printf("0 - Sair\n");

        printf("Digite o item desejado: ");
        scanf("%i", &option);
        printf("\n");

        switch(option){
            case 1:
                login();
                produtos();
            break;

            case 2:
                cadastro_usuario();
            break;
        }
    }
}