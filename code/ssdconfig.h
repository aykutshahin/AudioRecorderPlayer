/*
 * ssdconfig.h
 *
 * Created by Aykut Sahin
 * Updated for Audio Recorder & Player
 */

#ifndef SSDCONFIG_H_
#define SSDCONFIG_H_
#include "stm32g0xx.h"
#include <string.h>

 //Segments BEGIN
 //To light A LED
void SetSegmentA() {
	GPIOA->MODER &= ~(3U << 2 * 4);
	GPIOA->MODER |= (1U << 2 * 4);
}
//To light B LED
void SetSegmentB() {
	GPIOA->MODER &= ~(3U << 2 * 5);
	GPIOA->MODER |= (1U << 2 * 5);
}
//To light C LED
void SetSegmentC() {
	GPIOA->MODER &= ~(3U << 2 * 6);
	GPIOA->MODER |= (1U << 2 * 6);
}
//To light D LED
void SetSegmentD() {
	GPIOA->MODER &= ~(3U << 2 * 7);
	GPIOA->MODER |= (1U << 2 * 7);
}
//To light E LED
void SetSegmentE() {
	GPIOA->MODER &= ~(3U << 2 * 8);
	GPIOA->MODER |= (1U << 2 * 8);
}
//To light F LED
void SetSegmentF() {
	GPIOA->MODER &= ~(3U << 2 * 9);
	GPIOA->MODER |= (1U << 2 * 9);
}
//To light G LED
void SetSegmentG() {

	GPIOA->MODER &= ~(3U << 2 * 10);
	GPIOA->MODER |= (1U << 2 * 10);
}
//Segments END

//Numbers BEGIN
//To light Number 0
void SetNumberZero()
{
	SetSegmentA();
	SetSegmentB();
	SetSegmentC();
	SetSegmentD();
	SetSegmentE();
	SetSegmentF();
}
//To light Number 1
void SetNumberOne()
{
	SetSegmentB();
	SetSegmentC();
}
//To light Number 2
void SetNumberTwo()
{
	SetSegmentA();
	SetSegmentB();
	SetSegmentD();
	SetSegmentE();
	SetSegmentG();
}
//To light Number 3
void SetNumberThree()
{
	SetSegmentA();
	SetSegmentB();
	SetSegmentC();
	SetSegmentD();
	SetSegmentG();

}
//To light Number 4
void SetNumberFour()
{
	SetSegmentB();
	SetSegmentC();
	SetSegmentF();
	SetSegmentG();
}
//To light Number 5
void SetNumberFive()
{
	SetSegmentA();
	SetSegmentC();
	SetSegmentD();
	SetSegmentF();
	SetSegmentG();
}
//To light Number 6
void SetNumberSix()
{
	SetSegmentA();
	SetSegmentC();
	SetSegmentD();
	SetSegmentE();
	SetSegmentF();
	SetSegmentG();
}
//To light Number 7
void SetNumberSeven()
{
	SetSegmentA();
	SetSegmentB();
	SetSegmentC();
}
//To light Number 8
void SetNumberEight()
{
	SetSegmentA();
	SetSegmentB();
	SetSegmentC();
	SetSegmentD();
	SetSegmentE();
	SetSegmentF();
	SetSegmentG();
}
//To light Number 9
void SetNumberNine()
{
	SetSegmentA();
	SetSegmentB();
	SetSegmentC();
	SetSegmentD();
	SetSegmentF();
	SetSegmentG();
}
//To light Negative Sign
void SetNegativeSign()
{
	SetSegmentG();
}
//Numbers END

