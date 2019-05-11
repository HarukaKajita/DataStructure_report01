//// 線形探索（配列の動的確保）
//#include <iostream>
//#include <fstream>
//#include <stdlib.h>
//#include <string.h>
////時間計測用
//#include <chrono>
//
//using namespace std;
//
//// セルを表わす構造体の定義 
//struct cell
//{
//	int key;           // キー
//	char data[256];    // キーに対応する値（文字列）
//
//	struct cell* next;	// 次のデータへのポインタ
//};
//
//// 機能：リストの要素生成
//// 引数: int key キー
////       char *data 対応するデータとなる文字列
//// 戻値: 生成された要素へのポインタ． 
//struct cell* make_cell(int key, const char* data)
//{
//	struct cell* mk_cell;
//
//	// cellの領域を確保する 
//	mk_cell = new struct cell;
//
//	/* 文字列 data を cell->data へコピーする */
//	strcpy_s(mk_cell->data, data);
//
//	// 整数へ変換
//	mk_cell->key = key;
//
//	// nextを初期化
//	mk_cell->next = NULL;
//
//	return mk_cell;
//}
//
//
//// 機能：リストを検索
//// 引数：head -- リストの先頭要素のアドレス
////       key -- 検索したいキー
//// 戻値：キーが存在した要素のポインタ．ない場合は NULL
//struct cell* search_cell(struct cell* head, int key)
//{
//	struct cell* buf;
//	buf = head;
//
//	while (buf != NULL)
//	{
//		if (buf->key == key)
//		{
//			return buf;
//		}
//
//		buf = buf->next;
//	}
//
//	return NULL;
//}
//
//
//int main(int argc, char* argv[])
//{
//	if (argc == 1)  // 引数がない場合
//	{
//		cout << "input file name\n";
//		return -1;
//	}
//
//	// ファイルオープン
//	ifstream fp(argv[1]);
//
//	// リストのヘッドを定義し初期化
//	struct cell* head;
//	head = NULL;
//
//	// データのリストへの格納
//	cout << "Loading " << argv[1] << endl;
//	string line;
//
//  //構築時間の計測開始
//	chrono::system_clock::time_point start, end;
//	start = chrono::system_clock::now();
//
//	while (fp >> line)
//	{
//		// ファイルからキーと対応する値（ファイル名）を取得
//		int index = line.find(",");    // 区切り文字までの文字数
//		string key_str = line.substr(0, index);
//		string value = line.substr(index + 1);
//
//		// キーを整数変換 （本当は危険）
//		int key = atoi(key_str.data());
//
//		if (value.length() > 255)
//		{
//			cout << "length of value is too long\n";
//			return -1;
//		}
//
//		// リスト要素の生成
//		struct cell* e_cell;
//		e_cell = make_cell(key, value.data());
//
//		// 生成した要素をリストの先頭に追加
//		e_cell->next = head;
//
//		// 先頭アドレスを更新
//		head = e_cell;
//	}
//	//構築時間の計測終了
//	end = chrono::system_clock::now();
//	double elapse = chrono::duration_cast<chrono::microseconds>(end - start).count();
//	cout << "構築時間：" << elapse << " (micro sec)" << endl;
//
//	//0~1000の整数をkeyにして1000回検索し、探索時間を計測
//	start = chrono::system_clock::now();
//
//	for (int i = 0; i < 1000; i++)
//	{
//		int ky = i;
//		// 配列 data から値がkyである要素番号を探索
//		struct cell* s_cell;
//		s_cell = search_cell(head, ky);
//
//		if (s_cell == NULL)
//		{
//			cout << ky << "に対応する値は存在していません。" << endl;
//		}
//		else
//		{
//			cout << s_cell->key << " -> " << s_cell->data << endl;
//		}
//	}
//	//探索時間の計測終了
//	end = chrono::system_clock::now();
//	elapse = chrono::duration_cast<chrono::microseconds>(end - start).count();
//	cout << "探索時間：" << elapse << " (micro sec)" << endl;
//	fp.close();
//
//	return 0;
//}