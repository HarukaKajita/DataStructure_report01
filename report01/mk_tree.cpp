// 木構造の構築と検索
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
//時間計測用
#include <chrono>

using namespace std;


// ノードを表わす構造体の定義 
struct node
{
	int key;           // キー
	char data[256];    // キーに対応する値（文字列）

	struct node* r_next;	 // 次の右ノードへのポインタ
	struct node* l_next;  // 次の左ノードへのポインタ
};


// 機能：ツリーのノードを生成
// 引数: int key キー
//       char *data 対応するデータとなる文字列
// 戻値: 生成されたノードへのポインタ． 
struct node* make_node(int key, const char* data)
{
	struct node* e_node;

	// nodeの領域を確保する 
	e_node = new struct node;

	/* 文字列 data を cell->data へコピーする */
	strcpy_s(e_node->data, data);

	// 整数へ変換
	e_node->key = key;

	// nextを初期化
	e_node->r_next = NULL;
	e_node->l_next = NULL;

	return e_node;
}



// ノードをツリーに追加する
// 引数:  root -- ツリーのルートのポインタ
//        e_node -- ツリーに加えたいノードのポインタ
// 戻り値: なし
void insert_node(struct node* root, struct node* e_node)
{
	// 大小を比較し、ノード値よりも小さい場合
	if (root->key > e_node->key)
	{
		if (root->l_next != NULL)
		{
			// 左側にデータがある場合，再帰処理
			insert_node(root->l_next, e_node);
		}
		else
		{
			// 左側に追加する 
			root->l_next = e_node;
		}
	}
	else  // 大小を比較し、ノード値よりも大きい場合
	{
		if (root->r_next != NULL)
		{
			// 右側にデータがある場合，再帰処理
			insert_node(root->r_next, e_node);
		}
		else
		{
			// 右側に追加する 
			root->r_next = e_node;
		}
	}
}


// 機能：ツリーを検索
// 引数：root -- ツリーのルートのポインタ
//       key -- 検索したいキー
// 戻値：キーが存在したノードへのポインタ．ない場合は NULL
struct node* search_tree(struct node* root, int key)
{
	// ノードの値より小さい値ならば，左側 
	if (root->key > key)
	{
		// もし左側になければ，key はない
		if (root->l_next == NULL)
		{
			return NULL;
		}

		return search_tree(root->l_next, key);
	}

	// ノードの値より大きい値ならば，右側 
	if (root->key < key)
	{
		// もし右側になければ，key はない 
		if (root->r_next == NULL)
		{
			return NULL;
		}

		return search_tree(root->r_next, key);
	}

	// 見付かった場合
	if (root->key == key)
	{
		return root;
	}
}

int main(int argc, char* argv[])
{
	if (argc == 1)  // 引数がない場合
	{
		cout << "input file name\n";
		return -1;
	}

	// ファイルオープン
	ifstream fp(argv[1]);

	// ツリーのrootを定義し初期化
	struct node* root;
	root = NULL;

	// データのツリーへの格納
	cout << "Loading " << argv[1] << endl;
	string line;

	//構築時間の計測開始
	chrono::system_clock::time_point start, end;
	start = chrono::system_clock::now();

	while (fp >> line)
	{
		// ファイルからキーと対応する値（ファイル名）を取得
		int index = line.find(",");    // 区切り文字までの文字数
		string key_str = line.substr(0, index);
		string value = line.substr(index + 1);

		// キーを整数変換 （本当は危険）
		int key = atoi(key_str.data());

		if (value.length() > 255)
		{
			cout << "length of value is too long\n";
			return -1;
		}

		// cout << key << endl;

		// ノードの生成
		struct node* e_node;
		e_node = make_node(key, value.data());

		// １つもノードが存在しない場合
		if (root == NULL)
		{
			// 生成したノードをrootとしてツリーを開始
			root = e_node;
		}
		else
		{
			// ノードを追加
			insert_node(root, e_node);
		}
	}
	//構築時間の計測終了
	end = chrono::system_clock::now();
	double elapse = chrono::duration_cast<chrono::microseconds>(end - start).count();
	cout << "構築時間：" << elapse << " (micro sec)" << endl;
	fp.close();

	//0~1000の整数をkeyにして1000回検索し、探索時間を計測
	start = chrono::system_clock::now();
	for (int i = 0; i < 1000; i++)
	{
		int ky = i;
		// 配列 data から値がkyである要素番号を探索
		struct node* s_node = NULL;
		s_node = search_tree(root, ky);

		if (s_node == NULL)
		{
			cout << ky << "に対応する値は存在しません" << endl;
		}
		else
		{
			cout << s_node->key << " -> " << s_node->data << endl;
		}
	}
	//探索時間の計測終了
	end = chrono::system_clock::now();
	elapse = chrono::duration_cast<chrono::microseconds>(end - start).count();
	cout << "探索時間：" << elapse << " (micro sec)" << endl;

	return 0;
}