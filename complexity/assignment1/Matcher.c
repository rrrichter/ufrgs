#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *ComputaPrefixo(char PREFIXO[],int TAMANHO)
{
    int m = TAMANHO;
    int *FuncaoPrefixo = (int *)calloc(m,sizeof(int));
    int k,q;

    k = 0;
    FuncaoPrefixo[0] = 0;
    for(q=1; q<TAMANHO; q++)
    {
        while(k>0 && ((PREFIXO[k])!= (PREFIXO[q])))
        {
            k = FuncaoPrefixo[k-1];
        }
        if(PREFIXO[k]==PREFIXO[q])
            k++;
        FuncaoPrefixo[q]=k;
    }
    return FuncaoPrefixo;
}

int KMP_Matcher(char TEXTO[],char PADRAO[])
{
    int n = strlen(TEXTO);
    int m = strlen(PADRAO);
    int *FuncaoPrefixo = ComputaPrefixo(PADRAO,m);
    int num_caracteres,IndiceTexto,ACHOU = 0;

    num_caracteres = 0;
    for(IndiceTexto=0; IndiceTexto<n; IndiceTexto++)
    {
        while(num_caracteres>0 &&(PADRAO[num_caracteres]!=TEXTO[IndiceTexto]))
            num_caracteres = FuncaoPrefixo[num_caracteres-1];
        if(PADRAO[num_caracteres]==TEXTO[IndiceTexto])
            num_caracteres++;
        if(num_caracteres == m)
        {
            ACHOU = 1;
            num_caracteres = FuncaoPrefixo[num_caracteres-1];
        }
    }
    free(FuncaoPrefixo);
    return ACHOU;
}

void EncontraChave(char TEXTO1[],char TEXTO2[],char *Chave,int TAMANHO)
{
    int TAMANHO_STRING = TAMANHO;
    char SUB_STRING[2000];
    int TAMANHO_SUBSTRING = 2;
    int TAM_PADRAO_ATUAL = 0;
    int i,j,k;

    while(TAMANHO_SUBSTRING<=TAMANHO_STRING)
    {
        i=0;
        while(i+TAMANHO_SUBSTRING<=TAMANHO_STRING)
        {
            for(k=0,j=1; j<=TAMANHO_SUBSTRING; i++,j++,k++)
            {
                SUB_STRING[k] = TEXTO2[i];
            }
            SUB_STRING[k] = '\0';
            if((TAMANHO_SUBSTRING>TAM_PADRAO_ATUAL)&&(KMP_Matcher(TEXTO1,SUB_STRING)))
            {
                TAM_PADRAO_ATUAL = TAMANHO_SUBSTRING;
                strcpy(Chave,SUB_STRING);
            }
            i = (i-TAMANHO_SUBSTRING)+1;
        }
        TAMANHO_SUBSTRING++;
    }
}

int main()
{
    int Tamanho = 743;
    char Texto[] = "12345678901065703304011031338370763392959061742177117741574752405286675751751314504012625336320365104661051291909178480948331328953939507131293079240283777803550434266953656933331862862836053872629918246535772390084354593076702934450791518879868380519997944757051401202663606740768021543612770901240982825779317596912107867285544985437368652710797055348487148149587590243274151793944598475566943017826205603956290299910129298589726700292721565513320871031576930809285943446191042007026945145706963385419521277601571208503379491200480304910489078359571596307622501134540377100878475810202910188059443398551447401411271192011985935673099472044705074971205559203895085818347347252899195454541511061949049056468259567711373961417054550528811252031";
    char Padrao[] = "10657033040110313383707633929590617421771177415747524052866757517513145040126253363203651046610512919091784809483313289539395071312930792402837778035504342669536569333318628628360538726299182465357723900843545930767029344507915188798683805199979447570514012026636067407680215436127709012409828257793175969121078672855449854373686527107970553484871481495875902432741517939445984755669430178262056039562902999101292985897267002927215655133208710315769308092859434461910420070269451457069633854195212776015712085033794912004803049104890783595715963076225011345403771008784758102029101880594433985514474014112711920119859356730994720447050749712055592038950858183473472528991954545415110619490490564682595677113739614170545505288112520310000071232";
    char *Chave = (char *)calloc(2000,sizeof(char));
    EncontraChave(Texto,Padrao,Chave,Tamanho);

    printf("%s\n",Chave);
    free(Chave);
    return 0;
}

