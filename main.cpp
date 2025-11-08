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

int main(){
    //Definição das filas de prioridade, seus tamanhos e total de atendidos em cada uma
    queue <Paciente> filaVermelha; int tamVermelha = 0, atendidosVermelha = 0;
    queue <Paciente> filaAmarela; int tamAmarela = 0, atendidosAmarela = 0;
    queue <Paciente> filaVerde; int tamVerde = 0, atendidosVerde = 0;
    queue <Paciente> filaBranca; int tamBranca = 0, atendidosBranca = 0;

    //Inicialização em 0 nas variávies de contagem
    int picoLotacao = 0, totalAtendidos = 0, esperaMaxima = 0, totalAtual = 0; 
    //Definição das variáveis de horário
    int horaAtendimento, totalMinutosChegada, minutoAtendimento, totalMinutoAtendimento, tempoEspera;
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
                    tamVermelha++;
                } else if(p.prioridade == 'A'){
                    filaAmarela.push(p);
                    tamAmarela++;
                } else if(p.prioridade == 'D'){
                    filaVerde.push(p);
                    tamVerde++;
                } else if(p.prioridade == 'B'){
                    filaBranca.push(p);
                    tamBranca++;
                }

                //Atualização do contador de pico de lotação
                totalAtual = tamVermelha + tamAmarela + tamVerde + tamBranca;
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

                if(!filaVermelha.empty()){
                    pacienteAtual = filaVermelha.front();
                    totalMinutosChegada = pacienteAtual.hora*60 + pacienteAtual.minuto;
                    totalMinutoAtendimento = horaAtendimento*60 + minutoAtendimento;
                    tempoEspera = totalMinutoAtendimento - totalMinutosChegada;
                    if(tempoEspera > esperaMaxima){
                        esperaMaxima = tempoEspera;
                    }
                    filaVermelha.pop();
                    tamVermelha--;
                    atendidosVermelha++;
                    totalAtendidos++;
                } else if(!filaAmarela.empty()){
                    pacienteAtual = filaAmarela.front();
                    totalMinutosChegada = pacienteAtual.hora*60 + pacienteAtual.minuto;
                    totalMinutoAtendimento = horaAtendimento*60 + minutoAtendimento;
                    tempoEspera = totalMinutoAtendimento - totalMinutosChegada;
                    if(tempoEspera > esperaMaxima){
                        esperaMaxima = tempoEspera;
                    }
                    filaAmarela.pop();
                    tamAmarela--;
                    totalAtendidos++;
                    atendidosAmarela++;
                } else if(!filaVerde.empty()){
                    pacienteAtual = filaVerde.front();
                    totalMinutosChegada = pacienteAtual.hora*60 + pacienteAtual.minuto;
                    totalMinutoAtendimento = horaAtendimento*60 + minutoAtendimento;
                    tempoEspera = totalMinutoAtendimento - totalMinutosChegada;
                    if(tempoEspera > esperaMaxima){
                        esperaMaxima = tempoEspera;
                    }
                    filaVerde.pop();
                    tamVerde--;
                    atendidosVerde++;
                    totalAtendidos++;
                } else if(!filaBranca.empty()){
                    pacienteAtual = filaBranca.front();
                    totalMinutosChegada = pacienteAtual.hora*60 + pacienteAtual.minuto;
                    totalMinutoAtendimento = horaAtendimento*60 + minutoAtendimento;
                    tempoEspera = totalMinutoAtendimento - totalMinutosChegada;
                    if(tempoEspera > esperaMaxima){
                        esperaMaxima = tempoEspera;
                    }
                    filaBranca.pop();
                    tamBranca--;
                    totalAtendidos++;
                    atendidosBranca++;
                    }
                else{
                    cout << horaAtendimento << " " << minutoAtendimento << " Sem pacientes aguardando atendimento" << endl;
                }
                break;
            }

            case 'D':{
                cout << "V:" << filaVermelha.size() 
                     << " A:" << filaAmarela.size()
                     << " D:" << filaVerde.size()
                     << " B:" << filaBranca.size() << " | " << "Atendidos:" << totalAtendidos << endl;
                break;
            }
        
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
        }
    }
    return 0;
}
