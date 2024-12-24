-- Crear la base de datos si no existe
CREATE DATABASE IF NOT EXISTS control_ambiental;
USE control_ambiental;

-- Tabla de dispositivos IoT
CREATE TABLE IF NOT EXISTS dispositivos (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100),
    ubicacion VARCHAR(100),
    tipo_sensor VARCHAR(100),
    estado BOOLEAN DEFAULT 1,  -- 1 para activo, 0 para inactivo
    fecha_instalacion DATE,
    ultima_revision DATE,
    firmware_version VARCHAR(20)
);

-- Tabla de lecturas de sensores (CO2, temperatura, humedad, nivel de batería)
CREATE TABLE IF NOT EXISTS lecturas (
    id INT AUTO_INCREMENT PRIMARY KEY,
    dispositivo_id INT,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    co2_ppm FLOAT,
    temperatura FLOAT,
    humedad FLOAT,
    nivel_bateria FLOAT,
    FOREIGN KEY (dispositivo_id) REFERENCES dispositivos(id) ON DELETE CASCADE ON UPDATE CASCADE
);

-- Tabla de alertas
CREATE TABLE IF NOT EXISTS alertas (
    id INT AUTO_INCREMENT PRIMARY KEY,
    dispositivo_id INT,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    tipo_alerta VARCHAR(50),  -- Tipos de alertas: 'Encendido extractor', 'Apagado extractor', 'Batería baja', 'Corte eléctrico'
    nivel_co2 FLOAT,  -- Nivel de CO2 al momento de la alerta
    descripcion TEXT,
    FOREIGN KEY (dispositivo_id) REFERENCES dispositivos(id) ON DELETE CASCADE ON UPDATE CASCADE
);

-- Tabla de estado de batería
CREATE TABLE IF NOT EXISTS estado_de_bateria (
    id INT AUTO_INCREMENT PRIMARY KEY,
    dispositivo_id INT,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    nivel_bateria FLOAT,
    FOREIGN KEY (dispositivo_id) REFERENCES dispositivos(id) ON DELETE CASCADE ON UPDATE CASCADE
);

-- Tabla de eventos del extractor
CREATE TABLE IF NOT EXISTS eventos_extractor (
    id INT AUTO_INCREMENT PRIMARY KEY,
    dispositivo_id INT,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    accion VARCHAR(10),  -- "ENCENDIDO" o "APAGADO"
    co2_ppm FLOAT,  -- Nivel de CO2 al momento del evento
    FOREIGN KEY (dispositivo_id) REFERENCES dispositivos(id) ON DELETE CASCADE ON UPDATE CASCADE
);

-- Insertar algunos dispositivos de ejemplo
INSERT INTO dispositivos (nombre, ubicacion, tipo_sensor, fecha_instalacion, firmware_version)
VALUES
('ESP32_Sensor_1', 'Oficina 1', 'MQ135 + AHT25', '2024-09-10', 'v1.0.0'),
('ESP32_Sensor_2', 'Laboratorio', 'MQ135 + AHT25', '2024-09-12', 'v1.0.0');
