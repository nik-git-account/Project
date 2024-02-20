/*
 * dht22.h
 *
 *  Created on: Jan 9, 2024
 *      Author: parag
 */

#ifndef INC_DHT22_H_
#define INC_DHT22_H_

#define DHT_PORT GPIOA
#define DHT_PIN GPIO_PIN_5


typedef struct
{
	float Temperature;
	float Humidity;
}DHT_DataTypedef;


void DHT_GetData (DHT_DataTypedef *DHT_Data);


#endif /* INC_DHT22_H_ */
