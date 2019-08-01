#ifndef __M_CLOUD_H__
#define __M_CLOUD_H__

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include<boost/filesystem.hpp>
#include<boost/algorithm/string.hpp>

#define CLIENT_BACKUP_DIR "backup"
#define CLIENT_BACKUP_INFO_FILE "back.list"
#define RANGE_MAX_SIZE (10 << 20)
//10M

namespace bf = boost::filesystem;
class CloudClient
{
public:
	//��ȡ������Ϣ
	bool GetBackupInfo(){
		//filename1 etag\n
		//filename2 etag\n
		bf::path path(CLIENT_BACKUP_INFO_FILE);
		if (!bf::exists(path))
		{
			std::cerr << "list file" << path.string() << " is not exist" << std::endl;
			return false;
		}
		int64_t fsize = bf::file_size(path);
		if (fsize == 0)
		{
			std::cerr << "have no backup info" << std::endl;
			return false;
		}
		std::string body;
		body.resize(fsize);
		std::ifstream file(CLIENT_BACKUP_INFO_FILE, std::ios::binary);
		if (!file.is_open())
		{
			std::cerr << "list file open error" << std::endl;
			return false;
		}
		file.read(&body[0], fsize);
		if (!file.good())
		{
			std::cerr << "read list file body error" << std::endl;
			return false;
		}
		file.close();
		std::vector<std::string> list;
		boost::split(list, body, "\n");
		
		for (auto i : list){
			//filename1 etag\n
			size_t pos = i.find(" ");
			if (pos == std::string::npos)
			{
				continue;
			}
			std::string key = i.substr(0, pos);
			std::string val = i.substr(pos + 1);
			_backup_list[key] = val;
		}
		return true;
	}
	
	//����
	bool SetBackuoInfo()
	{
		std::string body;
		for (auto i : _backup_list)
		{
			body += i.first + " " = i.second + "\n";
		}
		std::ofstream file(CLIENT_BACKUP_INFO_FILE, std::ios::binary);
		if (!file.is_open()){
			std::cerr << "open list file error\n";
			return false;
		}
		file.write(&body[0], body.size());
		if (!file.good()){
			std::cerr << "set backup info error\n";
			return false;
		}
		file.close();
		return true;
	}
	
	//Ŀ¼����
	bool BackupDirListen(const std::string &path)
	{
		bf::directory_iterator item_begin(CLIENT_BACKUP_DIR);
		bf::directory_iterator item_end;
		for (; item_begin != item_end; ++item_begin){
			//�ݹ�ʵ������Ŀ¼
			if (bf::is_directory(item_begin->status())){
				BackupDirListen(item_begin->path().string());
				continue;
			}
			//���ñ��ݵ���ͨ�ļ�
			if (FileIsNeedBackup(item_begin->path().string()) == false){
				continue;
			}
			//��Ҫ���ݵ���ͨ�ļ�
			if (PutFileData(item_begin->path().string()) == false){
				continue;
			}
			AddBackInfo(item_begin->path().string());
		}
	}
	
	//���һ����Ϣ
	bool AddBackInfo(const std::string &file)
	{
		//etag = "mtime-fsize"
		std::string etag;
		if (GetFileEtag(file, etag) == false)
		{
			return false;
		}

		_backup_list[file] = etag;
	}
	


	bool GetFileEtag(const std::string &file,std::string &etag)
	{
		bf::path path(file);
		if (!bf::exists(path))
		{
			std::cerr << "get file" << file << " etag error\n";
			return false;
		}
		int64_t fsize = bf::file_size(path);
		int64_t mtime = bf::last_write_time(path);
		std::stringstream tmp;
		tmp << std::hex << fsize << "-" << std::hex << mtime;
		etag = tmp.str();
		return true;
	}


	//�ļ��Ƿ���Ҫ����
	//���ļ���Ҫ����
	//����ҵ����ļ������һ��������Ҫ���ݣ���һ����Ҫ����
	bool FileIsNeedBackup(const std::string &file)
	{
		std::string etag;
		if (GetFileEtag(file, etag) == false)
		{
			return false;
		}
		auto it = _backup_list.find(file);
		if (it != _backup_list.end() && it->second == etag)
		{
			return false;
		}
		return true;
	}

	//�ϴ�ģ��
	bool PutFileData(const std::string &file)
	{
		//���ֿ��С��10M�����ļ����зֿ鴫��
		//����ͨ����ȡ�ֿ鴫���Ƿ�ɹ��ж������ļ��Ƿ��ϴ��ɹ�
		//ѡ����̴߳���
		return true;
	}

public:
	bool Start()
	{
		//1.��ȡ
		GetBackupInfo();
		while (1)
		{
			BackupDirListen(CLIENT_BACKUP_DIR);
			SetBackuoInfo();
		}
	}
private:
	std::unordered_map<std::string, std::string> _backup_list;
};

#endif