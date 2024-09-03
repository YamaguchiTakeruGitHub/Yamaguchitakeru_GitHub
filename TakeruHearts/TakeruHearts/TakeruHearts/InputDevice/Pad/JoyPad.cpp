#include "JoyPad.h"

InputDevice::JoyPad::JoyPad()
	: pad()
	, Pad1(GetJoypadInputState(DX_INPUT_PAD1))
	, count(0)
	, isA(false)
	, isB(false)
	, isX(false)
	, isY(false)
	, isLB(false)
	, isRB(false)
	, isBACK(false)
	, isSTART(false)
	, isSTICKBL(false)
	, isSTICKBR(false)
	, isDUP(false)
	, isDRIGHT(false)
	, isDDOWN(false)
	, isDLEFT(false)
	


	, pisA(false)
	, pisB(false)
	, pisX(false)
	, pisY(false)
	, pisLB(false)
	, pisRB(false)
	, pisBACK(false)
	, pisSTART(false)
	, pisSTICKL(false)
	, pisSTICKR(false)

	, pisDUP(false)
	, pisDRIGHT(false)
	, pisDDOWN(false)
	, pisDLEFT(false)
{
}

InputDevice::JoyPad::~JoyPad()
{
}

void InputDevice::JoyPad::Init()
{
	Pad1 = GetJoypadInputState(DX_INPUT_PAD1);
	count = 0;

	isA = false;
	isB = false;
	isX = false;
	isY = false;
	isLB = false;
	isRB = false;
	isBACK = false;
	isSTART = false;
	isSTICKBL = false;
	isSTICKBR = false;

	isDUP = false;
	isDRIGHT = false;
	isDDOWN = false;
	isDLEFT = false;



	pisA = false;
	pisB = false;
	pisX = false;
	pisY = false;
	pisLB = false;
	pisRB = false;
	pisBACK = false;
	pisSTART = false;
	pisSTICKL = false;
	pisSTICKR = false;

	pisDUP = false;
	pisDRIGHT = false;
	pisDDOWN = false;
	pisDLEFT = false;

}

void InputDevice::JoyPad::Update()
{
	isA = false;
	isB = false;
	isX = false;
	isY = false;
	isLB = false;
	isRB = false;
	isBACK = false;
	isSTART = false;
	isSTICKBL = false;
	isSTICKBR = false;

	isDUP = false;
	isDRIGHT = false;
	isDDOWN = false;
	isDLEFT = false;



	/*ボタン（start）*/

	//Aボタン
	if (pad.Buttons[PadButton::A] && !pisA)
	{
		pisA = true;
		isA = true;//別クラスで判定する用のフラグ
	}
	//Bボタン
	if (pad.Buttons[PadButton::B])
	{
		pisB = true;
		isB = true;//別クラスで判定する用のフラグ
	}
	//Yボタン
	if (pad.Buttons[PadButton::Y])
	{
		pisY = true;
		isY = true;//別クラスで判定する用のフラグ
	}
	//Xボタン
	if (pad.Buttons[PadButton::X])
	{
		pisX = true;
		isX = true;//別クラスで判定する用のフラグ
	}
	//LBボタン
	if (pad.Buttons[PadButton::LB])
	{
		pisLB = true;
		isLB = true;//別クラスで判定する用のフラグ
	}
	//RBボタン
	if (pad.Buttons[PadButton::RB])
	{
		pisRB = true;
		isRB = true;//別クラスで判定する用のフラグ
	}
	//BACKボタン
	if (pad.Buttons[PadButton::BACK])
	{
		pisBACK = true;
		isBACK = true;//別クラスで判定する用のフラグ
	}
	//STARTボタン
	if (pad.Buttons[PadButton::START])
	{
		pisSTART = true;
		isSTART = true;//別クラスで判定する用のフラグ
	}
	//STICKLボタン
	if (pad.Buttons[PadButton::STICKBL])
	{
		pisSTICKL = true;
		isSTICKBL = true;//別クラスで判定する用のフラグ
	}
	//STICKRボタン
	if (pad.Buttons[PadButton::STICKBR])
	{
		pisSTICKR = true;
		isSTICKBR = true;//別クラスで判定する用のフラグ
	}

	//特定のボタンが押されていない時はフラグをおろす
	if (!pad.Buttons[PadButton::A] 
		&& !pad.Buttons[PadButton::B] 
		&& !pad.Buttons[PadButton::Y] 
		&& !pad.Buttons[PadButton::X] 
		&& !pad.Buttons[PadButton::LB]
		&& !pad.Buttons[PadButton::RB]
		&& !pad.Buttons[PadButton::BACK]
		&& !pad.Buttons[PadButton::START]
		&& !pad.Buttons[PadButton::STICKBL]
		&& !pad.Buttons[PadButton::STICKBR])
	{
		pisA = false;
		pisA = false;
		pisB = false;
		pisX = false;
		pisY = false;
		pisLB = false;
		pisRB = false;
		pisBACK = false;
		pisSTART = false;
		pisSTICKL = false;
		pisSTICKR = false;

		pisDUP = false;
		pisDRIGHT = false;
		pisDDOWN = false;
		pisDLEFT = false;
	}
	/*ボタン（end）*/

	/*十字キー（start）*/
	switch (pad.POV[PadButton::CROSSKEY])
	{
	case PadButton::DUP://上
		count++;
		isDUP = true;//別クラスで判定する用のフラグ
		break;

	case PadButton::DRIGHT://右
		count = 0;
		isDRIGHT = true;//別クラスで判定する用のフラグ
		break;

	case PadButton::DDOWN://下
		count--;
		isDDOWN = true;//別クラスで判定する用のフラグ
		break;

	case PadButton::DLEFT://左
		count = 1000;
		isDLEFT = true;//別クラスで判定する用のフラグ
		break;

	default:
		break;
	}
	/*十字キー（end）*/


	/*ジョイステック(strat)*/

	

	/*ジョイステック(end)*/


}



void InputDevice::JoyPad::Draw()
{
	//入力を取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &pad);


#if _DEBUG
	DrawFormatString(100, 100, 0xffffff, "%d", count);


	int i;
	int Color;


	// 画面に構造体の中身を描画
	Color = GetColor(255, 255, 255);
	DrawFormatString(0, 500, Color, "X:%d Y:%d Z:%d",
		pad.X, pad.Y, pad.Z);
	DrawFormatString(0, 516, Color, "Rx:%d Ry:%d Rz:%d",
		pad.Rx, pad.Ry, pad.Rz);
	DrawFormatString(0, 532, Color, "Slider 0:%d 1:%d",
		pad.Slider[0], pad.Slider[1]);
	DrawFormatString(0, 548, Color, "POV 0:%d 1:%d 2:%d 3:%d",
		pad.POV[0], pad.POV[1],
		pad.POV[2], pad.POV[3]);
	DrawString(0, 564, "Button", Color);
	for (i = 0; i < 32; i++)
	{
		DrawFormatString(64 + i % 8 * 64, 564 + i / 8 * 16, Color,
			"%2d:%d", i, pad.Buttons[i]);
	}

#endif

}

