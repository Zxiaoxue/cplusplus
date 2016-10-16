#pragma once

#include "Heap.h"
#include "Huffman.h"
#include <string>
#include <cassert>
#include <algorithm>

typedef long long LongType;

struct CharInfo
{
	char _ch; //�ַ�
	LongType _count; //�ַ����ֵı���
	string _code; //����

	CharInfo(LongType count = 0)
		:_ch(0)
		,_count(count)
	{}
	bool operator!=(const CharInfo& c)
	{
		return _count != c._count;
	}
	
	CharInfo operator+(const CharInfo& c)
	{
		return (_count+c._count);
	}

	bool operator<(const CharInfo& c)
	{
		return (_count < c._count);
	}
};


class Filecompress
{
public:
	Filecompress()
	{
		for(int i = 0; i<256; ++i)
		{
			_infos[i]._ch = i;
		}
	}

	string CompressFile(const char* filename,CharInfo& invalid = CharInfo())
	{
		//1.ͳ���ַ����ֵĴ���
		//2.����Huffman��
		//3.����Huffman����
		//4.ѹ��
		//5.��ѹ��

		//1.ͳ���ַ����ֵĴ���
		FILE* fIn = fopen(filename,"r");
		assert(fIn);

		char ch = fgetc(fIn);

		while(ch != EOF)
		{
			++(_infos[ch]._count);
			ch = fgetc(fIn);
		}

		//2.����Huffman��
		HuffmanTree<CharInfo> hp(_infos,256);

		//3.����Huffman����
		HuffmanTreeNode<CharInfo>* root = hp.GetRoot();
		string code = "";
		_GenerateHuffman(root,code);

		//����
		/*for(int i = 0; i<256; ++i)
		{
			if(_infos[i] != invalid)
				reverse(_infos[i]._code.begin(),_infos[i]._code.end());
		}*/

		//4.ѹ��
		string compressfilename = filename;
		compressfilename +=  ".compress";

		FILE* fOut = fopen(compressfilename.c_str(),"w");
		assert(fOut);

		//��������
		fseek(fIn,0,SEEK_SET);

		ch = fgetc(fIn);
		char pos = 0;
		int num = 0;
		int size = _infos[ch]._code.size();

		while(ch != EOF)
		{
			for(int i = 0; i < size; ++i)
			{
				string& code = _infos[ch]._code;
				pos <<= 1;
				pos |= code[i] - '0';
				++num;

				if(num == 8)
				{
					fputc(ch,fOut);
					pos = 0;
					num = 0;
				}

			}

			ch = fgetc(fIn);
			size = _infos[ch]._code.size();
		}
		
		if(num)
		{
			pos <<= (8-num);
		}

		fclose(fIn);
		fclose(fOut);

		return compressfilename;
	}

	/*string UnCompressFilename()
	{

	}*/
protected:

	//����Huffman����
	void _GenerateHuffman(HuffmanTreeNode<CharInfo>* root, string& code)
		{
			if(root == NULL)
				return;

			if(root->_left == NULL && root->_right == NULL)
			{
				_infos[root->_weight._ch]._code = code;
				//return;
			}

			_GenerateHuffman(root->_left, code+'0');
			_GenerateHuffman(root->_right, code+'1');

		}

protected:
	CharInfo _infos[256];
};

void Test()
{
	Filecompress filename;
	filename.CompressFile("Huffman.txt");

}