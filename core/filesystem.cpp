#include "filesystem.h"

#include <experimental/filesystem>
#include <fstream>

namespace fs = std::experimental::filesystem;

bool filesystem::file_exists(const char* filename)
{
	bool exists = fs::exists(filename) && fs::is_regular_file(filename);

	return exists;
}

bool filesystem::file_size(const char* filename, size_t& size)
{
	bool result = false;

	if (file_exists(filename)) { 
		result = true; 
		size = static_cast<size_t>(fs::file_size(filename));
	}

	return result;
}

bool filesystem::read_file(const char* filename, void** buffer, size_t& size)
{
	bool result = false;

	if (file_exists(filename)) {
		std::ifstream stream(filename, std::ios::binary);
		if (stream.is_open()) {
			if (file_size(filename, size)) {
				result = true;

				*buffer = new char[size];
				stream.read(static_cast<char*>(*buffer), size);
			}
		}
	}

	return result;
}

bool filesystem::write_file(const char* filename, void* buffer, size_t size)
{
	bool result = false;

	std::ofstream stream(filename, std::ios::binary);
	if (stream.is_open()) {
		result = true;
		stream.write(static_cast<char*>(buffer), size);
		stream.close();
	}

	return result;
}

void filesystem::free_file(void* buffer)
{
	delete buffer;
}

bool filesystem::delete_file(const char* filename)
{
	bool result = false;

	if (file_exists(filename)) {
		result = fs::remove(filename);
	}

	return result;
}

bool filesystem::copy_file(const char* source, const char* destination, bool overwrite)
{
	bool result = false;

	if (file_exists(source)) {
		result = fs::copy_file(source, destination, (overwrite ? fs::copy_options::overwrite_existing : fs::copy_options::skip_existing));
	}

	return result;
}

bool filesystem::directory_exists(const char* directory)
{
	bool result = fs::exists(directory) && fs::is_directory(directory);

	return result;
}

bool filesystem::copy_directory(const char* source, const char* destination, bool recursive)
{
	bool result = false;

	if (directory_exists(source)) {
		result = false;
		fs::copy(source, destination, (recursive ? fs::copy_options::recursive : fs::copy_options::none));
	}

	return result;
}

void filesystem::create_directory(const char* directory)
{
	fs::create_directories(directory);
}

void filesystem::delete_directory(const char* directory)
{
	if (directory_exists(directory)) {
		fs::remove_all(directory);
	}
}

void filesystem::delete_empty_directory(const char* directory)
{
	if (directory_exists(directory) && fs::is_empty(directory)) {
		fs::remove(directory);
	}
}

void filesystem::set_current_path(const char* pathname)
{
	fs::current_path(pathname);
}

void filesystem::get_current_path(char* pathname, size_t size)
{
	strcpy_s(pathname, size, fs::current_path().string().c_str());
}

