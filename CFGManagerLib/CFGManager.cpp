#include "CFGManager.h"





// ================================= CLASS CFGMANAGER::EXCEPTION =================================
CFGManager::exception::exception(const std::string& function_name, const std::string& error)
{
	this->message = "Exception '" + error + "' in the function '" + function_name + "'";
}



const char* CFGManager::exception::what() const noexcept
{
	return this->message.c_str();
}








// ================================= CLASS CFGMANAGER =================================


// Default constructor
CFGManager::CFGManager() {}




CFGManager::CFGManager(const std::string& file_path = "")
{
	this->file_path = file_path;
}




const bool CFGManager::is_key_exists(const std::string& key)
{
	if (this->structure.count(key) > 0)
		return true;
	return false;
}





const bool CFGManager::is_empty()
{
	if (CFGManager::size() == 0) 
		return true;
	return false;
}





const size_t CFGManager::size()
{
	return this->structure.size();
}





void CFGManager::open()
{
	this->filestream.open(this->file_path, std::ios::in);
	if (!this->filestream.is_open())
		throw CFGManager::exception("open", "the file stream could not be opened for reading");



	std::string current_line;
	std::cmatch result;
	std::regex pattern(R"(\[(.+)\]\s*:\s*)"		// selects lines between square brackets, separated by colon
					   R"(\[(.+)\])");


	// Parsing line
	while (std::getline(this->filestream, current_line))
	{
		// If the current line matches
		if (std::regex_match(current_line.data(), result, pattern))
		{
			this->structure[result[1]] = result[2];
		}
	}

	this->filestream.close();
}





void CFGManager::save()
{
	if (!file_path.empty())
		this->file_path = file_path;



	this->filestream.open(this->file_path, std::ios::out);
	if (!this->filestream.is_open())
		throw CFGManager::exception("save", "the file stream could not be opened for writing");



	for (auto& i : this->structure)
		this->filestream << '[' << i.first << "]:[" << i.second << "]\n";



	this->filestream.close();
}





void CFGManager::set_file_path(const std::string& file_path)
{
	this->file_path = file_path;
}





const char* CFGManager::get_file_path()
{
	return this->file_path.c_str();
}





void CFGManager::add_key(const std::string& key, const std::string& value)
{
	this->structure[key] = value;
}





void CFGManager::remove_key(const std::string& key)
{
	this->structure.erase(key);
}





void CFGManager::clear()
{
	this->structure.clear();
}




// Provide access to container
std::unordered_map<std::string, std::string>& CFGManager::get_container()
{
	return this->structure;
}





void CFGManager::rename_key(const std::string& key, const std::string& new_name)
{
	auto node = this->structure.extract(key);
	if(node)
	{
		node.key() = new_name;
		this->structure.insert(std::move(node));
	}
}


