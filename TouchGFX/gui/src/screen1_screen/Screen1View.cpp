
#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/Unicode.hpp>
#include "touchgfx/Unicode.hpp"
#include "stm32h7xx_hal.h"
#include "stdlib.h"
int32_t temperatureInCelcius;
int32_t humidityValue;
volatile int32_t isLocked;
volatile int32_t isEnabled;
Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

volatile int a = 1;

void Screen1View::changeColor(){
	temperature.invalidateContent();

	if(a>0){
		howHotItIsPainter.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	}else{
		howHotItIsPainter.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
	}
	a = -a;
	temperature.resizeToCurrentText();
	howHotItIs.invalidate();
}

void Screen1View::updateTemperature(){
	temperature.invalidateContent();
	if(!isEnabled){
		return;
	}
	if(temperatureInCelcius < 10 && temperatureInCelcius > 0){
		Unicode::snprintf(temperatureBuffer, TEMPERATURE_SIZE, "%d", temperatureInCelcius);
	}else{
		Unicode::snprintf(temperatureBuffer, TEMPERATURE_SIZE, "%d", temperatureInCelcius);
	}
	temperature.setWildcard(temperatureBuffer);
	temperature.resizeToCurrentText();
	temperature.invalidate();

}

void Screen1View::setHumidity(){

	humidity.invalidateContent();
	if(!isEnabled){
		return;
	}
	Unicode::snprintf(humidityBuffer, HUMIDITY_SIZE, "%d", humidityValue);

	humidity.setWildcard(humidityBuffer);
	humidity.resizeToCurrentText();
	humidity.invalidate();
}

void Screen1View::enableLockFunction(){
	whatIsLock.invalidateContent();
	if(isLocked){
		isLocked = 0;
		Unicode::snprintf(whatIsLockBuffer, WHATISLOCK_SIZE, "disabled");
	}else{
		isLocked = 1;
		Unicode::snprintf(whatIsLockBuffer, WHATISLOCK_SIZE, "enabled");
	}
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, isLocked ? GPIO_PIN_SET : GPIO_PIN_RESET);

	whatIsLock.resizeToCurrentText();
	whatIsLock.invalidate();

}

void Screen1View::readFromSensor(){
	isEnabled = !isEnabled;
	if(!isEnabled){
		Unicode::snprintf(temperatureBuffer, TEMPERATURE_SIZE, "????");
		Unicode::snprintf(humidityBuffer, HUMIDITY_SIZE, "????");
		temperature.setWildcard(temperatureBuffer);
		temperature.resizeToCurrentText();
		temperature.invalidate();
		humidity.setWildcard(humidityBuffer);
		humidity.resizeToCurrentText();
		humidity.invalidate();
		return;
	}
	updateTemperature();
	setHumidity();
}

