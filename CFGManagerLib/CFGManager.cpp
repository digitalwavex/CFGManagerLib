#include "CFGManager.h"
#include <iostream>


// Default constructor
CFGManager::CFGManager()
{
}




CFGManager::CFGManager(const std::string& file_path = "")
{
	this->file_path = file_path;
}




const bool CFGManager::is_key_exists(const std::string& key)
{
	try
	{
		this->structure.at(key);
		return true;
	}
	catch (std::out_of_range) 
	{
		return false;
	}
	
}





const bool CFGManager::is_empty()
{
	if (this->structure.size() == 0) return true;
	return false;
}





const size_t CFGManager::size()
{
	return this->structure.size();
}





void CFGManager::openconfig(const std::string& file_path)
{
	if (file_path != "")
	{
		this->file_path = file_path;
	}

	this->filestream.open(this->file_path, std::ios::in);


	if (!this->filestream.is_open())
		//throw std::exception("error opening file");
		std::cout << "ERROR OPENING FILE" << std::endl;



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





void CFGManager::save(const std::string& file_path)
{
	if (file_path != "")
		this->file_path = file_path;

	this->filestream.open(this->file_path, std::ios::out);

	for (auto i : this->structure)
		this->filestream << '[' << i.first << "]:[" << i.second << "]\n";

	this->filestream.close();
}





void CFGManager::set_file_path(const std::string& file_path)
{
	this->file_path = file_path;
}





const std::string& CFGManager::get_file_path()
{
	return this->file_path;
}





std::string& CFGManager::operator[](const std::string& key)
{
	return this->structure[key];
}





std::pair <const std::string, std::string>& CFGManager::operator[](const size_t& index)
{
	auto iterator = this->structure.begin();
	std::advance(iterator, index);

	return *iterator;
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





void CFGManager::rename_key(const std::string& key, const std::string& new_name)
{
	auto node = this->structure.extract(key);
	if(node)
	{
		node.key() = new_name;
		this->structure.insert(std::move(node));
	}
}

