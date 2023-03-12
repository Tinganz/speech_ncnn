#include "dir_iterate.h"
#if defined(__WIN32__) || defined(_WIN32)
#include <windows.h>
#include "dirent_portable.h"
#else
#include <dirent.h>
#endif
#include <string.h>
#include <iostream>
#include <string>
#include <algorithm>

static std::vector<std::string> split(std::string str, std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;//扩展字符串以方便操作
    int size=str.size();

    for(int i = 0; i < size; i++)
    {
        pos = str.find(pattern, i);
        if(pos < size)
        {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}

int DIR_Iterate(std::string directory, std::vector<std::string>& filesAbsolutePath, std::vector<std::string>& filesname, std::vector<std::string>& suffix_filter, std::string prefix_filter, bool suffix, bool prefix, bool recurrence, bool sort)
{
	DIR* dir = opendir(directory.c_str());
	if ( dir == NULL )
	{
		//std::cout << directory << " is not a directory or not exist!" << std::endl;
		return -1;
	}
	struct dirent* d_ent = NULL;
	char dot[3] = ".";
	char dotdot[6] = "..";
	
	while ( (d_ent = readdir(dir)) != NULL )
	{
		if ( (strcmp(d_ent->d_name, dot) != 0)
			&& (strcmp(d_ent->d_name, dotdot) != 0) )
		{
			if ( d_ent->d_type == DT_DIR)
			{
                if (recurrence)
                {
                    std::string newDirectory = directory + std::string("/") + std::string(d_ent->d_name);
                    if( directory[directory.length()-1] == '/')
                    {
                        newDirectory = directory + std::string(d_ent->d_name);
                    }
                    if ( -1 == DIR_Iterate(newDirectory, filesAbsolutePath, filesname, suffix_filter, prefix_filter, suffix, prefix) )
                    {
                        return -1;
                    }
                }
			}
			else
			{
				if (d_ent->d_name[0] == '.')
					continue;
                bool need_add = false;
                std::string suffix_str;
				std::string absolutePath = directory + std::string("/") + std::string(d_ent->d_name);
				if( directory[directory.length()-1] == '/')
				{
					absolutePath = directory + std::string(d_ent->d_name);
				}
                char * pos = strrchr(d_ent->d_name, '.');
                if (pos)
                {
                    suffix_str = std::string(pos + 1);
                    for(auto &elem : suffix_str) elem = std::tolower(elem);
                }

                if (suffix && !suffix_filter.empty())
                {
                    for (auto filter : suffix_filter)
                    {
                        if (filter.compare(suffix_str) == 0)
                        {
                            need_add = true;
                            break;
                        }
                    }
                }
                else if (prefix && !prefix_filter.empty())
                {
                    auto prefix_length = prefix_filter.length();
                    auto name_str = std::string(d_ent->d_name);
                    if (name_str.length() >= prefix_length)
                    {
                        auto prefix_str = name_str.substr(0, prefix_length);
                        if (prefix_str == prefix_filter)
                            need_add = true;
                    }
                }
                else
                    need_add = true;

				if (need_add) filesAbsolutePath.push_back(absolutePath);
				if (!suffix)
				{
					char * pos = strrchr(d_ent->d_name, '.');
					if (pos) *pos = '\0';
				}
				if (need_add) filesname.push_back(d_ent->d_name);
			}
		}
	}
	closedir(dir);
    if (sort)
    {
        std::sort(filesAbsolutePath.begin(), filesAbsolutePath.end());
        std::sort(filesname.begin(), filesname.end());
    }
	return 0;
}
