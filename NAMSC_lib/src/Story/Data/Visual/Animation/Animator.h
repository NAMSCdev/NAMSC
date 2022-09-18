#pragma once
#include "Global.h"

#include "Story/Data/Visual/Animation/AnimNode.h"

//Base class for an Animator, which controls the animation output that will be assigned to change something that is being animated
template<class DataType, unsigned dimension>
class Animator
{
public:
	Animator() = default;
	Animator(std::vector<AnimNode<DataType, dimension>> &&nodes) :
		nodes(move(nodes)) {}

	//Calculates interpolated state in given [time]
	DataType[dimension] currentAnimState(double time) 
	{
		//TODO: Set currentNode and nextNode, check if the animation has ended
		DataType[dimension] ret			= currentNode->state;
		double				deltaTime	= time - currentNode->timestamp,
							duration	= nextHode->timestamp - currentNode->timestamp;
		switch (nextNode->interpolationMethod)
		{
		case AnimInterpolationMethod::Linear:
		default:
			for (unsinged i = 0u; i != dimension; ++i)
			{
				if (duration == 0.0)
					ret[i] = nextNode->state[i];
				else
					ret[i] += (nextNode->state[i] - ret[i]) * (deltaTime/duration);
			}
			break;
		}
		return ret;
	};

	virtual ~Animator() = 0;

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	virtual SerializationID									getType() const		= 0;

	//TODO: Switch to AnimAsset and create smart loading and unloading instead of raw data inside this class
	//Holds all the AnimNodes, that contain sequential changes
	std::vector<AnimNode<DataType, dimension>>				nodes;

	//Nodes containing current state and next state that we interpolate into
	std::vector<AnimNode<DataType, dimension>>::iterator	currentNode, 
															nextNode;
	//TODO: serialize using AnimAsset
	//---SERIALIZATION---
	//Loading an object from a binary file
	virtual void serializableLoad(QIODevice &ar);

	//Saving an object to a binary file
	virtual void serializableSave(QIODevice &ar) const;
};

//One dimensional Animator, which controls the animation output that will be assigned to change something that is being animated
template <class DataType>
using Animator1D = Animator<DataType, 1>;

//Two dimensional Animator, which controls the animation output that will be assigned to change something that is being animated
template <class DataType>
using Animator2D = Animator<DataType, 2>;

//Three dimensional Animator, which controls the animation output that will be assigned to change something that is being animated
template <class DataType>
using Animator3D = Animator<DataType, 3>;

//Four dimensional Animator, which controls the animation output that will be assigned to change something that is being animated
template <class DataType>
using Animator4D = Animator<DataType, 4>;

