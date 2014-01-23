#include <string>
#include <stdio.h>
#include <string.h>

#include "JsonFileManager.h"
#include "system.h"

jsonFileManager::jsonFileManager(const std::string & fileName)
	:_fileName(fileName)
{
}

jsonFileManager::~jsonFileManager(void)
{
}

int	jsonFileManager::write(const std::string & text)
{
	return 0;
}

int	jsonFileManager::_parseSystem(SolarSystem * solarSystem)
{
    int		i, intTmp;
	json_t *			root;
    json_error_t		error;
	
	root = json_loads(_text.c_str(), 0, &error);
	if(!root)
	{
		std::cout << "error: on line " << error.line << ": " << error.text << std::endl;
		return 1;
	}

    //verif type file
    json_t *type;
    type = json_object_get(root, "type");
    if(!json_is_string(type) || strcmp(json_string_value(type), "system") != 0)
    {
        std::cout << "error: on type" << std::endl;
        json_decref(root);
        return 1;
    }
    std::cout << "Type file : System" << std::endl;

	//date
	json_t *date;
	date = json_object_get(root, "date");
    if(!json_is_string(date))
    {
		std::cout << "error: on date" << std::endl;
		json_decref(root);
		return 1;
    }
	std::string tmp(json_string_value(date));
	solarSystem->date(tmp);
	std::cout << "Parsing date, done" << std::endl;

	//nombre d'astres
	json_t *nbAstre;
	nbAstre = json_object_get(root, "nombreAstres");
	if(!json_is_integer(nbAstre))
    {
		std::cout << "error: on astres numbers" << std::endl;
		json_decref(root);
		return 1;
    }
	intTmp = json_integer_value(nbAstre);
	solarSystem->nbAstre(intTmp);
	solarSystem->astres(intTmp);
	std::cout << "Parsing number astres, done" << std::endl;

	//astres, tableau
	//astre
	json_t *astres;
	astres = json_object_get(root, "astres");
	if(!json_is_array(astres))
	{
		std::cout << "error: astres is not an array" << std::endl;
		json_decref(astres);
		return 1;
	}
	int size = json_array_size(astres);
    if (size != intTmp)
    {
        std::cout << "error: on astre number" << std::endl;
        json_decref(root);
        return 1;
    }
    json_t *astre;
    json_t *data;
	for(i = 0; i < size; i++)
    {
        data = json_array_get(astres, i);
        if (!json_is_object(data))
		{
            std::cout << "error: on astre array" << std::endl;
			json_decref(root);
			return 1;
		}
        astre = json_object_get(data, "astre");
        if (!json_is_string(astre))
        {
            std::cout << "error: on astre" << std::endl;
            json_decref(root);
            return 1;
        }
		tmp = json_string_value(astre);
		solarSystem->astres(i, tmp);
	}
	std::cout << "Parsing astres, done" << std::endl;

    //nombre d'materials
    json_t *nbMaterial;
    nbMaterial = json_object_get(root, "nombreMaterials");
    if(!json_is_integer(nbMaterial))
    {
        std::cout << "error: on materials numbers" << std::endl;
        json_decref(root);
        return 1;
    }
    intTmp = json_integer_value(nbMaterial);
    solarSystem->nbMaterial(intTmp);
    solarSystem->materials(intTmp);
    std::cout << "Parsing number materials, done" << std::endl;

	//materiaux
	json_t *materials;
    materials = json_object_get(root, "materials");
    if(!json_is_array(materials))
	{
		std::cout << "error: materials is not an array" << std::endl;
		json_decref(root);
		return 1;
    }
    size = json_array_size(materials);
    if (size != intTmp)
    {
        std::cout << "error: on material number" << std::endl;
        json_decref(root);
        return 1;
    }
    json_t *material;
    for(i = 0; i < size; i++)
    {
        data = json_array_get(materials, i);
        if (!json_is_object(data))
        {
            std::cout << "error: on material array" << std::endl;
            json_decref(root);
            return 1;
        }
        astre = json_object_get(data, "material");
        if (!json_is_string(material))
        {
            std::cout << "error: on material" << std::endl;
            json_decref(root);
            return 1;
        }
        tmp = json_string_value(material);
        solarSystem->materials(i, tmp);
    }
    std::cout << "Parsing materials, done" << std::endl;
	return 0;
}

int jsonFileManager::_writeSystem(const SolarSystem & solarSystem)
{
	json_t		*tmp;

	tmp = json_object();
	//add date

	//add nbastres

	//add astres, array
	//add astre

	//add materials

	//write
	//int json_dump_file(const json_t *json, const char *path, size_t flags)
	return 0;
}

bool jsonFileManager::_isReadable(void)
{
	std::ifstream file(_fileName.c_str()); 
    std::cout << "Filename : " << _fileName.c_str() << std::endl;
    return !file.fail();		
}

int jsonFileManager::_read(void)
{
	std::stringstream buffer;
	std::ifstream file(_fileName.c_str());
	if (!file)
		return 1;
	buffer << file.rdbuf();
    _text = buffer.str();
	return 0;
}

int jsonFileManager::_write(void)
{
	if (!_text.c_str())
		return 1;
    std::ofstream file(_fileName.c_str());
	if (!file)
		return 1;
	file << _text;
	return 0;
}

//*Getter // Setter

void	jsonFileManager::fileName(const std::string & fileName)
{
	this->_fileName = fileName;
}

const std::string & jsonFileManager::fileName(void)
{
	return _fileName;
}

void jsonFileManager::text(const std::string & text)
{
	this->_text = text;
}

const std::string & jsonFileManager::text(void)
{
	return _text;
}
