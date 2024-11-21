# Projeto: Monitoramento IoT com ESP32, MQTT e Dashboard Interativo
## Descrição Geral
Este projeto integra um sistema de monitoramento IoT utilizando o ESP32 para leitura de temperatura e umidade, com envio de dados via MQTT para um broker. Os dados são exibidos em tempo real em um painel interativo desenvolvido com a biblioteca Dash. LEDs simulam ações de controle (como ventilação ou aquecimento) com base nas leituras.

## Arquitetura do Sistema
### Hardware:

- ESP32 como microcontrolador.
- Sensor DHT22 para leitura de temperatura e umidade.
- LEDs para simular ventilador e aquecedor.
### Software:

###Arduino:
  ###Conexão Wi-Fi para envio dos dados.
- MQTT (via PubSubClient) para publicação das informações.
- Dashboard Python:
    - Dash para criar o painel de controle.
    - Plotly para gráficos interativos.
    - paho-mqtt para receber dados do broker MQTT.
## Fluxo de Dados
### 1. ESP32:
  -Lê os dados do sensor DHT22.
  - Publica os valores de temperatura, umidade e status do sistema nos tópicos MQTT:
        /monitor/temperature
        /monitor/humidity
        /monitor/status
  - LEDs indicam as ações:
      -  Ventilador ligado: Temperatura > 25°C ou umidade > 60%.
      - Aquecedor ligado: Temperatura < 22°C.
### 2. Dashboard Python:
  - Conecta-se ao broker MQTT e escuta os tópicos configurados.
  - Exibe gráficos de temperatura e umidade ao longo do tempo.
  - Atualiza o status do sistema em tempo real.

##Funcionalidades
###  ESP32:
  -Monitoramento local via display OLED.
  - Controle automático dos LEDs com base nas condições ambientais.
  - Publicação de dados via MQTT.
### Dashboard:
  - Gráfico de temperatura.
  - Gráfico de umidade.
  - Exibição de status atual (ex.: "Ventilador Ligado").
## Como Usar
### 1. ESP32:

  - Configure o código Arduino para conectar à sua rede Wi-Fi e ao broker MQTT.
  - Conecte o DHT22 e os LEDs aos pinos apropriados.
  - Carregue o código no ESP32 utilizando a Arduino IDE.

## 2. Dashboard Python:

  - Instale as dependências necessárias:
      pip install dash plotly paho-mqtt
  - Configure o endereço e a porta do broker MQTT no script Python.
  - Execute o script:
      python app.py
  - Acesse o painel no navegador (geralmente em http://localhost:8050).

## Exemplo de Saída
### ESP32:
  - Publicação MQTT:
      /monitor/temperature: 24.50
      /monitor/humidity: 55.00
      /monitor/status: "Ventilador Ligado"
### Dashboard:
  - Gráficos atualizados a cada 2 segundos.
  - Status do sistema exibido em tempo real.

### Autores

- Gabriel Luni Nakashima
- Melyssa Huang
- Gabriel Lacerda
