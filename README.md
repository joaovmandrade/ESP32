# BioSpine MVP V3 - Plataforma de Comunicação e Processamento Postural com ESP32

## Sobre o Projeto

O BioSpine é uma solução em desenvolvimento voltada para monitoramento e correção postural através de um colete inteligente equipado com sensores eletrônicos.

Este repositório apresenta a terceira versão do MVP (Minimum Viable Product), cujo objetivo é validar a arquitetura embarcada responsável por:

- Receber informações dos sensores;
- Processar os dados recebidos;
- Classificar a postura do usuário;
- Gerar alertas de postura inadequada;
- Disponibilizar os dados para integração com aplicativos mobile e sistemas externos.

Nesta versão os sensores ainda são simulados por software, permitindo validar toda a lógica de processamento antes da integração física dos componentes eletrônicos.

---

# Objetivo

O principal objetivo deste MVP é fornecer uma base funcional para integração com os sensores que serão instalados no colete inteligente.

A arquitetura foi desenvolvida para que a substituição dos dados simulados pelos sensores reais exija alterações mínimas no código.

---

# Arquitetura do Sistema

## MVP Atual

```text
Sensores Simulados
        ↓
      ESP32
        ↓
Processamento
        ↓
Classificação Postural
        ↓
Geração de Alertas
        ↓
JSON
        ↓
Monitor Serial
```

---

## Arquitetura Final Prevista

```text
MPU6050 / ISM330
Flex Sensors
FSR
        ↓
      ESP32
        ↓
Processamento
        ↓
Bluetooth BLE
        ↓
Aplicativo Mobile
        ↓
Dashboard e Histórico
```

---

# Tecnologias Utilizadas

- ESP32 Dev Module
- Arduino IDE
- Linguagem C++
- Comunicação Serial UART
- Estrutura de dados JSON
- Bluetooth BLE (planejado para versões futuras)

---

# Funcionalidades Implementadas

## Recebimento de Comandos

O ESP32 recebe comandos através do Monitor Serial.

Comandos disponíveis:

| Comando | Descrição |
|----------|----------|
| START | Inicia monitoramento contínuo |
| STOP | Interrompe monitoramento |
| STATUS | Retorna uma leitura instantânea |
| CALIBRATE | Simula calibração do sistema |

---

## Simulação de Sensores

O sistema simula os sensores que serão utilizados futuramente no colete.

### MPU6050 / ISM330

Responsável por:

- Inclinação do tronco
- Movimento corporal
- Orientação espacial

Atualmente:

```cpp
return random(0, 450) / 10.0;
```

---

### Flex Sensor Esquerdo

Responsável por:

- Curvatura lateral da coluna

Atualmente:

```cpp
return random(300, 800);
```

---

### Flex Sensor Direito

Responsável por:

- Curvatura lateral da coluna

Atualmente:

```cpp
return random(300, 800);
```

---

### FSR (Force Sensing Resistor)

Responsável por:

- Distribuição de pressão

Atualmente:

```cpp
return random(0, 100);
```

---

# Classificação Postural

O sistema classifica a postura com base no ângulo calculado.

| Ângulo | Status |
|----------|----------|
| 0° a 10° | GOOD |
| 11° a 20° | WARNING |
| Acima de 20° | BAD |

---

# Sistema de Alertas

Quando uma postura inadequada é detectada:

```json
{
  "status": "BAD",
  "alert": true
}
```

O sistema pode futuramente:

- Acionar vibração;
- Enviar alerta BLE;
- Notificar aplicativo mobile.

---

# Exemplo de Resposta

```json
{
  "angle": 28.2,
  "flex_left": 743,
  "flex_right": 685,
  "pressure": 89,
  "status": "BAD",
  "alert": true
}
```

---

# Comandos Disponíveis

## STATUS

Entrada:

```text
STATUS
```

Saída:

```json
{
  "angle": 13.5,
  "flex_left": 769,
  "flex_right": 660,
  "pressure": 36,
  "status": "WARNING",
  "alert": false
}
```

---

## START

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

Após iniciar, o ESP32 envia leituras continuamente.

---

## STOP

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

## CALIBRATE

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

# Como Executar

## 1. Instalar Arduino IDE

Download:

https://www.arduino.cc/en/software

---

## 2. Instalar suporte ao ESP32

Arduino IDE:

```text
Boards Manager
↓
Pesquisar: ESP32
↓
Instalar:
ESP32 by Espressif Systems
```

---

## 3. Selecionar Placa

```text
ESP32 Dev Module
```

---

## 4. Selecionar Porta

Exemplo:

```text
COM5
```

---

## 5. Fazer Upload

Enviar o firmware para o ESP32.

Em algumas placas pode ser necessário:

```text
Segurar BOOT durante o upload
```

---

## 6. Abrir Monitor Serial

Configurações:

```text
Baud Rate: 115200
Line Ending: New Line
```

---

## 7. Reiniciar ESP32

Caso o Monitor Serial não exiba as mensagens iniciais:

```text
Pressionar botão EN
```

Fluxo recomendado:

```text
Upload
↓
Abrir Monitor Serial
↓
Pressionar EN
↓
Executar testes
```

O botão EN apenas reinicia o microcontrolador.

O firmware não é apagado.

---

# Integração dos Sensores Reais

## MPU6050

Conexão planejada:

```text
VCC → 3.3V
GND → GND
SDA → GPIO21
SCL → GPIO22
```

Substituir:

```cpp
float readMPUAngle() {
    return random(0, 450) / 10.0;
}
```

Por:

```cpp
float readMPUAngle() {
    mpu.update();
    return mpu.getAngleX();
}
```

---

## Flex Sensor Esquerdo

Conexão:

```text
GPIO34
```

Substituir:

```cpp
int readFlexLeft() {
    return random(300, 800);
}
```

Por:

```cpp
int readFlexLeft() {
    return analogRead(34);
}
```

---

## Flex Sensor Direito

Conexão:

```text
GPIO35
```

Substituir:

```cpp
int readFlexRight() {
    return random(300, 800);
}
```

Por:

```cpp
int readFlexRight() {
    return analogRead(35);
}
```

---

## FSR

Conexão:

```text
GPIO32
```

Substituir:

```cpp
int readFSR() {
    return random(0, 100);
}
```

Por:

```cpp
int readFSR() {
    return analogRead(32);
}
```

---

# Resultados Obtidos

✅ ESP32 configurado e operacional

✅ Comunicação Serial funcional

✅ Recebimento de comandos

✅ Processamento de dados

✅ Simulação de sensores

✅ Classificação postural

✅ Geração de alertas

✅ Estrutura JSON

✅ Arquitetura preparada para integração com sensores reais

✅ Base pronta para integração com aplicativo mobile

---

# Próximas Etapas

- Integração do MPU6050
- Integração dos Flex Sensors
- Integração do FSR
- Comunicação Bluetooth BLE
- Aplicativo Mobile
- Dashboard de monitoramento
- Histórico postural
- Sistema de vibração para correção postural

---

# Autor

**João Vitor Andrade**

Projeto desenvolvido como etapa inicial do sistema BioSpine para validação da comunicação entre hardware embarcado, sensores posturais e software de monitoramento.