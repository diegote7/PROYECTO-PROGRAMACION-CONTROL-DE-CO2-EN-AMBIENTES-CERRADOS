import requests
import random

# URL del servidor Flask
url = 'http://localhost:5000/api/lecturas'

def enviar_datos():
    """Simula el envío de datos del ESP32 a la API vía HTTP"""
    headers = {
        'X-API-KEY': 'adamantium'  # Clave API en el encabezado
    }

    data = {
        'dispositivo_id': 1,
        'co2_ppm': round(random.uniform(400, 2000), 2),
        'temperatura': round(random.uniform(18, 30), 2),
        'humedad': round(random.uniform(40, 60), 2),
        'nivel_bateria': round(random.uniform(3.0, 4.2), 2)  # Aseguramos un valor válido
    }

    # Enviar los datos al servidor
    response = requests.post(url, json=data, headers=headers)
    print(response.json())

if __name__ == "__main__":
    for _ in range(5):  # Simular 5 lecturas
        enviar_datos()
