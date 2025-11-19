/*
Simulador de Fila de Triagem Hospitalar
*/

#include <iostream>
#include <queue>

using namespace std; 

//Struct do paciente para guardar as informações quando há a chegada de um
struct Paciente{
    string senha;
    char prioridade;
    int hora;
    int minuto;
}; 


//Função para atender o paciente e nao precisar repetir todos comandos em varios ifs
void atender(queue<Paciente>& fila,
    int horaAtendimento,
    int minutoAtendimento,
    int& esperaMaxima,
    int& totalAtendidos,
    int& atendidosDaFila){
        if(fila.empty()) return;
        Paciente p = fila.front();
        fila.pop();
        int chegada = p.hora*60 + p.minuto;
        int atendimento = horaAtendimento*60 + minutoAtendimento;
        int espera = atendimento - chegada;

        if(espera > esperaMaxima){
            esperaMaxima = espera;
            }

        totalAtendidos++;
        atendidosDaFila++;

}

int main(){
    //Definição das filas de prioridade, seus tamanhos e total de atendidos em cada uma
    queue <Paciente> filaVermelha; int atendidosVermelha = 0;
    queue <Paciente> filaAmarela; int atendidosAmarela = 0;
    queue <Paciente> filaVerde; int atendidosVerde = 0;
    queue <Paciente> filaBranca; int atendidosBranca = 0;

    //Inicialização em 0 nas variávies de contagem
    int picoLotacao = 0, totalAtendidos = 0, esperaMaxima = 0, totalAtual = 0; 
    //Definição das variáveis de horário
    int horaAtendimento, minutoAtendimento;
    //Variável do menu C-A-D-Q
    char comando;
    bool paradaLoop = true;
    //Loop que exibe o menu com as 4 escolhas pro paciente
    while(paradaLoop){
        cout << "==Atendimento Hospitalar==\n"
                "C - Novo paciente\n"
                "A - Atendimento\n"
                "D - Exibir informações das filas\n"
                "Q - Encerrar programa" << endl;
        cin >> comando;

        switch(comando){
            case 'C':{
                Paciente p;
                cout << "Senha do paciente: " << endl;
                cin >> p.senha;

                //Loop que lê a prioridade de atendimento até que um comando(V, A, D ou B) seja válido.
                do{cout << "Prioridade do atendimento: \n"
                           "V - Vermelho\n"
                           "A - Amarelo\n"
                           "D - Verde\n"
                           "B - Branco" << endl;
                cin >> p.prioridade;
                } while(p.prioridade != 'V' && p.prioridade != 'A' && p.prioridade != 'D' && p.prioridade != 'B');

                cout << "Hora de chegada: " << endl;
                cin >> p.hora;
                cout << "Minuto de chegada: " << endl;
                cin >> p.minuto;

                //Push nas filas correspondentes e incremento do tamanho de acordo com a priorudade
                if(p.prioridade == 'V'){
                    filaVermelha.push(p);
                } else if(p.prioridade == 'A'){
                    filaAmarela.push(p);
                } else if(p.prioridade == 'D'){
                    filaVerde.push(p);
                } else if(p.prioridade == 'B'){
                    filaBranca.push(p);
                }

                //Atualização do contador de pico de lotação
                totalAtual = filaVermelha.size() + filaAmarela.size() + filaVerde.size() + filaBranca.size();
                    if(totalAtual > picoLotacao){
                    picoLotacao = totalAtual;
                }
                break;
            }

            case 'A':{
                Paciente pacienteAtual;
                //Leitura do horário do atendimento
                cout << "Hora do atendimento: " << endl;
                cin >> horaAtendimento;
                cout << "Minuto do atendimento: " << endl;
                cin >> minutoAtendimento;

                //Aqui fica o uso da função criada lá em cima, o "atender", com os parametros certos, da push nas filas, atualiza variaveis de controle etc
                if(!filaVermelha.empty()){
                    atender(filaVermelha, horaAtendimento, minutoAtendimento, esperaMaxima, totalAtendidos, atendidosVermelha);
                    } else if(!filaAmarela.empty()){
                        atender(filaAmarela, horaAtendimento, minutoAtendimento, esperaMaxima, totalAtendidos, atendidosAmarela);
                    } else if(!filaVerde.empty()){
                    atender(filaVerde, horaAtendimento, minutoAtendimento, esperaMaxima, totalAtendidos, atendidosVerde);
                    } else if(!filaBranca.empty()){
                    atender(filaBranca, horaAtendimento, minutoAtendimento, esperaMaxima, totalAtendidos, atendidosBranca);
                    }
                else{
                    cout << horaAtendimento << " " << minutoAtendimento << " Sem pacientes aguardando atendimento" << endl;
                }
                break;
            }

            //Caso entrada seja 'D', mostra a sitaução atual das ilas e os atendidos
            case 'D':{
                cout << "V:" << filaVermelha.size() 
                     << " A:" << filaAmarela.size()
                     << " D:" << filaVerde.size()
                     << " B:" << filaBranca.size() << " | " << "Atendidos:" << totalAtendidos << endl;
                break;
            }
        

            //Caso entrada seja 'Q', mostra o relatório final
            case 'Q':
                cout << "---RELATÓRIO FINAL---\n"
                        "Total atendidos: " << totalAtendidos << "\n"
                        << "Por prioridade: V=" << atendidosVermelha 
                        << " A=" << atendidosAmarela 
                        << " D=" << atendidosVerde
                        << " B=" << atendidosBranca << "\n"
                        << "Pico de lotação: " << picoLotacao << "\n"
                        << "Espera máxima: " << esperaMaxima << " min" << endl;
            paradaLoop = false;
            break;

            //Default caso a entrada seja diferente das opções fornecidas
            default:
                cout << "Comando inválido" << endl;
                break;
        }
    }
    return 0;
}
