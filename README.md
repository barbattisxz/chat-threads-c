# 💬 Chat Cliente-Servidor com Threads em C

## 📘 Descrição
Este projeto implementa um **chat em rede** utilizando **sockets TCP** e **threads** na linguagem C.  
Ele permite que **vários clientes se conectem simultaneamente** a um servidor e troquem mensagens entre si em tempo real.

O foco é demonstrar:
- Comunicação entre processos via rede (cliente-servidor);
- Criação e controle de **threads** para gerenciar múltiplas conexões;
- Uso de **sockets TCP/IP** e sincronização em sistemas concorrentes.

---

## ⚙️ Funcionalidades
✅ Servidor capaz de aceitar **vários clientes ao mesmo tempo**.  
✅ Cada cliente pode **enviar e receber mensagens simultaneamente**.  
✅ Uso de **threads** para o envio e recebimento concorrente.  
✅ Comunicação baseada em **sockets TCP/IP**.  
✅ Exemplo didático ideal para disciplinas de **Redes de Computadores** ou **Sistemas Operacionais**.

---

## 🗂️ Estrutura do Projeto
chat_servidor/
├── servidor_chat.c # Código do servidor (aceita múltiplos clientes)
├── cliente_chat.c # Código do cliente (envia e recebe mensagens)
└── README.md # Documento de explicação do projeto

yaml
Copiar código

---

## 🧠 Tecnologias Utilizadas
- Linguagem **C**
- **Threads POSIX** (`pthread`)
- **Sockets TCP/IP** (`sys/socket.h`, `arpa/inet.h`)
- **Comunicação cliente-servidor**

---

## 🖥️ Como Compilar
Abra o terminal na pasta do projeto e compile os arquivos com:

```bash
gcc servidor_chat.c -o servidor -lpthread
gcc cliente_chat.c -o cliente -lpthread
🚀 Como Executar
1️⃣ Inicie o servidor:
bash
Copiar código
./servidor
O servidor ficará escutando conexões na porta 20032 (padrão do código).

2️⃣ Em outro terminal (ou computador da rede), execute o cliente:
bash
Copiar código
./cliente 127.0.0.1
Substitua 127.0.0.1 pelo IP do servidor se estiver em outra máquina.

Agora, você pode abrir vários clientes simultaneamente — todos conseguirão conversar entre si.

💬 Exemplo de Execução
🖥️ Servidor:
yaml
Copiar código
Servidor aguardando conexões na porta 20032...
Novo cliente conectado: 127.0.0.1
Novo cliente conectado: 127.0.0.2
Mensagem recebida: Olá, pessoal!
💻 Cliente:
markdown
Copiar código
Conectado ao servidor 127.0.0.1
Mensagem: Olá, tudo bem?
[Outro usuário]: Tudo sim!
⚠️ Observações Importantes
Este projeto é educacional, voltado para aprendizado de redes e threads em C.

Não foi desenvolvido com foco em segurança ou autenticação.

Recomendado para trabalhos práticos de redes de computadores.

👨‍💻 Autor
Bernardo Machado Barbatti
💡 Projeto desenvolvido para estudos acadêmicos de comunicação em rede e programação concorrente em C.
