#include "ini_parser.h"
#include <fstream>
#include "tokener.h"

namespace qh
{
	bool INIParser::Parse(const std::string& ini_file_path)  
	{
		std::string line_seperator = "\n" ;
		std::string key_value_seperator = "=";
		std::ifstream t ;
		size_t len ;
		t.open(ini_file_path);
		t.seekg(0 ,std::ios::end);
		len = (size_t)t.tellg();
		t.seekg(0 , std::ios::beg);
		char * buffer = new char[len] ;
		t.read(buffer , len);
		for(size_t i = 0 ; i < len ; i++ )
		{
			if (buffer[i] == ':')
				key_value_seperator = ":" ;
			if (buffer[i] == '|')
			{
				line_seperator = "||" ;
			}
		}
		t.close() ;
		bool flag = Parse(buffer , len ,line_seperator,key_value_seperator) ;
		delete [] buffer ;
		buffer = NULL;
		return flag ;
	}
	//将字符串中的line_seperator 统一转换成'\n' ,便于统一处理。
	bool INIParser::Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator , const std::string& key_value_seperator)
	{
		bool flag = false ;
		std::map<std::string,std::string> assistMap ; 
		std::string str(ini_data , ini_data_len);
		if (line_seperator.compare("\n") != 0 )
		{
			 ReplaceAllDistinct(str,line_seperator ,"\n"); 
		}   
		if (key_value_seperator.compare("=") != 0 )
		{
			 ReplaceAllDistinct(str,key_value_seperator ,"="); 
		}   
		char line_sep = '\n';
		char kv_sep = '=';
		Tokener token(str);
		token.skipSpaces() ;
		std::string key;
		std::string value;
		while (!token.isEnd()) 
		{
			key = token.nextString(kv_sep);
			if(key.find(line_sep) != -1 )
			{
				token.skipBackTo(line_sep);
				key = token.nextString(kv_sep);
			}
            const char* curpos = token.getCurReadPos();
            int nreadable = token.getReadableSize();
            value = token.nextString(line_sep);

			if (!key.empty() && value.empty() && nreadable > 0) 
			{
				assert(curpos);
                value.assign(curpos, nreadable);
				if(value.find(line_sep) != -1 )
					value.clear();
             }
			if (!key.empty() && !value.empty())
			{
				assistMap.insert(std::make_pair(key,value));
			}
			else
				token.next();
        }
		if (!assistMap.empty())
		{
			smap.insert(std::make_pair("default",assistMap));
			flag = true ;
		}
		return flag ;
	}


	void INIParser::ReplaceAllDistinct(std::string& str, const std::string& old_value ,const std::string& new_value)//字符替换
	{   
		for(std::string::size_type pos(0); pos != std::string::npos; pos+=new_value.length()) 
		{   
			if( (pos = str.find(old_value,pos)) != std::string::npos )   
				str.replace(pos,old_value.length(),new_value);   
			else   
				break;   
		}   
	}
	const std::string& INIParser::Get(const std::string& section, const std::string& key, bool* found)
	{
		str = "" ;
		if (found)
			*found = false ;
		std::map<std::string,std::string> m;
		if( smap.count(section) > 0 && smap[section].count(key) > 0)
		{
			m = smap[section];
			str = m[key] ;
			if(found)
				*found = true ;
		}
		return str ;
	}
	const std::string& INIParser::Get(const std::string& key, bool* found)
	{
		return Get("default",  key, found);
	}
}