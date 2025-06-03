
# 🌡️ Sistema IoT de Monitoramento Ambiental e Resposta a Falhas Elétricas

## 📝 Descrição do Problema

Eventos climáticos extremos, como **ondas de calor**, **tempestades**, **secas** e **enchentes**, têm causado frequentes **quedas de energia elétrica**, comprometendo serviços essenciais como **saúde, comunicação e transporte**.

Para mitigar os impactos desses eventos, é necessário desenvolver **soluções tecnológicas** que monitorem o ambiente e ajam de forma **proativa e autônoma** em situações críticas. O objetivo deste projeto é criar um **sistema IoT (Internet das Coisas)** que monitore variáveis ambientais e simule ações de resposta diante de falhas elétricas.

---

## 🎯 Objetivo

Desenvolver um sistema embarcado com sensores e atuadores que:

- Leia e envie dados de **temperatura e umidade** periodicamente via MQTT.
- Classifique o ambiente em três estados (normal, alerta, falha crítica).
- Acione **LEDs indicadores** e um **servo motor** de forma automática com base nos dados.
- Permita o **controle remoto via MQTT** para simular o **modo de reparo do sistema**.
- Integre-se com um **dashboard em Node-RED** para visualização em tempo real.

---

## 🛠️ Componentes Utilizados

- **ESP32/Arduino (emulado ou físico)**
- **Sensor DHT11 ou DHT22** (Temperatura e Umidade)
- **3 LEDs** (Verde, Amarelo e Vermelho)
- **Servo Motor** (representa uma válvula de emergência)
- **Broker MQTT** (como `mqtt-dashboard.com` ou `test.mosquitto.org`)
- **Node-RED** (para visualização dos dados)

---

## ⚙️ Funcionamento do Sistema

### 📡 Monitoramento Ambiental

- A cada **2 segundos**, o sensor **DHT22** mede a **temperatura** e a **umidade**.
- Os valores são exibidos no **Serial Monitor** e enviados via **MQTT** no formato JSON:
  ```json
  {"temp": 32, "umid": 48}
  ```

### 🔄 Classificação do Estado do Sistema

| Estado           | Condição                                     | LED Ativo   | Ação do Servo Motor |
|------------------|-----------------------------------------------|-------------|----------------------|
| Normal           | Temperatura e umidade em faixa ideal         | Verde       | Válvula fechada      |
| Alerta           | Temperatura ou umidade fora do ideal         | Amarelo     | Válvula fechada      |
| Falha Crítica    | Temperatura muito alta ou umidade muito baixa| Vermelho    | Válvula aberta       |

### 🔧 Modo de Reparo

- Ativado remotamente via **comando MQTT** (`1`).
- Neste modo:
  - Os **3 LEDs piscam simultaneamente** a cada segundo.
  - O **servo motor alterna** entre aberto e fechado.
- Modo permanece ativo até o recebimento do comando `0`.

---

## 🧠 Lógica de Decisão (exemplo de faixas)

```cpp
if (temp >= 70 || umi <= 10) {
  // Falha crítica
} else if (temp >= 60 || umi <= 30) {
  // Alerta
} else {
  // Normal
}
```

---

## 🔗 Integração com Node-RED

- Dashboard exibe **gráficos em tempo real** das variáveis monitoradas.
- Pode-se utilizar **nós MQTT**, **gráficos lineares**, e **textos dinâmicos**.
- O controle do **modo de reparo** pode ser feito por um botão virtual.

---

## 💻 Código-Fonte (Resumo)

- Uso das bibliotecas:
  - `DHT.h` para leitura de temperatura e umidade
  - `ArduinoJson.h` para criação do JSON
  - `Servo.h` para controle da válvula
- Comunicação via `Serial` (simulação do MQTT pode ser feita com ponte no Node-RED).

---

## ✅ Possíveis Melhorias

- Substituir `Serial` por uma **biblioteca MQTT real** (como `PubSubClient`) para uso direto com Wi-Fi.
- Adicionar **log de eventos**.
- Armazenar dados em um **banco de dados remoto**.
- Enviar **notificações** em caso de falha.

---

## 📸 Demonstração

> *(Adicione aqui imagens ou GIFs da simulação no Wokwi e do dashboard no Node-RED, se desejar.)*
