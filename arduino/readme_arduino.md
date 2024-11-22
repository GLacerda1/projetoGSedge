# **Projeto: Monitoramento IoT com ESP32 e MQTT**

# *Descrição*

Este projeto utiliza um ESP32 integrado com um sensor DHT22 para monitorar temperatura e umidade em tempo real. As informações são enviadas via MQTT para um broker. Além disso, LEDs controlam dispositivos simulados (ventilador e aquecedor) com base nas leituras.

# **Arquitetura**
## *Hardware:*

- ESP32 como microcontrolador.
- DHT22 para leitura de temperatura e umidade.
- LEDs para indicar o status do sistema.

## *Software:*

- Conexão Wi-Fi para transmissão de dados.
- MQTT (via biblioteca PubSubClient) para comunicação entre dispositivos.
- Monitoramento de dados por meio de tópicos específicos no broker MQTT.


# **Funcionalidades**
## *Monitoramento de Temperatura e Umidade:*

- Publica as informações em tópicos MQTT:
- /monitor/temperature: Temperatura atual.
- /monitor/humidity: Umidade atual.
- /monitor/status: Status do sistema (ex.: "Ventilador Ligado").

## *Automação com LEDs:*

- Ventilador (LED): Ativado se a temperatura for maior que 25°C ou a umidade ultrapassar 60%.
- Aquecedor (LED): Ativado se a temperatura for inferior a 22°C.
- Desligado: Sistema em repouso caso não haja necessidade de ativação.

# **Como Usar**
## *1.Configuração do Código:*

Edite as seguintes linhas no código Arduino:

    const char* ssid = "Wokwi-GUEST";      // Substitua pelo nome da sua rede Wi-Fi.
    const char* password = "";             // Substitua pela senha da sua rede Wi-Fi.
    const char* mqtt_server = "BROKER_IP"; // Substitua pelo IP público do seu broker MQTT.
    const int mqtt_port = 1883;            // Porta padrão do MQTT (1883).

## **2.Componentes e Conexões:**

- Conecte o DHT22 ao pino 14 do ESP32.
- Conecte os LEDs ao pino 13 (Ventilador) e pino 15 (Aquecedor).

### *Configuração do Broker MQTT:*

- Configure um broker MQTT local (ex.: Mosquitto) ou utilize um público.
- Certifique-se de que a máquina virtual ou o dispositivo que executa o broker está acessível no endereço especificado.

### *Carregamento do Código:*

- Use a Arduino IDE para compilar e carregar o código no ESP32.
- Certifique-se de instalar as bibliotecas necessárias:
  -PubSubClient
  -Adafruit SSD1306
  -DHT

### *Testando o Sistema:*

- Após carregar o código, o ESP32 tentará conectar à rede Wi-Fi.
- O display exibirá a temperatura, umidade e o status da conexão.
- Verifique os tópicos MQTT configurados para visualizar os dados enviados.

# **Fluxo de Controle**
1. O ESP32 conecta ao Wi-Fi e ao broker MQTT.
2. O sensor DHT22 lê temperatura e umidade.
3. Dados são exibidos no display OLED e enviados para o broker MQTT.
4. LEDs simulam ações de controle baseadas em condições:
  -Aquecer se a temperatura for baixa.
  -Ventilar se a temperatura for alta ou houver excesso de umidade.

# **Diagrama de Conexão**
- Inclua um diagrama (em imagem ou ASCII) para ilustrar as conexões do ESP32, sensores e LEDs.

# **Exemplo de Saída**

## *Tópicos MQTT:*
  /monitor/temperature: 24.50
  /monitor/humidity: 55.00
  /monitor/status: "Ventilador Ligado"

