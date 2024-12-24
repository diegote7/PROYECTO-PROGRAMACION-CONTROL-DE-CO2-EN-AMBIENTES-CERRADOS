from server import app  # Importamos el objeto `app` del servidor Flask

def iniciar_servidor():
    """Función para inicializar el servidor Flask"""
    app.run(debug=True, host='0.0.0.0', port=5000)

if __name__ == "__main__":
    iniciar_servidor()
