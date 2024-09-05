#include "SpeechBubble.h"

UI::SpeechBubble::SpeechBubble()
	: speechBubbleGraphHandle(-1)
	, position()
{
}

UI::SpeechBubble::~SpeechBubble()
{
	DeleteGraph(speechBubbleGraphHandle);
}

void UI::SpeechBubble::Init()
{
	speechBubbleGraphHandle = LoadGraph("../Data/Asset/img/speechBubbleBIG.png");
}

void UI::SpeechBubble::Update(VECTOR pos)
{
	position = pos;
}

void UI::SpeechBubble::Draw()
{
	DrawGraph(position.x, position.y, speechBubbleGraphHandle, true);
}

void UI::SpeechBubble::Final()
{
	DeleteGraph(speechBubbleGraphHandle);
}
