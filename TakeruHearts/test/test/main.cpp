#include "DxLib.h"

#include <list>



// �E�B���h�E�T�C�Y
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
//
//// ���j���[���ڂ̐�
//const int MENU_ITEM_COUNT = 3;
//// �I�𒆂̃��j���[����
//int selectedItem = 0;
//
//// �t�F�[�h�C���G�t�F�N�g�̏��
//int fadeAlpha = 0;
//const int FADE_SPEED = 5;
//
//void UpdateFadeEffect() {
//    if (fadeAlpha < 255) {
//        fadeAlpha += FADE_SPEED;
//        if (fadeAlpha > 255) fadeAlpha = 255;
//    }
//}
//
//void DrawMenu() {
//    // �w�i�̕`��
//    DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);
//
//    // ���j���[���ڂ̕`��
//    for (int i = 0; i < MENU_ITEM_COUNT; ++i) {
//        int y = 100 + i * 50;
//        if (i == selectedItem) {
//            SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
//            DrawBox(0, y - 10, WINDOW_WIDTH, y + 30, GetColor(255, 100, 100), TRUE);
//            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//        }
//        DrawString(50, y, "Menu Item", GetColor(255, 255, 255));
//    }
//}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // DxLib������
    ChangeWindowMode(TRUE);
    SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
    if (DxLib_Init() == -1) {
        return -1;
    }
    SetDrawScreen(DX_SCREEN_BACK);

    // ���C�����[�v
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        // �t�F�[�h�C���G�t�F�N�g�̍X�V
        //UpdateFadeEffect();

        //// ���͏���
        //if (CheckHitKey(KEY_INPUT_DOWN)) {
        //    selectedItem = (selectedItem + 1) % MENU_ITEM_COUNT;
        //    fadeAlpha = 0;  // �t�F�[�h�C�������Z�b�g
        //}
        //if (CheckHitKey(KEY_INPUT_UP)) {
        //    selectedItem = (selectedItem - 1 + MENU_ITEM_COUNT) % MENU_ITEM_COUNT;
        //    fadeAlpha = 0;  // �t�F�[�h�C�������Z�b�g
        //}

        //// ���j���[�̕`��
        //DrawMenu();



        std::list<int> ls = { 1 };
        //ls.clear();
        ls.begin();
        for (int x : ls)
        {
           
           DrawFormatString(0, 0, 0xffffff, "%d", x);
            
        }


    }

    // DxLib�I��
    DxLib_End();
    return 0;
}