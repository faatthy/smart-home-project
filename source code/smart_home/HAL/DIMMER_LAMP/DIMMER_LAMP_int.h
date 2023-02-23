/*
 * DIMMER_LAMP_int.h
 *
 *  Created on: Feb 4, 2023
 *      Author: fathy
 */

#ifndef HAL_DIMMER_LAMP_DIMMER_LAMP_INT_H_
#define HAL_DIMMER_LAMP_DIMMER_LAMP_INT_H_

ES_t DIMMER_LAMP_enuInit(void);
ES_t DIMMER_LAMP_enuSetIntensity(u8 Copy_u8Intensity);
ES_t DIMMER_LAMP_enuStart(void);
ES_t DIMMER_LAMP_enuStop(void);

#endif /* HAL_DIMMER_LAMP_DIMMER_LAMP_INT_H_ */
