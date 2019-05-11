// ���`�T���i�z��̓��I�m�ہj
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

// �Z����\�킷�\���̂̒�` 
struct cell
{
	char name[256];           // �L�[
	char telNum[256];    // �L�[�ɑΉ�����l�i������j

	struct cell* next;	// ���̃f�[�^�ւ̃|�C���^
};

// �@�\�F���X�g�̗v�f����
// ����: int key �L�[
//       char *data �Ή�����f�[�^�ƂȂ镶����
// �ߒl: �������ꂽ�v�f�ւ̃|�C���^�D 
struct cell* make_cell(const char* name, const char* data)
{
	struct cell* mk_cell;

	// cell�̗̈���m�ۂ��� 
	mk_cell = new struct cell;

	/* ������ data �� cell->data �փR�s�[���� */
	strcpy_s(mk_cell->telNum, data);

	// �����֕ϊ�
	strcpy_s(mk_cell->name, name);

	// next��������
	mk_cell->next = NULL;

	return mk_cell;
}

//���X�g�̍\�z
cell* struct_list(ifstream &stream, cell* head) {
	string line;
	
	while (stream >> line)
	{
		// �t�@�C������L�[�ƑΉ�����l�i�t�@�C�����j���擾
		int index = line.find(",");    // ��؂蕶���܂ł̕�����
		string name_str = line.substr(0, index);
		string value = line.substr(index + 1);
		//cout << name_str << endl;
		//cout << value << endl;

		if (value.length() > 255)
		{
			cout << "length of value is too long\n";
			return NULL;
		}

		// ���X�g�v�f�̐���
		struct cell* e_cell;
		e_cell = make_cell(name_str.data(), value.data());

		// ���������v�f�����X�g�̐擪�ɒǉ�
		e_cell->next = head;

		// �擪�A�h���X���X�V
		head = e_cell;
	}
	return head;
}

//���X�g�̌���
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

//���X�g�̏o��
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
	if (argc < 3)  // ����������Ȃ��ꍇ
	{
		cout << "input file name\n";
		return -1;
	}

	// �t�@�C���I�[�v��
	ifstream fp1(argv[1]);
	ifstream fp2(argv[2]);

	// ���X�g�̃w�b�h���`��������
	struct cell* head1;
	head1 = NULL;

	struct cell* head2;
	head2 = NULL;

	// �f�[�^�̃��X�g�ւ̊i�[
	cout << "Loading " << argv[1] << endl;
	head1 = struct_list(fp1, head1);
	fp1.close();

	cout << "Loading " << argv[2] << endl;
	head2 = struct_list(fp2, head2);
	fp2.close();
	
	// ���X�g head2���C���X�g head1�Ɍ����i�{�֐�����������j
	join_list(head1, head2);

	// head1��\���i�؍\���̍u�`�������Q�Ɓj
	print_file_list(head1);

	return 0;
}