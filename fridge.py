import serial
import pymysql
import time

# Define the device and baud rate for the Arduino serial connection
device = '/dev/ttyS0'
baud_rate = 9600

# Connect to the Arduino serial port
arduino = serial.Serial(device, baud_rate)

# Connect to the MySQL database
dbConn = pymysql.connect("localhost", "", "", "assignment_db")

# Print the database connection status
print(dbConn)

try:
    while True:
        # Read data from Arduino
        data = arduino.readline().decode().strip()
        print("Received data:", data)

        # Split the data into temperature, status, ldr_number, and fridge_door
        temperature, status, ldr_number, fridge_door = data.split(' ', 3)
        temperature = float(temperature)
        ldr_number = int(ldr_number)

        # Print the parsed values
        print("Temperature:", temperature)
        print("Status:", status)
        print("LDR Number:", ldr_number)
        print("Fridge Door:", fridge_door)

        # Create a cursor object to execute SQL queries
        with dbConn.cursor() as cursor:
            # Define the SQL query to insert data into the table
            sql = "INSERT INTO fridge_sensor (temperature, status, ldr_number, fridge_door) VALUES (%s, %s, %s, %s)"
            # Execute the SQL query with the values
            cursor.execute(sql, (temperature, status, ldr_number, fridge_door))
            
            # Commit the changes to the database
            dbConn.commit()

        # Print a message indicating successful insertion
        print("Data inserted successfully!")

        # Wait for a short duration before reading the next data
        time.sleep(5)  

except Exception as e:
    # If an error occurs, print the error message
    print("Error:", e)

finally:
    # Close the Arduino serial connection
    arduino.close()

    # Close the database connection
    dbConn.close()