//Letters Begin
//To light Letter A
void SetLetterA()
{
	SetSegmentA();
	SetSegmentB();
	SetSegmentC();
	SetSegmentE();
	SetSegmentF();
	SetSegmentG();
}
//To light Letter B
void SetLetterB()
{
	SetSegmentC();
	SetSegmentD();
	SetSegmentE();
	SetSegmentF();
	SetSegmentG();
}
//To light Letter C
void SetLetterC()
{
	SetSegmentD();
	SetSegmentE();
	SetSegmentG();
}
//To light Letter D
void SetLetterD()
{
	SetSegmentB();
	SetSegmentC();
	SetSegmentD();
	SetSegmentE();
	SetSegmentG();
}
//To light Letter E
void SetLetterE()
{
	SetSegmentA();
	SetSegmentD();
	SetSegmentE();
	SetSegmentF();
	SetSegmentG();
}
//To light Letter I
void SetLetterI()
{
	SetSegmentE();
	SetSegmentF();
}
//To light Letter N
void SetLetterN()
{
	SetSegmentC();
	SetSegmentE();
	SetSegmentG();
}
//To light Letter V
void SetLetterV()
{
	SetSegmentC();
	SetSegmentD();
	SetSegmentE();

}
//To light Letter O
void SetLetterO()
{
	SetSegmentC();
	SetSegmentD();
	SetSegmentE();
	SetSegmentG();
}
//To light Letter U
void SetLetterU()
{
	SetSegmentB();
	SetSegmentC();
	SetSegmentD();
	SetSegmentE();
	SetSegmentF();
}
//To light Letter F
void SetLetterF()
{
	SetSegmentA();
	SetSegmentE();
	SetSegmentF();
	SetSegmentG();
}
//To light Letter L
void SetLetterL()
{
	SetSegmentD();
	SetSegmentE();
	SetSegmentF();
}
//To light Letter P
void SetLetterP()
{
	SetSegmentA();
	SetSegmentB();
	SetSegmentE();
	SetSegmentF();
	SetSegmentG();
}
//To light Letter R
void SetLetterR()
{
	SetSegmentE();
	SetSegmentG();
}
//Letters End

//To turn leftmost digit when shifter reachs to rightmost digit
void TurnBeginning()
{
	//B0
	GPIOB->MODER &= ~(3U << 2 * 0);
	GPIOB->MODER |= (1U << 2 * 0);
	GPIOB->BRR = (1U << 0);
	GPIOB->ODR |= (1U << 0);
	//B1
	GPIOB->MODER &= ~(0U << 2 * 1);
	GPIOB->BRR = (1U << 1);
	//B2
	GPIOB->MODER &= ~(0U << 2 * 2);
	GPIOB->BRR = (1U << 2);
	//B3
	GPIOB->MODER &= ~(0U << 2 * 3);
	GPIOB->BRR = (1U << 3);
}

//To shift digits that will be displayed
void ShiftDigit(unsigned int currIndex)
{
	if (currIndex >= 3)
	{
		TurnBeginning();
		return;
	}
	GPIOB->MODER &= ~(0U << 2 * (currIndex));
	GPIOB->MODER &= ~(3U << 2 * (currIndex + 1));
	GPIOB->MODER |= (1U << 2 * (currIndex + 1));
	GPIOB->BRR = (1U << currIndex);
	GPIOB->ODR |= (1U << (currIndex + 1));

}

//To display numbers
void DisplayChar(char ch)
{
	switch (ch)
	{
	case '0':
		SetNumberZero();
		break;
	case '1':
		SetNumberOne();
		break;
	case '2':
		SetNumberTwo();
		break;
	case '3':
		SetNumberThree();
		break;
	case '4':
		SetNumberFour();
		break;
	case '5':
		SetNumberFive();
		break;
	case '6':
		SetNumberSix();
		break;
	case '7':
		SetNumberSeven();
		break;
	case '8':
		SetNumberEight();
		break;
	case '9':
		SetNumberNine();
		break;
	case 'a':
		SetLetterA();
		break;
	case 'b':
		SetLetterB();
		break;
	case 'c':
		SetLetterC();
		break;
	case 'd':
		SetLetterD();
		break;
	case 'e':
		SetLetterE();
		break;
	case 'i':
		SetLetterI();
		break;
	case 'n':
		SetLetterN();
		break;
	case 'v':
		SetLetterV();
		break;
	case 'o':
		SetLetterO();
		break;
	case 'u':
		SetLetterU();
		break;
	case 'f':
		SetLetterF();
		break;
	case 'l':
		SetLetterL();
		break;
	case 'p':
		SetLetterP();
		break;
	case 'r':
		SetLetterR();
		break;
	default:
		break;
	}
}

char IntToChar(uint8_t digit)
{
	switch (digit)
	{
	  case 0:
		return '0';
	  case 1:
		return '1';
	  case 2:
		return '2';
	  case 3:
		return '3';
	  case 4:
		return '4';
	  case 5:
		return '5';
	  case 6:
		return '6';
	  case 7:
		return '7';
	  case 8:
		return '8';
	  case 9:
		return '9';
	  default:
		break;
	 }
	return '0';
}

//Clearing displayer
void ResetDisplay()
{
	uint8_t index;
	for(index = 4;index < 11;index++)
	{
		GPIOA->MODER &= ~(3U << 2 * index);
		GPIOA->MODER |= (3U << 2 * index);
		GPIOA->ODR &= ~(1U << index);
	}

}
#endif /* SSDCONFIG_H_ */
