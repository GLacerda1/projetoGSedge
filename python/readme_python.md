Projeto: Monitoramento IoT com Dash e MQTT
Descrição

Este projeto utiliza a biblioteca Dash para criar um painel de controle interativo, visualizando dados em tempo real de um sistema de monitoramento IoT. Ele se conecta a um broker MQTT para receber informações de temperatura, umidade e status de um dispositivo (simulado ou real, como um ESP32 com sensores DHT22). Os dados recebidos são exibidos em gráficos e na interface de status do sistema.
Arquitetura
Software:

    Dash: Para criar a interface de visualização dos dados.
    Plotly: Para gerar os gráficos interativos de temperatura e umidade.
    paho-mqtt: Para receber os dados via protocolo MQTT.
    Deque (collections): Para armazenar os dados de forma eficiente e gerenciar a exibição no gráfico.

Fluxo de Dados:

    O sistema se conecta a um broker MQTT (como o Mosquitto ou outro broker público).
    O cliente MQTT recebe as mensagens publicadas nos tópicos:
        /monitor/temperature: Temperatura atual.
        /monitor/humidity: Umidade atual.
        /monitor/status: Status do sistema (ex.: "Ventilador Ligado").
    As mensagens são processadas e armazenadas em filas (deque) para exibição no gráfico e no status.
    O painel Dash exibe os dados de temperatura, umidade e o status de forma interativa e em tempo real.

Funcionalidades:

    Gráfico de Temperatura: Exibe as leituras de temperatura ao longo do tempo.
    Gráfico de Umidade: Exibe as leituras de umidade ao longo do tempo.
    Exibição de Status: Exibe o status atual do sistema (ex.: "Ventilador Ligado", "Aquecedor Desligado").

Como Usar

    Instalação de Dependências: Para rodar este código, você precisa instalar as seguintes bibliotecas Python:

pip install dash plotly paho-mqtt

Configuração do Broker MQTT: Edite as variáveis do código para refletir as configurações do seu broker MQTT:

    BROKER: Endereço IP do broker MQTT (ex.: "4.228.61.195").
    PORT: Porta do broker (normalmente 1883).
    TOPIC_TEMP: Tópico para temperatura (/monitor/temperature).
    TOPIC_HUM: Tópico para umidade (/monitor/humidity).
    TOPIC_STATUS: Tópico para o status (/monitor/status).

Executando o Código: Após configurar o broker MQTT, basta rodar o script Python:

    python app.py

    O servidor Dash será iniciado e você poderá acessar o painel de controle via localhost ou no endereço IP da sua máquina.

    Configuração do Sistema de Monitoramento (ESP32): Caso esteja utilizando um dispositivo como o ESP32 com sensores (por exemplo, DHT22), as informações de temperatura, umidade e status devem ser enviadas via MQTT para o broker configurado. O código no ESP32 deve ser configurado para publicar as informações nos tópicos corretos:
        /monitor/temperature: Para temperatura.
        /monitor/humidity: Para umidade.
        /monitor/status: Para o status (ex.: "Ventilador Ligado", "Aquecedor Desligado").

Fluxo de Controle

    O cliente MQTT conecta-se ao broker e começa a escutar os tópicos configurados.
    As mensagens de temperatura, umidade e status são recebidas e armazenadas em filas (deque).
    A cada intervalo (2 segundos), os gráficos de temperatura e umidade são atualizados.
    O status do sistema também é atualizado a cada intervalo.


Exemplo de Saída

Quando o ESP32 está funcionando corretamente e publicando os dados via MQTT, você verá a seguinte saída no painel Dash:

    Tópicos MQTT:
        /monitor/temperature: 24.50
        /monitor/humidity: 55.00
        /monitor/status: "Ventilador Ligado"

Autor(es)

    Gabriel Luni Nakashima
    Melyssa Huang
    Gabriel Lacerda

Licença

Este projeto é distribuído sob a licença MIT. Consulte o arquivo LICENSE para mais detalhes.
