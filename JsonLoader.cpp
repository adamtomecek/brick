/*
 *  JsonLoader.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 1/31/13.
 *  Copyright 2013 Brain Dead Cookie. All rights reserved.
 *
 */

#include "JsonLoader.h"

#define IDENT(n) for (int i = 0; i < n; ++i) printf("    ")

std::list<Point>* JsonLoader::GetPoints(void){
	return &points;
}

JsonLoader::JsonLoader(std::string file){
	this->LoadJSON(file);

	return ;
}

void JsonLoader::LoadJSON(std::string file){
	std::ifstream in(file.c_str(), std::ios::in | std::ios::binary);
	std::string contents;
	in.seekg(0, std::ios::end);
	contents.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&contents[0], contents.size());
	in.close();

	char *cstr = new char[contents.length() + 1];
	strcpy(cstr, contents.c_str());

	block_allocator allocator(1 << 10);

	char *errorPos = 0;
	char *errorDesc = 0;
	int errorLine = 0;
	json_value *root = json_parse(cstr, &errorPos, &errorDesc,
			&errorLine, &allocator);

	int ident = 0;

#ifdef DEBUG
	this->PrintTree(root, ident);
#endif

	this->LoadVertexes(root);

	delete [] cstr;
}


/*
 * loads JSON format [{x: 1, y: 1}, {} ... ]
 *
 */
void JsonLoader::LoadVertexes(json_value *root){
	int i = 0;
	std::list<Point> points;
	Point p;
	for(json_value *value = root->first_child; value;
		value = value->next_sibling){

		/* if object, cycle through its children - hopefully x and y values */
		if(value->type == JSON_OBJECT){
			for(json_value *val = value->first_child; val;
				val = val->next_sibling){

				if(val->type == JSON_FLOAT){
					if(!val->name){
						std::cout << "Error while loading JSON file" << std::endl;
						break;
					}
					if(strncmp(val->name, "x", 1) == 0){
						p.x = val->float_value;
					}else{
						p.y = val->float_value;
					}

					i++;
					/* push every second iteration */
					if(i != 0 && i % 2 == 0){
#ifdef DEBUG
						printf("x: %f, y: %f\n", p.x, p.y);
#endif
						points.push_back(p);
					}

				}
			}
		}
	}

	this->points = points;
}

void JsonLoader::PrintTree(json_value *root, int ident){
	for(json_value *value = root->first_child; value; value = value->next_sibling){
		IDENT(ident);
		if (value->name){
			printf("%s = ", value->name);
		}
		switch(value->type){
			case JSON_OBJECT:
			case JSON_ARRAY:
				printf(value->type == JSON_OBJECT ? "{\n" : "[\n");
				this->PrintTree(value, ident + 1);
				IDENT(ident);
				printf(value->type == JSON_OBJECT ? "}\n" : "]\n");
			break;
			case JSON_NULL:
				printf("null\n");
				break;
			case JSON_STRING:
				printf("\"%s\"\n", value->string_value);
				break;
			case JSON_INT:
				printf("%d\n", value->int_value);
				break;
			case JSON_FLOAT:
				printf("%f\n", value->float_value);
				break;
			case JSON_BOOL:
				printf(value->int_value ? "true\n" : "false\n");
				break;
		}
	}		
}

