#include "DxLib.h"

#include <list>



// ウィンドウサイズ
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
//
//// メニュー項目の数
//const int MENU_ITEM_COUNT = 3;
//// 選択中のメニュー項目
//int selectedItem = 0;
//
//// フェードインエフェクトの状態
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
//    // 背景の描画
//    DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);
//
//    // メニュー項目の描画
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
    // DxLib初期化
    ChangeWindowMode(TRUE);
    SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
    if (DxLib_Init() == -1) {
        return -1;
    }
    SetDrawScreen(DX_SCREEN_BACK);

    // メインループ
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        // フェードインエフェクトの更新
        //UpdateFadeEffect();

        //// 入力処理
        //if (CheckHitKey(KEY_INPUT_DOWN)) {
        //    selectedItem = (selectedItem + 1) % MENU_ITEM_COUNT;
        //    fadeAlpha = 0;  // フェードインをリセット
        //}
        //if (CheckHitKey(KEY_INPUT_UP)) {
        //    selectedItem = (selectedItem - 1 + MENU_ITEM_COUNT) % MENU_ITEM_COUNT;
        //    fadeAlpha = 0;  // フェードインをリセット
        //}

        //// メニューの描画
        //DrawMenu();



        std::list<int> ls = { 1 };
        //ls.clear();
        ls.begin();
        for (int x : ls)
        {
           
           DrawFormatString(0, 0, 0xffffff, "%d", x);
            
        }


    }

    // DxLib終了
    DxLib_End();
    return 0;
}