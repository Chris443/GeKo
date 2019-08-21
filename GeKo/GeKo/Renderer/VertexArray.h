#pragma once

/*
*	@ TODO: Implement
*	2 Possible Approaches:
*	-Use one VAO for every Geometry
*	-Use one Global Vertex Array and always bind the Buffers  (better according to NVIDIA benchmarks)
*/

namespace gke {

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
	};

}