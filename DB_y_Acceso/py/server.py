from flask import Flask, request, jsonify
from metodos_db import ConexionBD

app = Flask(__name__)

# Inicializar la conexión a la base de datos
bd = ConexionBD('localhost', 'root', 'root', 'control_ambiental')
bd.conectar()

@app.route('/api/lecturas', methods=['POST'])
def recibir_lecturas():
    """Endpoint para recibir las lecturas de los sensores vía POST"""
    # Obtener la clave API desde el encabezado HTTP
    clave_api = request.headers.get('X-API-KEY')

    # Validar clave API
    if clave_api not in ['silver', 'gold', 'adamantium']:
        return jsonify({'error': 'Clave API no válida'}), 401

    # Extraer los datos del cuerpo de la solicitud
    data = request.json
    dispositivo_id = data.get('dispositivo_id')
    co2_ppm = data.get('co2_ppm')
    temperatura = data.get('temperatura')
    humedad = data.get('humedad')
    nivel_bateria = data.get('nivel_bateria')

    # Verificar si todas las claves existen en el JSON
    if dispositivo_id is None or co2_ppm is None or temperatura is None or humedad is None or nivel_bateria is None:
        return jsonify({'error': 'Datos incompletos'}), 400

    # Insertar datos en la base de datos
    try:
        bd.insertar_lectura(dispositivo_id, co2_ppm, temperatura, humedad, nivel_bateria)

        # Verificar si hay que generar alertas
        if co2_ppm > 1000:
            bd.insertar_alerta(dispositivo_id, "Encendido extractor", co2_ppm, "CO2 excede los 1000 ppm")
        else:
            bd.insertar_alerta(dispositivo_id, "Apagado extractor", co2_ppm, "CO2 en nivel aceptable")

        if nivel_bateria < 3.5:
            bd.insertar_alerta(dispositivo_id, "Batería baja", nivel_bateria, "Nivel de batería bajo")

        # Insertar estado de la batería
        bd.insertar_estado_bateria(dispositivo_id, nivel_bateria)

        return jsonify({'status': 'Datos recibidos e insertados correctamente'}), 200
    except Exception as e:
        return jsonify({'error': str(e)}), 500
