#include <iostream>
#include <stack>

#define LIVRE   0
#define BISHOP  8*8
#define ALCANCE 1

using namespace std;

void printa_mat(int n, int mat[][8]){
    cout<<endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cout<<mat[i][j]<<'\t';
        cout<<endl;
    }
    cout<<endl;
}

void insere_bispo(int n, int mat[][8],int x, int y){
    mat[x][y] += BISHOP;
}
void insere_alcance(int n, int mat[][8],int x, int y){
    int menor,xaux,yaux;

    menor = x>y?y:x;
    xaux = x-menor;
    yaux = y-menor;
    while(xaux < n && yaux < n)
        mat[xaux++][yaux++] += ALCANCE;
    menor = (n-x-1)>y?y:(n-x-1);
    xaux = x+menor;
    yaux = y-menor;
    while(xaux >= 0 && yaux < n)
        mat[xaux--][yaux++] += ALCANCE;
}

void remove_bispo(int n, int mat[][8],int x, int y){
    mat[x][y] -= BISHOP;
}

void remove_alcance(int n, int mat[][8],int x, int y){
    int menor,xaux,yaux;

    menor = x>y?y:x;
    xaux = x-menor;
    yaux = y-menor;
    while(xaux < n && yaux < n)
        mat[xaux++][yaux++] -= ALCANCE;
    menor = (n-x-1)>y?y:(n-x-1);
    xaux = x+menor;
    yaux = y-menor;
    while(xaux >= 0 && yaux < n)
        mat[xaux--][yaux++] -= ALCANCE;
}

long long bishops(int n, int k, int mat[][8],int xini, int yini){
    long long cont = 0;
    int x,y,espacos=0,test=1;
    stack<int> pilha;

    if(k == 0)
        return 1;
    if(k > (n-1)*2 && n > 1)
        return 0;
    for(int i = xini; i < n; i++)
        for(int j = i==xini?yini:0; j < n; j++)
            if(mat[i][j] == LIVRE)
                espacos++;
    if(espacos<k)
        return 0;
    if(k == 1)
        return (long long)espacos;
    if(k == 2){
        for(int i = xini; i < n && test; i++)
            for(int j = i==xini?yini:0; j < n && test; j++)
                if(mat[i][j] == LIVRE){
                    if(espacos<k){
                        test=0;
                        break;
                    }
                    //printa_mat(n,mat);
                    insere_bispo(n,mat,i,j);
                    insere_alcance(n,mat,i,j);
                    //printa_mat(n,mat);
                    pilha.push(i);
                    pilha.push(j);
                    for(int k = i; k < n; k++)
                        for(int l = k==i?j:0; l < n; l++)
                            if(mat[k][l] == LIVRE)
                                cont++;
                    remove_alcance(n,mat,i,j);
                    espacos--;
                    //printa_mat(n,mat);
                }
    }
    else if(k > 2){
        for(int i = xini; i < n && test; i++)
            for(int j = i==xini?yini:0; j < n && test; j++)
                if(mat[i][j] == LIVRE){
                    if(espacos<k){
                        test=0;
                        break;
                    }
                    //printa_mat(n,mat);
                    insere_bispo(n,mat,i,j);
                    insere_alcance(n,mat,i,j);
                    //printa_mat(n,mat);
                    pilha.push(i);
                    pilha.push(j);
                    cont += bishops(n,k-1,mat,i,j);
                    remove_alcance(n,mat,i,j);
                    espacos--;
                    //printa_mat(n,mat);
                }
    }
    /*else if(k == 1)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(mat[i][j] == LIVRE)
                    cont++;*/
    while(!pilha.empty()){
        y = pilha.top();
        pilha.pop();
        x = pilha.top();
        pilha.pop();
        remove_bispo(n,mat,x,y);
    }

    return cont;
}

int main(){
    //~ int n,k;
    //int mat[8][8];

    //~ while(cin>>n>>k){
        //~ if(n==0 && k==0)
            //~ break;
        //int mat[n][n];
        int mat[8][8] = {0};
        //memset(mat,0,sizeof(mat));  //ZERO EM TUTÔ
        //~ cout<<bishops(n,k,mat,0,0)<<endl;
        bishops(8,8,mat,0,0);
    //~ }

    return 0;
}
