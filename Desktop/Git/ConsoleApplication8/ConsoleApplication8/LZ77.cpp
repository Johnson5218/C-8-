#include"LZ77.h"
#include<iostream>
#include<assert.h>
using namespace std;


LZ77::LZ77()
	: _pWin(new UCH[WSIZE * 2])
	, _ht(WSIZE)
	, _start(0)
{}

LZ77::~LZ77()
{
	if (_pWin)
	{
		delete[] _pWin;
	}
}

void LZ77::CompressFile(const std::string& filePath)
{
	FILE* fIn = fopen(filePath.c_str(), "rb");
	if (nullptr == fIn)
	{
		cout << "���ļ�ʧ��" << endl;
		return;
	}

	//��ȡ�ļ���С
	fseek(fIn, 0, SEEK_END);
	ULL fileSize = ftell(fIn);
	fseek(fIn, 0, SEEK_SET);

	//�ļ���СС�������ֽڣ�����Ҫ����ѹ��
	if (fileSize < 3)
		return;

	USH hashAddr = 0;
	//�ȶ�ȡһ��������������
	size_t lookAhead = fread(_pWin, 1, 2*WSIZE,fIn);
	for (size_t i = 0; i < MIN_MATCH; i++)
		_ht.HashFunc(hashAddr, _pWin[i]);
	
	//дԴ�ļ���׺
	FILE* fOutD = fopen("1.lzp", "wb");
	assert(fOutD);
	string postFix = filePath.substr(filePath.rfind('.'));
	postFix += '\n';
	fwrite(postFix.c_str(), 1, postFix.size(), fOutD);

	FILE* fOutF = fopen("2.lzp", "wb");
	assert(fOutF);


	USH matchHead = 0;
	UCH chFlag = 0;
	UCH bitCount = 0;
	while (lookAhead)
	{
		//��startΪ�׵����ĸ��ַ����뵽��ϣ����
		_ht.Insert(hashAddr, _pWin[_start + 2], _start, matchHead);

		if (0 == matchHead)
		{
			//û���ҵ�ƥ��,дԴ�ַ�
			fputc(_pWin[_start], fOutD);
			++_start;
			--lookAhead;
			//д���---Դ�ַ���0���--false
			//д���λ
			WriteFlag(fOutF, chFlag, bitCount, false);
		}
		else
		{
			//���ƥ��
			UCH curMatchDist = 0;
			UCH curMatchLen = longMatch(matchHead, curMatchDist);
			
			//д���볤�ȶ�
			fputc(curMatchDist, fOutD);
			fputc(curMatchLen, fOutD);
			
			//д���λ
			//���Ⱦ����--->��1���б��
			WriteFlag(fOutF, chFlag, bitCount, true);
			
			lookAhead -= curMatchLen;

			//���¹�ϣ��
			curMatchLen -= 1;
			while (curMatchLen)
			{
				++_start;
				_ht.Insert(hashAddr, _pWin[_start + 2], _start, matchHead);
				curMatchLen--;
			}
			++_start;
		}
	}
	//���һ����ǲ���8������λ��Ҫ���⴦��
	if (bitCount >> 0 && bitCount << 8)
	{
		chFlag <<= (8 - bitCount);
		fputc(chFlag, fOutF);
	}

	fclose(fIn);
	fclose(fOutF);

	//������ļ������ݰ��Ƶ�ѹ���ļ���
	FILE* fInF = fopen("2.lzp", "rb");
	assert(fInF);
	UCH* pReadBuff = new UCH[1024];
	size_t flagSize = 0;
	while (true)
	{
		size_t rdSize = fread(pReadBuff, 1, 1024, fInF);
		if (0 == rdSize)
		{
			break;
		}
		flagSize += rdSize;
		fwrite(pReadBuff, 1, rdSize, fOutD);
	}

	fclose(fInF);

	fwrite(&fileSize, sizeof(fileSize), 1, fOutD);
	fwrite(&fileSize, sizeof(flagSize), 1, fOutD);

	fclose(fOutD);
	remove("2.lzp");
	
}

