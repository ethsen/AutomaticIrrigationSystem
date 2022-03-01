import pyfirmata
from pyfirmata import Arduino, util
import time

board = pyfirmata.Arduino('COM3')

moistureSensor1 = board.get_pin('a:0:i')
moistureSensor2 = board.get_pin('a:1:i')
moistureSensor3 = board.get_pin('a:2:i')
pump1 = board.get_pin('d:6:o')
pump2 = board.get_pin('d:7:o')

def moistureAverage(sensorLevel1, sensorLevel2, sensorLevel3):

    average = (sensorLevel1 + sensorLevel2 + sensorLevel3)/3

    return average

def doubleCheck():
    time.sleep(1)

    moistureLevel1 = moistureSensor1.read()
    moistureLevel2 = moistureSensor1.read()
    moistureLevel3 = moistureSensor1.read()

    averageMoisture = moistureAverage(moistureLevel1, moistureLevel2, moistureLevel3)

    if averageMoisture > .35:
        return True
    
    else:
        return False

def waterPlant(averageMoisture):
    time.sleep(1)

    while averageMoisture >.35:
        pump1.write(0)
        pump2.write(0)
        moistureLevel1 = moistureSensor1.read()
        moistureLevel2 = moistureSensor1.read()
        moistureLevel3 = moistureSensor1.read()
        averageMoisture = moistureAverage(moistureLevel1, moistureLevel2, moistureLevel3)

def main():
    it = pyfirmata.util.Iterator(board)
    it.start()

    while True:
        moistureLevel1 = moistureSensor1.read()
        moistureLevel2 = moistureSensor1.read()
        moistureLevel3 = moistureSensor1.read()

        averageMoisture = moistureAverage(moistureLevel1, moistureLevel2, moistureLevel3)

        if averageMoisture > .35:
            isSoilWet = doubleCheck()

            if isSoilWet == True:
                waterPlant(averageMoisture)
        
main()