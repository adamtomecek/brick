/*
 *  JsonLoader.h
 *  sfml
 *
 *  Created by Adam Tomeček on 1/31/13.
 *  Copyright 2013 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef JSON_LOADER_H
#define JSON_LOADER_H

#include "Includes.h"
#include "vjson/json.h"

enum{
	X, Y
};

class JsonLoader{
	public:
		JsonLoader(std::string file);
		std::list<Point>* GetPoints(void);

	private:
		void LoadJSON(std::string file);
		void LoadVertexes(json_value *root);
		void PrintTree(json_value *root, int ident);

		std::list<Point> points;
};

#endif