//matchHead--->��ϣƥ������ʼλ��
UCH LZ77::longMatch(USH matchHead, UCH& curMatchDist)
{


	
	UCH curMatchLen = 0;
	UCH maxLen = 0;
	UCH pos = 0;
	UCH Matchchainlen = 255;
	do{	
		UCH* pStart = _pWin + _start;
		UCH* pEnd = pStart + MAX_MATCH;
		//�ڲ��һ������ҵ�ƥ�䴮��λ��
		UCH* pCurStart = _pWin + matchHead;
		
		curMatchLen = 0;

		//�ҵ�������ƥ�䳤��
		while (pCurStart <pEnd && *pStart == *pCurStart)
		{
			pStart++;
			pCurStart++;
			curMatchLen++;
		}
		if (curMatchLen>maxLen)
		{
			maxLen = curMatchLen;
			pos = matchHead;		
		}
	} while((matchHead = _ht.GetNext(matchHead))&& Matchchainlen--);
	
	curMatchDist = _start - pos;

	return maxLen;
}



void  LZ77::WriteFlag(FILE* fOutF, UCH& chFlag, UCH& bitCount, bool IsChar)
{
	chFlag <<= 1;

	//��⵱ǰ����Ƿ�Ϊ�����
	if (IsChar)
	{
		chFlag |= 1;
	}
	
	bitCount++;
	if (8 == bitCount)
	{
		fputc(chFlag, fOutF);
		chFlag = 0;
		bitCount = 0;
	}
}

void LZ77::UNCompressFile(const std::string& filePath)
{
	string strPostFix = filePath.substr(filePath.rfind('.'));
	if (strPostFix != ".lzp")
	{
		cout << "ѹ���ļ���֧��" << endl;
		return;
	}

	FILE* fInD = fopen(filePath.c_str(),"rb");
	if (nullptr == fInD)
	{
		cout << "ѹ���ļ���ʧ��" << endl;
		return;
	}

	//��ȡ��ǵĵĴ�С
	size_t flagSize = 0;
	int offset = 0 - sizeof(flagSize);
	fseek(fInD, offset, SEEK_END);
	
	fread(&flagSize, sizeof(flagSize), 1, fInD);
	
	//��ȡԴ�ļ��Ĵ�С
	ULL fileSize = 0;
	offset = 0 - sizeof(fileSize)-sizeof(flagSize);
	fseek(fInD, offset, SEEK_END);
	fread(&fileSize, sizeof(fileSize), 1, fInD);

	//fInF���ã���ȡ�������
	FILE* fInF = fopen(filePath.c_str(), "rb");
	assert(fInF);
	offset = 0 - (sizeof(fileSize) + sizeof(flagSize) + flagSize);
	fseek(fInF, offset, SEEK_END);
	
	//��ѹ���ļ�
	fseek(fInD, 0, SEEK_SET);
	string strUNComFileName("3");
	strPostFix = "";
	GetLine(fInD, strPostFix);
	strUNComFileName += strPostFix;

	//fOut���ã�дѹ������
	FILE* fOut = fopen(strUNComFileName.c_str(), "wb");
	assert(fOut);

	//�����Ⱦ����
	FILE* fWin = fopen(strUNComFileName.c_str(), "rb");
	assert(fWin);

	UCH charFlag = 0;
	char bitCount = -1;


	while (fileSize)
	{
		//��ȡ���
		if (bitCount < 0)
		{
			charFlag = fgetc(fInF);
			bitCount = 7;
		}
		//0	Դ����
		//1	�����
		if (charFlag & (1 << bitCount))
		{
			//�����
			UCH dist = fgetc(fInD);
			UCH length = fgetc(fInD);

			fflush(fOut);
			fseek(fWin, 0 - dist, SEEK_END);
			fileSize -= length;
			

			while (length)
			{
				UCH ch = fgetc(fWin);
				fputc(ch, fOut);
				length--;
			}

		}
		else
		{
			UCH ch = fgetc(fInD);
			fputc(ch, fOut);
			fileSize -= 1;
		}

		bitCount--;
	}
	fclose(fInD);
	fclose(fInF);
	fclose(fOut);
	fclose(fWin);

}

void LZ77::GetLine(FILE* fIn, std::string& strContent)//��ȡÿһ�е���Ϣ��ʵ��
{
	while (!feof(fIn))
	{
		char ch = fgetc(fIn);
		if ('\n' == ch)
		{
			return;
		}
		strContent += ch;
	}
}