#include "../include/CFGManager.h"



// ================================= CLASS CFGMANAGER::EXCEPTION =================================




CFGManager::exception::exception(const std::string& function_name, const std::string& error, 
										  const unsigned int& error_code) noexcept
{
	_message = "Exception '" + error + "' in the function '" + function_name + "'";
	_error_code = error_code;
}



const char* CFGManager::exception::what() const noexcept
{
	return _message.c_str();
}



const unsigned int& CFGManager::exception::get_error_code() const noexcept
{
	return _error_code;
}







// ================================= CLASS CFGMANAGER =================================



CFGManager::CFGManager() noexcept {}




CFGManager::CFGManager(const CFGManager& other) noexcept
{
	_data = other._data;
	_file_path = other._file_path;
}




CFGManager::CFGManager(const std::string& file_path) noexcept
{
	_file_path = file_path;
}





bool CFGManager::is_key_exists(const std::string& key) const noexcept
{
	if (_data.find(key) != _data.end())
		return true;
	return false;
}





bool CFGManager::is_empty() const noexcept
{
	if (CFGManager::size() == 0) 
		return true;
	return false;
}





size_t CFGManager::size() const noexcept
{
	return _data.size();
}





void CFGManager::open()
{
	if (_file_path.empty())
		throw CFGManager::exception("open", "the path to the file is not specified", 
			CFGManager::exception::exceptions::FILE_PATH_IS_NOT_SPECIFIED);

	
	_filestream.open(_file_path, std::ios::in);


	if (!_filestream.is_open())
		throw CFGManager::exception("open", "the file stream could not be opened for reading", 
			CFGManager::exception::exceptions::FILESTREAM_CANT_BE_OPENED_FOR_READING);



	std::string current_line;
	std::cmatch result;
	std::regex pattern(R"(\[(.+)\]\s*:\s*)"		// selects lines between square brackets, separated by colon
					   R"(\[(.+)\])");

	// Parsing line
	while (std::getline(_filestream, current_line))
	{
		// If the current line matches
		if (std::regex_match(current_line.data(), result, pattern))
		{
			_data[result[1]] = result[2];
		}
	}

	_filestream.close();
}





void CFGManager::save()
{
	if (_file_path.empty())
		throw CFGManager::exception("save", "the path to the file is not specified", 
			CFGManager::exception::exceptions::FILE_PATH_IS_NOT_SPECIFIED);


	_filestream.open(_file_path, std::ios::out);

	if (!_filestream.is_open())
		throw CFGManager::exception("save", "the file stream could not be opened for writing", 
			CFGManager::exception::exceptions::FILESTREAM_CANT_BE_OPENED_FOR_WRITING);



	for (auto& i : _data)
		_filestream << '[' << i.first << "]:[" << i.second << "]\n";



	_filestream.close();
}





void CFGManager::set_file_path(const std::string& file_path) noexcept
{
	_file_path = file_path;
}





std::string CFGManager::get_file_path() const noexcept
{
	return _file_path.c_str();
}





void CFGManager::add_key(const std::string& key, const std::string& value) noexcept
{
	_data[key] = value;
}





void CFGManager::remove_key(const std::string& key) noexcept
{
	_data.erase(key);
}





void CFGManager::clear() noexcept
{
	_data.clear();
}




// Provides access to container
std::unordered_map<std::string, std::string>& CFGManager::get_container() noexcept
{
	return _data;
}



// Provides access to container
const std::unordered_map<std::string, std::string>& CFGManager::get_container() const noexcept
{
	return _data;
}




void CFGManager::rename_key(const std::string& key, const std::string& new_name) noexcept
{
	auto node = _data.extract(key);
	if(node)
	{
		node.key() = new_name;
		_data.insert(std::move(node));
	}
}




void CFGManager::operator = (const CFGManager& other) noexcept
{
	_data = other._data;
	_file_path = other._file_path;
}




std::string& CFGManager::operator [] (const std::string& key)
{
	if(_data.find(key) != _data.end())
		return _data[key];
	
	throw exception("operator []", "Key `" + key + "` not found", exception::KEY_NOT_FOUND);
}




bool operator == (const CFGManager& first, const CFGManager& second) noexcept
{
	return first.get_container() == second.get_container();
}