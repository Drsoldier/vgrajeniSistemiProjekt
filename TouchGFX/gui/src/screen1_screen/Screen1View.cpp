#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
class Screen1View : public Screen1ViewBase
{
public:
	virtual void changeColor() override;
	virtual void updateTemperature() override;
	virtual void enableLockFunction() override;
	virtual void readFromSensor() override;
	virtual void setHumidity() override;
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREEN1VIEW_HPP

//---------------------------------------------------------------------------------


#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/Unicode.hpp>
#include "touchgfx/Unicode.hpp"
#include "stm32h7xx_hal.h"
#include "stdlib.h"
extern float temperatureInCelcius;
extern float humidityValue;
volatile extern int32_t isLocked;
volatile extern int32_t isEnabled;
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
	int prefix = 1;
	if(temperatureInCelcius < 0){
		prefix = -1;
	}else{
		prefix = 1;
	}
	int zgornjiDel = floor(temperatureInCelcius*prefix);
	int decimal = floor((prefix*temperatureInCelcius*100.0 - zgornjiDel*100.0));
	Unicode::snprintf(temperatureBuffer, TEMPERATURE_SIZE, "%d.%d", zgornjiDel*prefix, decimal);

	temperature.setWildcard(temperatureBuffer);
	temperature.resizeToCurrentText();
	temperature.invalidate();

}

void Screen1View::setHumidity(){
	int humidityInt = floor(humidityValue);
	humidity.invalidateContent();
	if(!isEnabled){
		return;
	}
	Unicode::snprintf(humidityBuffer, HUMIDITY_SIZE, "%d", humidityInt);

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
		temperature.invalidateContent();
		humidity.invalidateContent();
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



