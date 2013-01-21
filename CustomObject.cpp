/*
 *  CustomObject.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 12/27/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */
#define IDENT(n) for (int i = 0; i < n; ++i) printf("    ")
#include "CustomObject.h"

void CustomObject::DefineBody(void){
	int size = this->points.size();
	b2Vec2 verticles[size];

	std::list<Point>::iterator i;
	Point p;	

	int j = 0;	
	for(i = this->points.begin(); i != this->points.end(); ++i){
		p = *i;
		verticles[j].Set(p.x, p.y);
		j++;
	}

	b2PolygonShape polygonShape;
	polygonShape.Set(verticles, size);
	
	b2FixtureDef shapeDef;
	shapeDef.shape = &polygonShape;
	shapeDef.density = 0.8f;
	shapeDef.friction = 0.3f;
	shapeDef.restitution = 0.2f;

	this->body->CreateFixture(&shapeDef);

	return ;
}

void CustomObject::LoadJSON(std::string file){
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
void CustomObject::LoadVertexes(json_value *root){
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

void CustomObject::PrintTree(json_value *root, int ident){
	for(json_value *value = root->first_child; value; value = value->next_sibling){
		printf("iterace\n");
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

