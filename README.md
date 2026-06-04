# BioSpine MVP - Comunicação ESP32

## Sobre o Projeto

O BioSpine é um sistema de monitoramento postural em desenvolvimento que tem como objetivo auxiliar na identificação de desvios posturais por meio de sensores embarcados em um colete inteligente.

Esta primeira versão consiste em um MVP (Minimum Viable Product) desenvolvido para validar a camada de comunicação entre um microcontrolador ESP32 e sistemas externos.

Nesta etapa, o foco não está na leitura de sensores reais, mas sim na comprovação de que o ESP32 é capaz de:

* Receber comandos externos;
* Processar informações;
* Retornar respostas estruturadas;
* Simular dados de postura;
* Servir como base para futuras integrações com sensores e aplicativo mobile.

Os dados utilizados atualmente são simulados através de valores aleatórios, permitindo validar toda a arquitetura antes da integração dos componentes eletrônicos definitivos.

---

## Objetivos

O objetivo desta implementação é disponibilizar uma estrutura funcional para que futuras equipes possam integrar:

* Sensores de inclinação;
* Sensores de pressão;
* Sensores de curvatura;
* Comunicação sem fio;
* Aplicativo de monitoramento;
* Sistema de correção postural.

Arquitetura prevista para a solução final:

```text
Sensores
   ↓
ESP32
   ↓
Bluetooth BLE / Wi-Fi
   ↓
Aplicativo Mobile
   ↓
Dashboard e Histórico
```

---

## Tecnologias Utilizadas

* ESP32 Dev Module
* Arduino IDE
* Linguagem C++
* Comunicação Serial UART
* JSON para troca de informações
* Bluetooth BLE (planejado para próximas versões)
* Wi-Fi (planejado para próximas versões)

---

## Funcionalidades Implementadas

### Recebimento de Comandos

O ESP32 recebe comandos enviados através do Monitor Serial.

Comandos disponíveis:

| Comando   | Descrição                          |
| --------- | ---------------------------------- |
| START     | Inicia o monitoramento             |
| STOP      | Interrompe o monitoramento         |
| STATUS    | Retorna dados simulados de postura |
| CALIBRATE | Simula a calibração do sistema     |

---

### Processamento de Dados

O sistema gera valores simulados de inclinação postural para validar a lógica de processamento.

Faixas utilizadas:

| Ângulo    | Classificação |
| --------- | ------------- |
| 0° a 10°  | GOOD          |
| 11° a 20° | WARNING       |
| 21° a 45° | BAD           |

---

### Retorno Estruturado em JSON

Exemplo de resposta:

```json
{
  "angle": 19,
  "status": "WARNING"
}
```

---

## Exemplos de Uso

### STATUS

Entrada:

```text
STATUS
```

Saída:

```json
{
  "angle": 19,
  "status": "WARNING"
}
```

---

### START

Entrada:

```text
START
```

Saída:

```json
{
  "success": true,
  "message": "Monitoring started"
}
```

---

### STOP

Entrada:

```text
STOP
```

Saída:

```json
{
  "success": true,
  "message": "Monitoring stopped"
}
```

---

### CALIBRATE

Entrada:

```text
CALIBRATE
```

Saída:

```json
{
  "success": true,
  "message": "Calibration completed"
}
```

---

## Como Executar

### 1. Instalar a Arduino IDE

Download:

https://www.arduino.cc/en/software

---

### 2. Instalar o suporte ao ESP32

Na Arduino IDE:

```text
Boards Manager
↓
Pesquisar: ESP32
↓
Instalar: ESP32 by Espressif Systems
```

---

### 3. Selecionar a Placa

```text
ESP32 Dev Module
```

---

### 4. Selecionar a Porta Serial

Selecionar a porta correspondente ao ESP32 conectado.

Exemplo:

```text
COM5
```

---

### 5. Realizar Upload

Compilar e enviar o firmware para o ESP32.

Em algumas placas pode ser necessário:

```text
Segurar o botão BOOT
durante o upload
```

---

### 6. Abrir o Monitor Serial

Configurações recomendadas:

```text
Baud Rate: 115200
Line Ending: New Line
```

---

### 7. Reinicialização do ESP32

Durante os testes foi observado que o ESP32 pode não iniciar automaticamente após o upload ou após a abertura do Monitor Serial.

Caso isso aconteça:

```text
Pressione o botão EN
```

presente na placa.

O botão EN reinicia o microcontrolador e executa novamente o firmware gravado.

Fluxo recomendado:

```text
Upload do código
↓
Abrir Monitor Serial
↓
Pressionar EN
↓
Executar testes
```

Importante:

O botão EN não apaga o firmware. Ele apenas reinicia a execução do programa armazenado na memória do ESP32.

---

## Estrutura Atual do Sistema

```text
ESP32
│
├── Recebe comandos
├── Processa informações
├── Simula dados de postura
└── Retorna respostas JSON
```

---

## Comunicação Sem Fio (Próximas Versões)

Planejado para implementação:

* Bluetooth Low Energy (BLE)
* Wi-Fi

---

## Próximas Etapas

Integração com sensores reais:

* MPU6050
* ISM330
* Flex Sensor
* Force Sensing Resistor (FSR)
* Sensor Piezoelétrico

Desenvolvimento de:

* Aplicativo Mobile
* Dashboard em tempo real
* Histórico de postura
* Sistema de calibração
* Comunicação Bluetooth BLE

---

## Resultados Obtidos

✅ ESP32 configurado e operacional

✅ Comunicação serial funcional

✅ Recebimento de comandos

✅ Processamento de informações

✅ Retorno estruturado em JSON

✅ Simulação de dados posturais

✅ Arquitetura preparada para integração com sensores

✅ Base preparada para comunicação com aplicativo mobile

---

## Autor

João Vitor Andrade

Projeto desenvolvido como etapa inicial do sistema BioSpine para validação da comunicação entre hardware embarcado e software de monitoramento postural.