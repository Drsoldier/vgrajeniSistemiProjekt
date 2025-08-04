#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/Unicode.hpp>
#include "touchgfx/Unicode.hpp"
#include "stdlib.h"
extern int32_t tempC;
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
	if(a>0){
		howHotItIsPainter.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	}else{
		howHotItIsPainter.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
	}
	a = -a;
	howHotItIs.invalidate();
}

void Screen1View::updateTemperature(){
	touchgfx::Unicode::UnicodeChar* neki = (touchgfx::Unicode::UnicodeChar*)malloc(10*(sizeof(touchgfx::Unicode::UnicodeChar)));
	Unicode::itoa(7, neki, 10, 10);
	Unicode::snprintf(temperatureBuffer, 10, "%s", neki);
	whatIsLock.setWildcard(whatIsLockBuffer);
	whatIsLock.resizeToCurrentText();
	free(neki);
	//temperature.resizeToCurrentText();
	temperature.invalidate();
}
