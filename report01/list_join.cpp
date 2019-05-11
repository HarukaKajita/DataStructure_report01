// 線形探索（配列の動的確保）
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

// セルを表わす構造体の定義 
struct cell
{
	char name[256];           // キー
	char telNum[256];    // キーに対応する値（文字列）

	struct cell* next;	// 次のデータへのポインタ
};

// 機能：リストの要素生成
// 引数: int key キー
//       char *data 対応するデータとなる文字列
// 戻値: 生成された要素へのポインタ． 
struct cell* make_cell(const char* name, const char* data)
{
	struct cell* mk_cell;

	// cellの領域を確保する 
	mk_cell = new struct cell;

	/* 文字列 data を cell->data へコピーする */
	strcpy_s(mk_cell->telNum, data);

	// 整数へ変換
	strcpy_s(mk_cell->name, name);

	// nextを初期化
	mk_cell->next = NULL;

	return mk_cell;
}

//リストの構築
cell* struct_list(ifstream &stream, cell* head) {
	string line;
	
	while (stream >> line)
	{
		// ファイルからキーと対応する値（ファイル名）を取得
		int index = line.find(",");    // 区切り文字までの文字数
		string name_str = line.substr(0, index);
		string value = line.substr(index + 1);
		//cout << name_str << endl;
		//cout << value << endl;

		if (value.length() > 255)
		{
			cout << "length of value is too long\n";
			return NULL;
		}

		// リスト要素の生成
		struct cell* e_cell;
		e_cell = make_cell(name_str.data(), value.data());

		// 生成した要素をリストの先頭に追加
		e_cell->next = head;

		// 先頭アドレスを更新
		head = e_cell;
	}
	return head;
}

//リストの結合
void join_list(cell* head1, cell* head2) {
	cell* ptr = head1;
	cell* pre = NULL;
	while (ptr != NULL)
	{
		pre = ptr;
		ptr = ptr->next;
	}
	pre->next = head2;
}

//リストの出力
void print_file_list(cell* head) {
	const cell* ptr = head;
	while (ptr != NULL)
	{
		cout << ptr->name << " -> " << ptr->telNum << endl;
		ptr = ptr->next;
	}
}

int main(int argc, char* argv[])
{
	if (argc < 3)  // 引数が足りない場合
	{
		cout << "input file name\n";
		return -1;
	}

	// ファイルオープン
	ifstream fp1(argv[1]);
	ifstream fp2(argv[2]);

	// リストのヘッドを定義し初期化
	struct cell* head1;
	head1 = NULL;

	struct cell* head2;
	head2 = NULL;

	// データのリストへの格納
	cout << "Loading " << argv[1] << endl;
	head1 = struct_list(fp1, head1);
	fp1.close();

	cout << "Loading " << argv[2] << endl;
	head2 = struct_list(fp2, head2);
	fp2.close();
	
	// リスト head2を，リスト head1に結合（本関数を実装せよ）
	join_list(head1, head2);

	// head1を表示（木構造の講義資料を参照）
	print_file_list(head1);

	return 0;
}