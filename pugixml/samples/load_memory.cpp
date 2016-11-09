#include <iostream>
#include <cstring>

int main()
{
    const char source[] = "<mesh name='sphere'><bounds>0 0 1 1</bounds></mesh>";
    size_t size = sizeof(source);

    pugi::xml_document doc;

    {
        pugi::xml_parse_result result = doc.load_buffer(source, size);

        std::cout 
			<< "Load result: " << result.description() 
			<< ", mesh name: " << doc.child("mesh").attribute("name").value() 
			<< std::endl;
    }

    {
        char* buffer = new char[size];
        memcpy(buffer, source, size);
        pugi::xml_parse_result result = doc.load_buffer_inplace(buffer, size);
   
        std::cout 
			<< "Load result: " << result.description() 
			<< ", mesh name: " << doc.child("mesh").attribute("name").value() 
			<< std::endl;

        delete[] buffer;
    }

    {
        char* buffer = static_cast<char*>(pugi::get_memory_allocation_function()(size));
        memcpy(buffer, source, size);

        pugi::xml_parse_result result = doc.load_buffer_inplace_own(buffer, size);

        std::cout 
			<< "Load result: " << result.description() << ", mesh name: " 
			<< doc.child("mesh").attribute("name").value() 
			<< std::endl;
    }

    {
        pugi::xml_parse_result result = doc.load_string("<mesh name='sphere'><bounds>0 0 1 1</bounds></mesh>");

        std::cout 
			<< "Load result: " << result.description() 
			<< ", mesh name: " << doc.child("mesh").attribute("name").value() 
			<< std::endl;
    }
}
