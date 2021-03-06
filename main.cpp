/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//簡易タイマー

//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"

//########## マクロ定義 ##########
#define GAME_WIDTH	800	//画面の横の大きさ
#define GAME_HEIGHT	600	//画面の縦の大きさ
#define GAME_COLOR	32	//画面のカラービット

#define GAME_WINDOW_BAR	0	//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"GAME TITLE"	//ウィンドウのタイトル

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);						//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//指定の数値でウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR);		//タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));	//ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE);						//非アクティブでも実行する

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	int DrawX = 0;	//表示位置X
	int DrawY = 0;	//表示位置Y
	int time, time_2 = 0;
	int TimeLimit = 6;

	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画
	time = GetNowCount();

	//無限ループ(6秒たったら終了)
	while ((time_2 - time) < 6000)
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了

		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了
		//DrawFormatString(0, 100, GetColor(255, 255, 255), "立ち上がってから%dミリ秒", time);

		time_2 = GetNowCount();
		DrawFormatString(0, 100, GetColor(255, 255, 255), "あと %d秒", TimeLimit - (time_2 - time) / 1000);
		DrawString(DrawX, DrawY, "Hello World", GetColor(255, 255, 255));	//文字を描画

		ScreenFlip();		//モニタのリフレッシュレートの速さで裏画面を再描画
	}
	DxLib_End();	//ＤＸライブラリ使用の終了処理

	return 0;
}