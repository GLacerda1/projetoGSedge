import dash
from dash import dcc, html
from dash.dependencies import Input, Output
import plotly.graph_objs as go
import paho.mqtt.client as mqtt
from collections import deque
import json

# Variáveis globais para armazenar os dados
temperatures = deque(maxlen=50)
humidities = deque(maxlen=50)
statuses = deque(maxlen=50)
timestamps = deque(maxlen=50)

# Configuração do Broker MQTT
BROKER = "4.228.61.195"  # Endereço do broker (exemplo)
PORT = 1883               # Porta padrão MQTT
TOPIC_TEMP = "/monitor/temperature"
TOPIC_HUM = "/monitor/humidity"
TOPIC_STATUS = "/monitor/status"

# Callback quando uma mensagem é recebida
def on_message(client, userdata, msg):
    global temperatures, humidities, statuses, timestamps
    topic = msg.topic
    payload = msg.payload.decode()
    current_time = len(timestamps)  # Exemplo simples de timestamp

    if topic == TOPIC_TEMP:
        temperatures.append(float(payload))
        timestamps.append(current_time)
    elif topic == TOPIC_HUM:
        humidities.append(float(payload))
    elif topic == TOPIC_STATUS:
        statuses.append(payload)

# Inicializando cliente MQTT
mqtt_client = mqtt.Client()
mqtt_client.on_message = on_message
mqtt_client.connect(BROKER, PORT, 60)
mqtt_client.subscribe([(TOPIC_TEMP, 0), (TOPIC_HUM, 0), (TOPIC_STATUS, 0)])
mqtt_client.loop_start()

# Inicializando o app Dash
app = dash.Dash(__name__)
app.title = "Dashboard IoT - Wokwi"

app.layout = html.Div([
    html.H1("Monitoramento IoT - Wokwi", style={'text-align': 'center'}),
    # Gráfico de Temperatura
    dcc.Graph(id='temp-graph'),
    # Gráfico de Umidade
    dcc.Graph(id='hum-graph'),
    # Status Atual
    html.Div(id='status-display', style={'text-align': 'center', 'font-size': '20px', 'margin-top': '20px'}),
    # Intervalo de atualização
    dcc.Interval(
        id='update-interval',
        interval=2000,  # Atualizar a cada 2 segundos
        n_intervals=0
    )
])

# Callback para atualizar o gráfico de temperatura
@app.callback(
    Output('temp-graph', 'figure'),
    Input('update-interval', 'n_intervals')
)
def update_temp_graph(n):
    fig = go.Figure()
    fig.add_trace(go.Scatter(x=list(timestamps), y=list(temperatures), mode='lines+markers', name='Temperatura'))
    fig.update_layout(title="Temperatura ao longo do tempo",
                      xaxis_title="Tempo",
                      yaxis_title="Temperatura (°C)")
    return fig

# Callback para atualizar o gráfico de umidade
@app.callback(
    Output('hum-graph', 'figure'),
    Input('update-interval', 'n_intervals')
)
def update_hum_graph(n):
    fig = go.Figure()
    fig.add_trace(go.Scatter(x=list(timestamps), y=list(temperatures), mode='lines+markers', name='Temperatura'))
    fig.update_layout(title="Temperatura ao longo do tempo",
                      xaxis_title="Tempo",
                      yaxis_title="Temperatura (°C)")
    return fig

# Callback para atualizar o gráfico de umidade
@app.callback(
    Output('hum-graph', 'figure'),
    Input('update-interval', 'n_intervals')
)
def update_hum_graph(n):
    fig = go.Figure()
    fig.add_trace(go.Scatter(x=list(timestamps), y=list(humidities), mode='lines+markers', name='Umidade'))
    fig.update_layout(title="Umidade ao longo do tempo",
                      xaxis_title="Tempo",
                      yaxis_title="Umidade (%)")
    return fig

# Callback para exibir o status atual
@app.callback(
    Output('status-display', 'children'),
    Input('update-interval', 'n_intervals')
)
def update_status(n):
    if statuses:
        return f"Status Atual: {statuses[-1]}"
    return "Status Atual: Não disponível"

if __name__ == '__main__':
    app.run_server(host='0.0.0.0', port=8050, debug=True)
