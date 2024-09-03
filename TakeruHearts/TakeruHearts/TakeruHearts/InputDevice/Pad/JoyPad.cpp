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



	/*�{�^���istart�j*/

	//A�{�^��
	if (pad.Buttons[PadButton::A] && !pisA)
	{
		pisA = true;
		isA = true;//�ʃN���X�Ŕ��肷��p�̃t���O
	}
	//B�{�^��
	if (pad.Buttons[PadButton::B])
	{
		pisB = true;
		isB = true;//�ʃN���X�Ŕ��肷��p�̃t���O
	}
	//Y�{�^��
	if (pad.Buttons[PadButton::Y])
	{
		pisY = true;
		isY = true;//�ʃN���X�Ŕ��肷��p�̃t���O
	}
	//X�{�^��
	if (pad.Buttons[PadButton::X])
	{
		pisX = true;
		isX = true;//�ʃN���X�Ŕ��肷��p�̃t���O
	}
	//LB�{�^��
	if (pad.Buttons[PadButton::LB])
	{
		pisLB = true;
		isLB = true;//�ʃN���X�Ŕ��肷��p�̃t���O
	}
	//RB�{�^��
	if (pad.Buttons[PadButton::RB])
	{
		pisRB = true;
		isRB = true;//�ʃN���X�Ŕ��肷��p�̃t���O
	}
	//BACK�{�^��
	if (pad.Buttons[PadButton::BACK])
	{
		pisBACK = true;
		isBACK = true;//�ʃN���X�Ŕ��肷��p�̃t���O
	}
	//START�{�^��
	if (pad.Buttons[PadButton::START])
	{
		pisSTART = true;
		isSTART = true;//�ʃN���X�Ŕ��肷��p�̃t���O
	}
	//STICKL�{�^��
	if (pad.Buttons[PadButton::STICKBL])
	{
		pisSTICKL = true;
		isSTICKBL = true;//�ʃN���X�Ŕ��肷��p�̃t���O
	}
	//STICKR�{�^��
	if (pad.Buttons[PadButton::STICKBR])
	{
		pisSTICKR = true;
		isSTICKBR = true;//�ʃN���X�Ŕ��肷��p�̃t���O
	}

	//����̃{�^����������Ă��Ȃ����̓t���O�����낷
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
	/*�{�^���iend�j*/

	/*�\���L�[�istart�j*/
	switch (pad.POV[PadButton::CROSSKEY])
	{
	case PadButton::DUP://��
		count++;
		isDUP = true;//�ʃN���X�Ŕ��肷��p�̃t���O
		break;

	case PadButton::DRIGHT://�E
		count = 0;
		isDRIGHT = true;//�ʃN���X�Ŕ��肷��p�̃t���O
		break;

	case PadButton::DDOWN://��
		count--;
		isDDOWN = true;//�ʃN���X�Ŕ��肷��p�̃t���O
		break;

	case PadButton::DLEFT://��
		count = 1000;
		isDLEFT = true;//�ʃN���X�Ŕ��肷��p�̃t���O
		break;

	default:
		break;
	}
	/*�\���L�[�iend�j*/


	/*�W���C�X�e�b�N(strat)*/

	

	/*�W���C�X�e�b�N(end)*/


}



void InputDevice::JoyPad::Draw()
{
	//���͂��擾
	GetJoypadDirectInputState(DX_INPUT_PAD1, &pad);


#if _DEBUG
	DrawFormatString(100, 100, 0xffffff, "%d", count);


	int i;
	int Color;


	// ��ʂɍ\���̂̒��g��`��
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

