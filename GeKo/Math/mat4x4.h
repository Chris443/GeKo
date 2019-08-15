/**
* @class mat4x4 float
* @author Christian Kati
*
* @brief Basic matrix class for mathematical operations
		 uses COLUMN_MAJOR by default
*		  feel free to extend the current version
*	-templating
*/

#pragma once

namespace gkm {

	class mat4 {
	public:
		//creates an identitiy matrix
		mat4();
		//sets the diagonal to n
		mat4(float n);

		float m[4][4];
	private:

	};

}