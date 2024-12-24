import pymysql

class ConexionBD:
    def __init__(self, host, usuario, contraseña, base_datos):
        self.host = host
        self.usuario = usuario
        self.contraseña = contraseña
        self.base_datos = base_datos
        self.conexion = None
        self.cursor = None

    def conectar(self):
        """Conectar a la base de datos."""
        try:
            self.conexion = pymysql.connect(
                host=self.host,
                user=self.usuario,
                password=self.contraseña,
                database=self.base_datos
            )
            self.cursor = self.conexion.cursor()
            print("Conexión a la base de datos exitosa")
        except Exception as e:
            print(f"Error al conectar a la base de datos: {e}")

    def cerrar(self):
        """Cerrar la conexión a la base de datos."""
        if self.conexion:
            self.conexion.close()
            print("Conexión cerrada")

    def insertar_lectura(self, dispositivo_id, co2_ppm, temperatura, humedad, nivel_bateria):
        """Insertar una nueva lectura de sensores."""
        query = f"""
        INSERT INTO lecturas (dispositivo_id, co2_ppm, temperatura, humedad, nivel_bateria)
        VALUES ({dispositivo_id}, {co2_ppm}, {temperatura}, {humedad}, {nivel_bateria});
        """
        try:
            self.cursor.execute(query)
            self.conexion.commit()
            print("Lectura insertada correctamente")
        except Exception as e:
            print(f"Error al insertar la lectura: {e}")


    def insertar_alerta(self, dispositivo_id, tipo_alerta, nivel_co2, descripcion):
        """Insertar una nueva alerta."""
        query = f"""
        INSERT INTO alertas (dispositivo_id, tipo_alerta, nivel_co2, descripcion)
        VALUES ({dispositivo_id}, '{tipo_alerta}', {nivel_co2}, '{descripcion}');
        """
        try:
            self.cursor.execute(query)
            self.conexion.commit()
            print("Alerta insertada correctamente")
        except Exception as e:
            print(f"Error al insertar la alerta: {e}")

    def insertar_estado_bateria(self, dispositivo_id, nivel_bateria):
        """Insertar un nuevo estado de batería."""
        query = f"""
        INSERT INTO estado_de_bateria (dispositivo_id, nivel_bateria)
        VALUES ({dispositivo_id}, {nivel_bateria});
        """
        try:
            self.cursor.execute(query)
            self.conexion.commit()
            print("Estado de batería insertado correctamente")
        except Exception as e:
            print(f"Error al insertar el estado de batería: {e}")
